# Microsoft Developer Studio Project File - Name="glpool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=glpool - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "glpool.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "glpool.mak" CFG="glpool - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "glpool - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "glpool - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "glpool - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "." /I ".." /I "..\GL" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 libcd.lib libcid.lib kernel32.lib opengl32.lib glu32.lib glut32.lib glpng.lib /nologo /subsystem:console /machine:I386 /out:"..\glpool.exe" /libpath:"GL" /libpath:"..\GL"

!ELSEIF  "$(CFG)" == "glpool - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "..\GL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libcd.lib libcid.lib kernel32.lib opengl32.lib glu32.lib glut32.lib glpng.lib /nologo /subsystem:console /debug /machine:I386 /out:"..\glpool.exe" /pdbtype:sept /libpath:"..\GL"
# SUBTRACT LINK32 /map /nodefaultlib

!ENDIF 

# Begin Target

# Name "glpool - Win32 Release"
# Name "glpool - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\cAudio.cpp
# End Source File
# Begin Source File

SOURCE=..\cBall.cpp
# End Source File
# Begin Source File

SOURCE=..\cBallList.cpp
# End Source File
# Begin Source File

SOURCE=..\cTable.cpp
# End Source File
# Begin Source File

SOURCE=..\cTexMaps.cpp
# End Source File
# Begin Source File

SOURCE=..\cVmain.cpp
# End Source File
# Begin Source File

SOURCE=..\cVstatus.cpp
# End Source File
# Begin Source File

SOURCE=..\cWMain.cpp
# End Source File
# Begin Source File

SOURCE=..\glcViewport.cpp
# End Source File
# Begin Source File

SOURCE=..\glcWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\glm.cpp
# End Source File
# Begin Source File

SOURCE=..\GLPOOL.cpp
# End Source File
# Begin Source File

SOURCE=..\glUtil.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\cAudio.h
# End Source File
# Begin Source File

SOURCE=..\cBall.h
# End Source File
# Begin Source File

SOURCE=..\cBallList.h
# End Source File
# Begin Source File

SOURCE=..\Colors.h
# End Source File
# Begin Source File

SOURCE=..\Common.h
# End Source File
# Begin Source File

SOURCE=..\cTable.h
# End Source File
# Begin Source File

SOURCE=..\cTexMaps.h
# End Source File
# Begin Source File

SOURCE=..\Cuestick.h
# End Source File
# Begin Source File

SOURCE=..\cVmain.h
# End Source File
# Begin Source File

SOURCE=..\cVstatus.h
# End Source File
# Begin Source File

SOURCE=..\cWMain.h
# End Source File
# Begin Source File

SOURCE=..\glcViewport.h
# End Source File
# Begin Source File

SOURCE=..\glcWindow.h
# End Source File
# Begin Source File

SOURCE=..\Glm.h
# End Source File
# Begin Source File

SOURCE=..\Glpng.h
# End Source File
# Begin Source File

SOURCE=..\Glpool.h
# End Source File
# Begin Source File

SOURCE=..\glUtil.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
