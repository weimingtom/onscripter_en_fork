# Microsoft Developer Studio Project File - Name="onscripter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=onscripter - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "onscripter.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "onscripter.mak" CFG="onscripter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "onscripter - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "onscripter - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "onscripter - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\extlib\src\bzip2-1.0.4" /I "..\..\..\extlib\src\freetype-2.3.5\include" /I "..\..\..\extlib\src\jpeg-6b" /I "..\jpeg" /I "..\..\..\extlib\src\libogg-1.1.3\include" /I "..\..\..\extlib\src\libpng-1.2.24" /I "..\..\..\extlib\src\libvorbis-1.2.0\include" /I "..\..\..\extlib\src\SDL-1.2.13\include" /I "..\..\..\extlib\src\SDL_image-1.2.6" /I "..\..\..\extlib\src\SDL_mixer-1.2.8" /I "..\..\..\extlib\src\SDL_ttf-2.0.8" /I "..\..\..\extlib\src\smpeg" /I "..\..\..\extlib\src\zlib-1.2.3" /I "..\SDL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "USE_OGG_VORBIS" /D DECLSPEC="" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib dxguid.lib user32.lib gdi32.lib advapi32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "onscripter - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\extlib\src\bzip2-1.0.4" /I "..\..\..\extlib\src\freetype-2.3.5\include" /I "..\..\..\extlib\src\jpeg-6b" /I "..\jpeg" /I "..\..\..\extlib\src\libogg-1.1.3\include" /I "..\..\..\extlib\src\libpng-1.2.24" /I "..\..\..\extlib\src\libvorbis-1.2.0\include" /I "..\..\..\extlib\src\SDL-1.2.13\include" /I "..\..\..\extlib\src\SDL_image-1.2.6" /I "..\..\..\extlib\src\SDL_mixer-1.2.8" /I "..\..\..\extlib\src\SDL_ttf-2.0.8" /I "..\..\..\extlib\src\smpeg" /I "..\..\..\extlib\src\zlib-1.2.3" /I "..\SDL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "USE_OGG_VORBIS" /D DECLSPEC="" /D "USE_GLUT" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib dxguid.lib user32.lib gdi32.lib advapi32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "onscripter - Win32 Release"
# Name "onscripter - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\AnimationInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\AVIWrapper.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\DirectReader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\DirPaths.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\DirtyRect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\embed.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\FontInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\graphics_altivec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\graphics_mmx.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\graphics_sse2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Layer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\LUAHandler.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\MadWrapper.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\NsaReader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\nscriptdecode.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\onscripter.cpp
# End Source File
# Begin Source File

SOURCE=.\onscripter.rc
# End Source File
# Begin Source File

SOURCE=..\..\..\ONScripterLabel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ONScripterLabel_animation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ONScripterLabel_command.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ONScripterLabel_effect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ONScripterLabel_event.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ONScripterLabel_file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ONScripterLabel_file2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ONScripterLabel_image.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ONScripterLabel_rmenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ONScripterLabel_sound.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ONScripterLabel_text.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\resize_image.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\SarReader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ScriptHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ScriptParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ScriptParser_command.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\SDL_win32_main.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\sjis2utf16.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\AnimationInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\AVIWrapper.h
# End Source File
# Begin Source File

SOURCE=..\..\..\BaseReader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DirectReader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DirPaths.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DirtyRect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FontInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\graphics_altivec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\graphics_common.h
# End Source File
# Begin Source File

SOURCE=..\..\..\graphics_mmx.h
# End Source File
# Begin Source File

SOURCE=..\..\..\graphics_sse2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Layer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\LUAHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\MadWrapper.h
# End Source File
# Begin Source File

SOURCE=..\..\..\NsaReader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ONScripterLabel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\resize_image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\resources.h
# End Source File
# Begin Source File

SOURCE=..\..\..\SarReader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ScriptHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ScriptParser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\version.h
# End Source File
# Begin Source File

SOURCE=..\..\..\winres.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\ons-en.ico"
# End Source File
# End Group
# Begin Group "generate"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SDL_win32_main.cpp
# End Source File
# End Group
# Begin Group "test"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\arc.nsa
# End Source File
# Begin Source File

SOURCE=.\default.ttf
# End Source File
# Begin Source File

SOURCE=.\vc6_change.txt
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\BUGS
# End Source File
# Begin Source File

SOURCE=..\..\..\CHANGES
# End Source File
# Begin Source File

SOURCE=..\..\..\config.guess
# End Source File
# Begin Source File

SOURCE=..\..\..\config.sub
# End Source File
# Begin Source File

SOURCE=..\..\..\configure
# End Source File
# Begin Source File

SOURCE=..\..\..\COPYING
# End Source File
# Begin Source File

SOURCE=..\..\..\INSTALL
# End Source File
# Begin Source File

SOURCE="..\..\..\install-sh"
# End Source File
# Begin Source File

SOURCE=..\..\..\Makefile.extlibs
# End Source File
# Begin Source File

SOURCE=..\..\..\Makefile.onscripter
# End Source File
# Begin Source File

SOURCE="..\..\..\ons-en.png"
# End Source File
# Begin Source File

SOURCE=..\..\..\onscripter.rc.in
# End Source File
# Begin Source File

SOURCE=..\..\..\README
# End Source File
# End Target
# End Project
