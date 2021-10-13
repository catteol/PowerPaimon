#ifdef WIN32
#error You must build in x64
#endif

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <string>
#include <thread>
#include <Psapi.h>
#include <shellapi.h>
#include "inireader.h"
#include "resource.h"

#define WND_CLASS_NAME TEXT("unlockfps")
#define WM_TASKTRAY (WM_APP + 1)
HICON hIcon;
HMENU hTaskTrayMenu;

typedef struct {
	HWND hWnd;
	int TargetFPS;
} thread_arg;

// Global
std::string GamePath{};
int SelectedFPS;
std::vector<int> FPSEntry = { 240, 200, 144, 90, 60 };
UINT FPSEntryID[5] = {ID_240, ID_200, ID_144, ID_90, ID_60};

// SystemTray Funcs
void AddSystemTrayIcon(HWND hWnd)
{
	NOTIFYICONDATA nid = { 0 };
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.uFlags = (NIF_ICON | NIF_MESSAGE | NIF_TIP);
	nid.hWnd = hWnd;
	nid.hIcon = hIcon;
	nid.uCallbackMessage = WM_TASKTRAY;
	lstrcpy(nid.szTip, TEXT("unlockfps"));
	Shell_NotifyIcon(NIM_ADD, &nid);
}

void UpdateSystemTrayIcon(HWND hWnd, LPCSTR tip)
{
	NOTIFYICONDATA nid = { 0 };
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.uFlags = (NIF_MESSAGE | NIF_TIP);
	nid.hWnd = hWnd;
	nid.uCallbackMessage = WM_TASKTRAY;
	lstrcpy(nid.szTip, TEXT(tip));
	Shell_NotifyIcon(NIM_MODIFY, &nid);
}

void SendNotification(HWND hWnd, LPCSTR title, LPCSTR msg)
{
	NOTIFYICONDATA nid = { 0 };
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.uFlags = (NIF_MESSAGE | NIF_INFO);
	nid.hWnd = hWnd;
	nid.uCallbackMessage = WM_TASKTRAY;
	lstrcpy(nid.szInfoTitle, TEXT(title));
	lstrcpy(nid.szInfo, TEXT(msg));
	Shell_NotifyIcon(NIM_MODIFY, &nid);
}

void DeleteSystemTrayIcon(HWND hWnd)
{
	NOTIFYICONDATA nid = { 0 };
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hWnd;
	Shell_NotifyIcon(NIM_DELETE, &nid);
}

