# Microsoft Developer Studio Project File - Name="DesktopToolbox" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DesktopToolbox - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DesktopToolbox.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DesktopToolbox.mak" CFG="DesktopToolbox - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DesktopToolbox - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "DesktopToolbox - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "DesktopToolbox - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "DesktopToolbox - Win32 Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE "DesktopToolbox - Win32 Unicode Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "DesktopToolbox - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DesktopToolbox - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 comctl32.lib Advapi32.lib User32.lib psapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /incremental:no
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Debug\DesktopToolbox.exe
InputPath=.\Debug\DesktopToolbox.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=D:\UPX\upx -f -o .\install\DesktopToolbox.exe  .\debug\DesktopToolbox.exe
# End Special Build Tool

!ELSEIF  "$(CFG)" == "DesktopToolbox - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\DebugU
TargetPath=.\DebugU\DesktopToolbox.exe
InputPath=.\DebugU\DesktopToolbox.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DesktopToolbox - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /Yu"stdafx.h" /FD /D /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 Shell32.lib comctl32.lib Advapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\DesktopToolbox.exe
InputPath=.\ReleaseMinSize\DesktopToolbox.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DesktopToolbox - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /D /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\DesktopToolbox.exe
InputPath=.\ReleaseMinDependency\DesktopToolbox.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DesktopToolbox - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinSize"
# PROP Intermediate_Dir "ReleaseUMinSize"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\DesktopToolbox.exe
InputPath=.\ReleaseUMinSize\DesktopToolbox.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DesktopToolbox - Win32 Unicode Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinDependency"
# PROP BASE Intermediate_Dir "ReleaseUMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinDependency"
# PROP Intermediate_Dir "ReleaseUMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\DesktopToolbox.exe
InputPath=.\ReleaseUMinDependency\DesktopToolbox.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "DesktopToolbox - Win32 Debug"
# Name "DesktopToolbox - Win32 Unicode Debug"
# Name "DesktopToolbox - Win32 Release MinSize"
# Name "DesktopToolbox - Win32 Release MinDependency"
# Name "DesktopToolbox - Win32 Unicode Release MinSize"
# Name "DesktopToolbox - Win32 Unicode Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\About.cpp
# End Source File
# Begin Source File

SOURCE=.\About25.cpp
# End Source File
# Begin Source File

SOURCE=.\AboutModal.cpp
# End Source File
# Begin Source File

SOURCE=.\base64.cpp
# End Source File
# Begin Source File

SOURCE=.\CopyMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\DesktopToolbox.cpp
# End Source File
# Begin Source File

SOURCE=.\DesktopToolbox.idl
# ADD MTL /tlb ".\DesktopToolbox.tlb" /h "DesktopToolbox.h" /iid "DesktopToolbox_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\DesktopToolbox.rc
# End Source File
# Begin Source File

SOURCE=.\Exit.cpp
# End Source File
# Begin Source File

SOURCE=.\ExitModal.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\MainWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\MDragTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuOperation.cpp
# End Source File
# Begin Source File

SOURCE=.\MyMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTooltip.cpp
# End Source File
# Begin Source File

SOURCE=.\NagScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\NLisence.cpp
# End Source File
# Begin Source File

SOURCE=.\omputerID.cpp
# End Source File
# Begin Source File

SOURCE=.\RegisterSave.cpp
# End Source File
# Begin Source File

SOURCE=.\ShareWareMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ToolBox.cpp
# End Source File
# Begin Source File

SOURCE=.\WtlEditBrowserCtrl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\About.h
# End Source File
# Begin Source File

SOURCE=.\About25.h
# End Source File
# Begin Source File

SOURCE=.\AboutModal.h
# End Source File
# Begin Source File

SOURCE=.\base64.h
# End Source File
# Begin Source File

SOURCE=.\CopyMessage.h
# End Source File
# Begin Source File

SOURCE=.\CrsCoolMenu.h
# End Source File
# Begin Source File

