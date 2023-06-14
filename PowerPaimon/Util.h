public class Util {
public:
	static System::String^ GetString(UINT uID) {
		HINSTANCE hInst = GetModuleHandle(NULL);
		TCHAR str[256];

		LoadString(hInst, uID, str, sizeof(str) / sizeof(str[0]));

		return gcnew String(str);
	}
};