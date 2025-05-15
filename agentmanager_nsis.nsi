# define the name of the installer
Outfile "AgentManager.exe"
Icon "AgentManager\health.ico"

InstallDir $TEMP\AgentManagerSetup

AutoCloseWindow true

# default section
Section

HideWindow

SetOutPath $INSTDIR

File /r AgentManagerSetup\Release\*.*
nsExec::Exec "$INSTDIR\setup.exe"

RMDir /r "$INSTDIR"

SectionEnd