SOURCE=.\Exit.h
# End Source File
# Begin Source File

SOURCE=.\ExitModal.h
# End Source File
# Begin Source File

SOURCE=.\InfoMessage.h
# End Source File
# Begin Source File

SOURCE=.\MainWindow.h
# End Source File
# Begin Source File

SOURCE=.\MDragTarget.h
# End Source File
# Begin Source File

SOURCE=.\MenuOperation.h
# End Source File
# Begin Source File

SOURCE=.\MyMenu.h
# End Source File
# Begin Source File

SOURCE=.\MyTooltip.h
# End Source File
# Begin Source File

SOURCE=.\NagScreen.h
# End Source File
# Begin Source File

SOURCE=.\NewLoadLib.h
# End Source File
# Begin Source File

SOURCE=.\NLisence.h
# End Source File
# Begin Source File

SOURCE=.\omputerID.h
# End Source File
# Begin Source File

SOURCE=.\RegisterSave.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ShareWareMessage.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ToolBox.h
# End Source File
# Begin Source File

SOURCE=.\WtlEditBrowserCtrl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\about25.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ATTACHED_DOCUMENT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\close.bmp
# End Source File
# Begin Source File

SOURCE=.\res\close_ON.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DBF_DOC.bmp
# End Source File
# Begin Source File

SOURCE=.\res\delimiter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\desktop_off.bmp
# End Source File
# Begin Source File

SOURCE=.\res\desktop_on.bmp
# End Source File
# Begin Source File

SOURCE=.\DesktopToolbox.rgs
# End Source File
# Begin Source File

SOURCE=.\res\edit_des.ico
# End Source File
# Begin Source File

SOURCE=.\res\EDIT_NAME_BG.bmp
# End Source File
# Begin Source File

SOURCE=.\res\exit1_off.bmp
# End Source File
# Begin Source File

SOURCE=.\res\exit1_on.bmp
# End Source File
# Begin Source File

SOURCE=.\res\exit_mydesktoptoolbox.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Folder.bmp
# End Source File
# Begin Source File

SOURCE=.\res\godeskto2.ico
# End Source File
# Begin Source File

SOURCE=.\res\godesktoWin.ico
# End Source File
# Begin Source File

SOURCE=.\res\H_POINT.CUR
# End Source File
# Begin Source File

SOURCE=.\res\help.bmp
# End Source File
# Begin Source File

SOURCE=.\res\help_b.bmp
# End Source File
# Begin Source File

SOURCE=.\res\help_ON.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hide_box.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HTML_DOC.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_CHECK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_ITEMDEFAULT_N.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_NEXT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDC_NORMAL.CUR
# End Source File
# Begin Source File

SOURCE=.\res\IDC_SELECT.CUR
# End Source File
# Begin Source File

SOURCE=.\res\idr_docu.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_GODESKTOP.ico
# End Source File
# Begin Source File

SOURCE=.\res\iIDB_ITEMDEFAULT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\info_but.bmp
# End Source File
# Begin Source File

SOURCE=.\res\JPG_DOC.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_lock.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_unlock.bmp
# End Source File
# Begin Source File

SOURCE=.\res\left_layaut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\left_screen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MainWindow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MENU_ABOUT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MENU_CONFIGURATION.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MENU_HELP.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MENU_KEY.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MENU_WWW.bmp
# End Source File
# Begin Source File

SOURCE=.\myButton.rgs
# End Source File
# Begin Source File

SOURCE=.\res\myButton.rgs
# End Source File
# Begin Source File

SOURCE=.\res\myFolder.bmp
# End Source File
# Begin Source File

SOURCE=.\res\myFolder_open.bmp
# End Source File
# Begin Source File

SOURCE=.\res\myFolderEmpty.bmp
# End Source File
# Begin Source File

SOURCE=.\res\nag_screen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\NORMAL01.CUR
# End Source File
# Begin Source File

