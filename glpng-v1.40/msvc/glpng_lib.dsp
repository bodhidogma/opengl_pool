# Microsoft Developer Studio Project File - Name="glpng_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=glpng_lib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "glpng_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "glpng_lib.mak" CFG="glpng_lib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "glpng_lib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "glpng_lib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "glpng_lib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "include" /I "..\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\gl\glpng.lib"

!ELSEIF  "$(CFG)" == "glpng_lib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\gl\glpng.lib"

!ENDIF 

# Begin Target

# Name "glpng_lib - Win32 Release"
# Name "glpng_lib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "png"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\src\png\png.c"
# End Source File
# Begin Source File

SOURCE="..\src\png\png.h"
# End Source File
# Begin Source File

SOURCE="..\src\png\pngconf.h"
# End Source File
# Begin Source File

SOURCE="..\src\png\pngerror.c"
# End Source File
# Begin Source File

SOURCE="..\src\png\pngget.c"
# End Source File
# Begin Source File

SOURCE="..\src\png\pngmem.c"
# End Source File
# Begin Source File

SOURCE="..\src\png\pngpread.c"
# End Source File
# Begin Source File

SOURCE="..\src\png\pngread.c"
# End Source File
# Begin Source File

SOURCE="..\src\png\pngrio.c"
# End Source File
# Begin Source File

SOURCE="..\src\png\pngrtran.c"
# End Source File
# Begin Source File

SOURCE="..\src\png\pngrutil.c"
# End Source File
# Begin Source File

SOURCE="..\src\png\pngset.c"
# End Source File
# Begin Source File

SOURCE="..\src\png\pngtrans.c"
# End Source File
# End Group
# Begin Group "zlib"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\src\zlib\adler32.c"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\crc32.c"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\infblock.c"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\infblock.h"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\infcodes.c"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\infcodes.h"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\inffast.c"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\inffast.h"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\inffixed.h"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\inflate.c"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\inftrees.c"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\inftrees.h"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\infutil.c"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\infutil.h"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\zconf.h"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\zlib.h"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\zutil.c"
# End Source File
# Begin Source File

SOURCE="..\src\zlib\zutil.h"
# End Source File
# End Group
# Begin Source File

SOURCE="..\src\glpng.c"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
