Name "Rafkill"

OutFile "rafkill-1.2.2.exe"

InstallDir $PROGRAMFILES\Rafkill

# Page wtf

Section "Rafkill (required)"
	SetOutPath $INSTDIR
	File "..\rafkill.exe"
	File /r "..\gen"
SectionEnd

Section "Start Menu Shortcuts"
	CreateDirectory "$SMPROGRAMS\Games\Rafkill"
	CreateShortCut "$SMPROGRAMS\Games\Rafkill\Uninstall.lnk" "$INSTDIR\uninstall.exe" "$INSTDIR\uninstall.exe" 0
	CreateShortCut "$SMPROGRAMS\Games\Rafkill\Rafkill.lnk" "$INSTDIR\rafkill.exe" "$INSTDIR\rafkill.exe" 0
SectionEnd
