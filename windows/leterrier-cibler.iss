; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{9AF1C48C-90D5-48EA-AF9B-9CEE541519C8}
AppName=Le Terrier d'AbulEdu - Le Nombre Cible
AppVersion=LAVERSION
AppPublisher=RyXéo SARL
AppPublisherURL=http://www.abuledu.org/leterrier/leterrier-cibler
AppSupportURL=http://www.abuledu.org/leterrier/leterrier-cibler
AppUpdatesURL=http://www.abuledu.org/leterrier/leterrier-cibler
DefaultDirName={pf}\AbulEdu\Cibler
DefaultGroupName=Le Terrier d'AbulEdu
LicenseFile=..\gpl-2.0.txt
OutputDir=.
OutputBaseFilename=leterrier-cibler-LAVERSION-setup
SetupIconFile=leterrier-cibler.ico
Compression=lzma
SolidCompression=yes
; WizardImageFile=imageWizard.bmp
SignTool=ryxeo /d $qPackage d'installation$q $f
SignedUninstaller=True
SignedUninstallerDir=.

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\release\leterrier-cibler.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\debian\*.desktop"; DestDir: "{app}"; Flags: ignoreversion
Source: "leterrier-cibler.ico"; DestDir: "{app}\"
Source: "..\release\leterrier-cibler.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\data\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/code/quazip.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:/code/exiv2/bin/libexiv2-12.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:/QtSDK/mingw/bin/libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/mingw/bin/mingwm10.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/mingw/bin/libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/bin/libeay32.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/bin/libssl32.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/bin/ssleay32.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/bin/QtScript4.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/bin/QtNetwork4.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/bin/QtGUI4.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/bin/QtSQL4.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/bin/QtSVG4.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/bin/QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/bin/QtXml4.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/bin/QtWebKit4.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/plugins\imageformats/qgif4.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/plugins\imageformats/qico4.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/plugins\imageformats/qjpeg4.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/plugins\imageformats/qmng4.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/plugins\imageformats/qsvg4.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/plugins\imageformats/qtiff4.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/bin/QtMultimedia4.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/plugins/phonon_backend\phonon_ds94.dll"; DestDir: "{app}\phonon_backend"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:/QtSDK/Desktop/Qt/4.8.1/mingw/bin/phonon4.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; pour alacarte > 1.0.8
Source: "..\debian\*.desktop"; DestDir: "{win}\abuledu-alacarte\data\profile1.applications"; AfterInstall: UpdateDesktopPath; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\data\icones\leterrier-cibler-256.png"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
; Name: "{group}\Cibler"; Filename: "{app}\leterrier-cibler.exe"; WorkingDir: "{app}"
; Name: "{commondesktop}\Cibler"; Filename: "{app}\leterrier-cibler.exe"; Tasks: desktopicon; WorkingDir: "{app}"

[Run]
; Filename: "{app}\leterrier-cibler.exe"; Description: "{cm:LaunchProgram,Cibler}"; Flags: nowait postinstall skipifsilent

[Code]
procedure UpdateDesktopPath();
var Strings : TArrayOfString;
begin
  SetArrayLength(Strings, 1);
  Strings[0] := 'X-Horizon-WindowsExecPath=' + ExpandConstant('{app}');

  SaveStringsToFile(ExpandConstant('{win}') + '\abuledu-alacarte\data\profile1.applications\leterrier-cibler.desktop', Strings, True);
end;