// didnt made this pattern scan - c+p'd from somewhere
uintptr_t PatternScan(void* module, const char* signature)
{
	static auto pattern_to_byte = [](const char* pattern) {
		auto bytes = std::vector<int>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current) {
			if (*current == '?') {
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else {
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	auto dosHeader = (PIMAGE_DOS_HEADER)module;
	auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

	auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto patternBytes = pattern_to_byte(signature);
	auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

	auto s = patternBytes.size();
	auto d = patternBytes.data();

	for (auto i = 0ul; i < sizeOfImage - s; ++i) {
		bool found = true;
		for (auto j = 0ul; j < s; ++j) {
			if (scanBytes[i + j] != d[j] && d[j] != -1) {
				found = false;
				break;
			}
		}
		if (found) {
			return (uintptr_t)&scanBytes[i];
		}
	}
	return 0;
}

std::string GetLastErrorAsString(DWORD code)
{
	LPSTR buf = nullptr;
	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buf, 0, NULL);
	std::string ret = buf;
	LocalFree(buf);
	return ret;
}

bool GetModule(DWORD pid, std::string ModuleName, PMODULEENTRY32 pEntry)
{
	if (!pEntry)
		return false;

	MODULEENTRY32 mod32{};
	mod32.dwSize = sizeof(mod32);
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	for (Module32First(snap, &mod32); Module32Next(snap, &mod32);)
	{
		if (mod32.th32ProcessID != pid)
			continue;

		if (mod32.szModule == ModuleName)
		{
			*pEntry = mod32;
			break;
		}
	}
	CloseHandle(snap);

	return pEntry->modBaseAddr;
}

DWORD GetPID(std::string ProcessName)
{
	DWORD pid = 0;
	PROCESSENTRY32 pe32{};
	pe32.dwSize = sizeof(pe32);
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	for (Process32First(snap, &pe32); Process32Next(snap, &pe32);)
	{
		if (pe32.szExeFile == ProcessName)
		{
			pid = pe32.th32ProcessID;
			break;
		}
	}
	CloseHandle(snap);
	return pid;
}

bool WriteConfig(std::string GamePath, int fps)
{
	HANDLE hFile = CreateFileA("config.ini", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		DWORD code = GetLastError();
		printf("CreateFileA failed (%d): %s\n", code, GetLastErrorAsString(code).c_str());
		return false;
	}

	std::string content{};
	content = "[Setting]\n";
	content += "Path=" + GamePath + "\n";
	content += "FPS=" + std::to_string(fps);

	DWORD written = 0;
	WriteFile(hFile, content.data(), content.size(), &written, nullptr);
	CloseHandle(hFile);
}

void LoadConfig(int* defaultFPS, HWND* hWnd)
{
	if (GetFileAttributesA("config") != INVALID_FILE_ATTRIBUTES)
		DeleteFileA("config");

	INIReader reader("config.ini");
	if (reader.ParseError() != 0)
	{
		printf("Config not found - Starting first time setup\nPlease leave this open and start the game\nThis only need to be done once\n\n");
		printf("Waiting for game...\n");

		SendNotification(*hWnd, "Config not found", "Starting first time setup - Please start the game\nThis only need to be done once");

		DWORD pid = 0;
		while (!(pid = GetPID("YuanShen.exe")) && !(pid = GetPID("GenshinImpact.exe")))
			std::this_thread::sleep_for(std::chrono::milliseconds(200));

		HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | SYNCHRONIZE, FALSE, pid);

		char szPath[MAX_PATH]{};
		DWORD length = sizeof(szPath);
		QueryFullProcessImageNameA(hProcess, 0, szPath, &length);

		GamePath = szPath;
		WriteConfig(GamePath, *defaultFPS);

		HWND hwnd = nullptr;
		while (!(hwnd = FindWindowA("UnityWndClass", nullptr)))
			std::this_thread::sleep_for(std::chrono::milliseconds(200));

		DWORD ExitCode = STILL_ACTIVE;
		while (ExitCode == STILL_ACTIVE)
		{
			SendMessageA(hwnd, WM_CLOSE, 0, 0);
			GetExitCodeProcess(hProcess, &ExitCode);
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}

		// wait for the game to close then continue
		WaitForSingleObject(hProcess, -1);
		CloseHandle(hProcess);

		system("cls");
		return;
	}

	GamePath = reader.Get("Setting", "Path", "");
	*defaultFPS = reader.GetInteger("Setting", "FPS", *defaultFPS);

	if (GetFileAttributesA(GamePath.c_str()) == INVALID_FILE_ATTRIBUTES)
	{
		printf("Looks like you've moved your game somewhere else - Lets setup again\n");
		SendNotification(*hWnd, "Missing the game", "Looks like you've moved your game somewhere else\nLets setup again");
		DeleteFileA("config.ini");
		LoadConfig(defaultFPS, hWnd);
	}
}

void InjectReshade(HANDLE hProcess)
{
	std::string buffer;
	buffer.reserve(GetCurrentDirectoryA(0, nullptr));
	ZeroMemory(buffer.data(), buffer.capacity());
	GetCurrentDirectoryA(buffer.capacity(), buffer.data());

	std::string DLLPath = buffer.c_str() + std::string("\\ReShade64.dll");
	if (GetFileAttributesA(DLLPath.c_str()) == INVALID_FILE_ATTRIBUTES)
		return;

	printf("\nReShade found\n");
	printf("Injecting ReShade...\n");

	LPVOID pPath = VirtualAllocEx(hProcess, nullptr, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!pPath)
	{
		DWORD code = GetLastError();
		printf("VirtualAllocEx failed (%d): %s\n", code, GetLastErrorAsString(code).c_str());
		return;
	}

	WriteProcessMemory(hProcess, pPath, DLLPath.data(), DLLPath.length(), nullptr);

	HANDLE hThread = CreateRemoteThread(hProcess, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, pPath, 0, nullptr);
	if (!hThread)
	{
		DWORD code = GetLastError();
		printf("CreateRemoteThread failed (%d): %s\n", code, GetLastErrorAsString(code).c_str());
		return;
	}

	WaitForSingleObject(hThread, -1);
	VirtualFreeEx(hProcess, pPath, 0, MEM_RELEASE);
	CloseHandle(hThread);

	printf("ReShade loaded\n\n");
}

DWORD __stdcall _main(LPVOID p)
{
	if (!p)
		return 0;

	thread_arg* targ = (thread_arg*)p;

	SetConsoleTitleA("");

	std::string CommandLine{};

	LoadConfig(&targ->TargetFPS, &targ->hWnd);
	SelectedFPS = targ->TargetFPS;

	// Check menu
	std::vector<int>::iterator itr;
	itr = std::find(FPSEntry.begin(), FPSEntry.end(), SelectedFPS);
	if (itr != FPSEntry.end())
	{
		const int index = std::distance(FPSEntry.begin(), itr);
		CheckMenuRadioItem(hTaskTrayMenu, ID_240, ID_60, FPSEntryID[index], MF_BYCOMMAND); // wtf MF_BYCOMMAND not work
	}

	std::string ProcessPath = GamePath;
	std::string ProcessDir{};

	printf("unlockfps GUI v1.0.0\n");
	printf("Game: %s\n\n", ProcessPath.c_str());
	ProcessDir = ProcessPath.substr(0, ProcessPath.find_last_of("\\"));

	STARTUPINFOA si{};
	PROCESS_INFORMATION pi{};
	if (!CreateProcessA(ProcessPath.c_str(), (LPSTR)CommandLine.c_str(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi))
	{
		DWORD code = GetLastError();
		printf("CreateProcess failed (%d): %s\n", code, GetLastErrorAsString(code).c_str());
		return 0;
	}

	CloseHandle(pi.hThread);
	printf("PID: %d\n", pi.dwProcessId);

	MODULEENTRY32 hUnityPlayer{};
	while (!GetModule(pi.dwProcessId, "UnityPlayer.dll", &hUnityPlayer))
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	InjectReshade(pi.hProcess);

	printf("UnityPlayer: %X%X\n", (uintptr_t)hUnityPlayer.modBaseAddr >> 32 & -1, hUnityPlayer.modBaseAddr);

	LPVOID mem = VirtualAlloc(nullptr, hUnityPlayer.modBaseSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!mem)
	{
		DWORD code = GetLastError();
		printf("VirtualAlloc failed (%d): %s\n", code, GetLastErrorAsString(code).c_str());
		return 0;
	}

	ReadProcessMemory(pi.hProcess, hUnityPlayer.modBaseAddr, mem, hUnityPlayer.modBaseSize, nullptr);

	printf("Searching for pattern...\n");
	/*
		 7F 0F              jg   0x11
		 8B 05 ? ? ? ?      mov eax, dword ptr[rip+?]
	*/
	uintptr_t address = PatternScan(mem, "7F 0F 8B 05 ? ? ? ?");
	if (!address)
	{
		printf("outdated pattern\n");
		return 0;
	}

	// calculate the offset to where the fps value is stored
	uintptr_t pfps = 0;
	{
		uintptr_t rip = address + 2;
		uint32_t rel = *(uint32_t*)(rip + 2);
		pfps = rip + rel + 6;
		pfps -= (uintptr_t)mem;
		printf("FPS Offset: %X\n", pfps);
		pfps = (uintptr_t)hUnityPlayer.modBaseAddr + pfps;
	}

	// calculate where vsync value is stored
	address = PatternScan(mem, "E8 ? ? ? ? 8B E8 49 8B 1E");
	uintptr_t pvsync = 0;
	if (address)
	{
		uintptr_t ppvsync = 0;
		uintptr_t rip = address;
		int32_t rel = *(int32_t*)(rip + 1);
		rip = rip + rel + 5;
		uint64_t rax = *(uint32_t*)(rip + 3);
		ppvsync = rip + rax + 7;
		ppvsync -= (uintptr_t)mem;
		printf("VSync Offset: %X\n", ppvsync);
		ppvsync = (uintptr_t)hUnityPlayer.modBaseAddr + ppvsync;

		uintptr_t buffer = 0;
		while (!buffer)
		{
			ReadProcessMemory(pi.hProcess, (LPCVOID)ppvsync, &buffer, sizeof(buffer), nullptr);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		rip += 7;
		pvsync = *(uint32_t*)(rip + 2);
		pvsync = buffer + pvsync;
	}

	VirtualFree(mem, 0, MEM_RELEASE);
	printf("Done\n\n");


	DWORD ExitCode = STILL_ACTIVE;
	while (ExitCode == STILL_ACTIVE)
	{
		GetExitCodeProcess(pi.hProcess, &ExitCode);
		// runs a check every 2 seconds
		std::this_thread::sleep_for(std::chrono::seconds(2));
		int fps = 0;
		ReadProcessMemory(pi.hProcess, (LPVOID)pfps, &fps, sizeof(fps), nullptr);
		if (fps == -1)
			continue;
		if (SelectedFPS != targ->TargetFPS)
		{
			targ->TargetFPS = SelectedFPS;
			WriteConfig(GamePath, SelectedFPS);
		}
		if (fps != targ->TargetFPS)
		{
			WriteProcessMemory(pi.hProcess, (LPVOID)pfps, &targ->TargetFPS, sizeof(targ->TargetFPS), nullptr);
			TCHAR msg[64];
			wsprintf(msg, TEXT("unlockfps - %d FPS"), targ->TargetFPS);
			UpdateSystemTrayIcon(targ->hWnd, msg);
		}

		int vsync = 0;
		ReadProcessMemory(pi.hProcess, (LPVOID)pvsync, &vsync, sizeof(vsync), nullptr);
		if (vsync)
		{
			vsync = 0;
			// disable vsync
			WriteProcessMemory(pi.hProcess, (LPVOID)pvsync, &vsync, sizeof(vsync), nullptr);
		}
	}

	CloseHandle(pi.hProcess);
	TerminateProcess((HANDLE)-1, 0);

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wcl;

	hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	hTaskTrayMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

	wcl.cbSize = sizeof(WNDCLASSEX);
	wcl.hInstance = hInstance;
	wcl.lpszClassName = WND_CLASS_NAME;
	wcl.lpfnWndProc = WindowProc;
	wcl.style = NULL;
	wcl.hIcon = hIcon;
	wcl.hIconSm = NULL;
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.lpszMenuName = NULL;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	if (!RegisterClassEx(&wcl)) {
		return FALSE;
	}

	hWnd = CreateWindowEx(
		NULL,
		WND_CLASS_NAME,
		TEXT("unlockfps"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd) {
		return FALSE;
	}

	thread_arg targ = {
		hWnd,
		144
	};

	ShowWindow(hWnd, SW_HIDE);
	AddSystemTrayIcon(hWnd);

	// main thread
	HANDLE hThread = CreateThread(nullptr, 0, _main, &targ, 0, nullptr);

	MSG msg;
	BOOL bRet;
	DWORD dwExitCode;

	GetExitCodeThread(hThread, &dwExitCode);

	while ((bRet = GetMessage(&msg, hWnd, 0, 0)) != 0 || dwExitCode == STILL_ACTIVE) {
		if (bRet == -1) {
			break;
		}
		else {
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam) {

	switch (uMsg) {
		break;
		case WM_TASKTRAY:
		{
			switch (lParam)
			{
			case WM_RBUTTONUP:
			{
				if (hTaskTrayMenu)
				{
					// GetSubMenu 0
					HMENU hTrayIconSubMenu = GetSubMenu(hTaskTrayMenu, 0);
					if (hTrayIconSubMenu)
					{
						// clicked position
						POINT pos;
						GetCursorPos(&pos);

						SetForegroundWindow(hWnd);

						// to close menu
						SetFocus(hWnd);
						TrackPopupMenu(hTrayIconSubMenu, TPM_LEFTALIGN | TPM_BOTTOMALIGN,
							pos.x, pos.y, 0, hWnd, NULL
						);
					}
				}
			}
			break;
			}
		}
		break;
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Selected menu entry
			switch (wmId)
			{
			case ID_240:
				CheckMenuRadioItem(hTaskTrayMenu, ID_240, ID_60, wmId, MF_BYCOMMAND);
				SelectedFPS = 240;
				break;
			case ID_200:
				CheckMenuRadioItem(hTaskTrayMenu, ID_240, ID_60, wmId, MF_BYCOMMAND);
				SelectedFPS = 200;
				break;
			case ID_144:
				CheckMenuRadioItem(hTaskTrayMenu, ID_240, ID_60, wmId, MF_BYCOMMAND);
				SelectedFPS = 144;
				break;
			case ID_90:
				CheckMenuRadioItem(hTaskTrayMenu, ID_240, ID_60, wmId, MF_BYCOMMAND);
				SelectedFPS = 90;
				break;
			case ID_60:
				CheckMenuRadioItem(hTaskTrayMenu, ID_240, ID_60, wmId, MF_BYCOMMAND);
				SelectedFPS = 60;
				break;
			case ID_ABOUT:
				ShellAbout(hWnd, "unlockfps gui", "v1.0.1", hIcon);
				break;
			case ID_QUIT:
				DestroyWindow(hWnd);
				break;
			}
			break;
		}
		case WM_DESTROY:
		{
			DeleteSystemTrayIcon(hWnd);
			::PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}