SOURCE=.\res\ok_of.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ok_on.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PDF_DOC.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PPT_DOC.bmp
# End Source File
# Begin Source File

SOURCE=.\res\right_layaut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\right_screen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_selected.bmp
# End Source File
# Begin Source File

SOURCE=.\res\script_off.bmp
# End Source File
# Begin Source File

SOURCE=.\res\script_on.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SELECT.CUR
# End Source File
# Begin Source File

SOURCE=.\res\setup.ico
# End Source File
# Begin Source File

SOURCE=.\res\SHORTCUT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SHORTCUT_DESKTOP.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SHORTCUT_DESKTOP_EMPTY.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SHORTCUT_URL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\show_box.bmp
# End Source File
# Begin Source File

SOURCE=.\res\task_about.ico
# End Source File
# Begin Source File

SOURCE=.\res\task_ico_l.ico
# End Source File
# Begin Source File

SOURCE=.\res\task_start.ico
# End Source File
# Begin Source File

SOURCE=.\res\TaskIcon.ico
# End Source File
# Begin Source File

SOURCE=.\res\TASKICON_N.ico
# End Source File
# Begin Source File

SOURCE=.\res\TITLE_copy_to.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TITLE_EXPIRED.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TITLE_purchase.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_off.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_on.bmp
# End Source File
# Begin Source File

SOURCE=.\res\top_layaut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\top_screen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\trial_key_lock.bmp
# End Source File
# Begin Source File

SOURCE=.\res\trial_key_unlock.bmp
# End Source File
# Begin Source File

SOURCE=.\res\trying.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TXT_DOC.bmp
# End Source File
# Begin Source File

SOURCE=.\res\web_link.bmp
# End Source File
# Begin Source File

SOURCE=.\res\web_link_off.bmp
# End Source File
# Begin Source File

SOURCE=.\res\web_link_ON.bmp
# End Source File
# Begin Source File

SOURCE=.\res\web_note_off.bmp
# End Source File
# Begin Source File

SOURCE=.\res\web_note_on.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WINDOWS_DESKTOP.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WORD_DOCUMENT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\write_tools_off.bmp
# End Source File
# Begin Source File

SOURCE=.\res\write_tools_on.bmp
# End Source File
# Begin Source File

SOURCE=.\res\XLS_DOC.bmp
# End Source File
# End Group
# End Target
# End Project
# Section DesktopToolbox : {1EA89455-D85C-427C-A335-3468D836E254}
# 	1:8:IDD_EXIT:105
# 	2:16:Resource Include:resource.h
# 	2:6:Exit.h:Exit.h
# 	2:12:CLASS: CExit:CExit
# 	2:8:IDD_EXIT:IDD_EXIT
# 	2:8:Exit.cpp:Exit.cpp
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:desktoptoolbox.h
# End Section
# Section DesktopToolbox : {00000000-0000-0000-0000-800000800000}
# 	1:15:IDD_INFOMESSAGE:112
# End Section
# Section DesktopToolbox : {B3346462-497B-4CAA-ADCB-BD336182AB35}
# 	1:11:IDD_ABOUT25:110
# 	2:16:Resource Include:resource.h
# 	2:10:ENUM: enum:enum
# 	2:15:CLASS: CAbout25:CAbout25
# 	2:19:Application Include:DesktopToolbox.h
# 	2:9:About25.h:About25.h
# 	2:11:IDD_ABOUT25:IDD_ABOUT25
# 	2:11:About25.cpp:About25.cpp
# End Section
# Section DesktopToolbox : {ECD73F77-5AD0-472E-94F7-5715B21FF75A}
# 	2:26:CLASS: CWtlEditBrowserCtrl:CWtlEditBrowserCtrl
# 	2:20:WtlEditBrowserCtrl.h:WtlEditBrowserCtrl.h
# 	2:22:WtlEditBrowserCtrl.cpp:WtlEditBrowserCtrl.cpp
# 	2:19:Application Include:DesktopToolbox.h
# End Section
