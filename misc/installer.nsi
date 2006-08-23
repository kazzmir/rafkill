Name "Rafkill"

OutFile "rafkill-1.2.2.exe"

InstallDir $PROGRAMFILES\Rafkill

Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

Section "Rafkill (required)"
	SetOutPath $INSTDIR
	File "..\rafkill.exe"
	File "c:\WINDOWS\system32\alleg42.dll"
	File "c:\WINDOWS\system32\pthreadGC2.dll"
	File /r "..\gen"
	WriteUninstaller "uninstall.exe"
SectionEnd

Section "Start Menu Shortcuts"
	CreateDirectory "$SMPROGRAMS\Games\Rafkill"
	CreateShortCut "$SMPROGRAMS\Games\Rafkill\Uninstall.lnk" "$INSTDIR\uninstall.exe" "$INSTDIR\uninstall.exe" 0
	CreateShortCut "$SMPROGRAMS\Games\Rafkill\Rafkill.lnk" "$INSTDIR\rafkill.exe" "$INSTDIR\rafkill.exe" 0
SectionEnd

Section "Uninstall"
	RMDIR /r "$SMPROGRAMS\Games\Rafkill"
	RMDIR /r "$INSTDIR"
SectionEnd
