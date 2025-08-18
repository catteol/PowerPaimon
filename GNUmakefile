release : PowerPaimon/bin/ReleaseMin/net8.0-windows/win-x64/publish/PowerPaimon.exe

UnlockerStub/UnlockerStub.dll :
	make -C $(@D)

PowerPaimon/Resources/%.dll : UnlockerStub/%.dll
	cp $^ $@

PowerPaimon/bin/%/net8.0-windows/win-x64/publish/PowerPaimon.exe : PowerPaimon/PowerPaimon.csproj PowerPaimon/Resources/UnlockerStub.dll
	dotnet publish $< -c $* -r win-x64 -f net8.0-windows --self-contained false -p:PublishSingleFile=true -p:PublishReadyToRun=false

clean :
	rm -rf UnlockerStub/UnlockerStub.dll PowerPaimon/Resources/UnlockerStub.dll.dll PowerPaimon/bin