# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\daruma\bin\.cmake\CMake\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\daruma\bin\.cmake\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\daruma\vscode-source\cpp\test-parse

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\daruma\vscode-source\cpp\test-parse\build

# Include any dependencies generated for this target.
include CMakeFiles/test-parse.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test-parse.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test-parse.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test-parse.dir/flags.make

CMakeFiles/test-parse.dir/src/main.cc.obj: CMakeFiles/test-parse.dir/flags.make
CMakeFiles/test-parse.dir/src/main.cc.obj: C:/Users/daruma/vscode-source/cpp/test-parse/src/main.cc
CMakeFiles/test-parse.dir/src/main.cc.obj: CMakeFiles/test-parse.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\daruma\vscode-source\cpp\test-parse\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test-parse.dir/src/main.cc.obj"
	C:\Users\daruma\bin\.gcc\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test-parse.dir/src/main.cc.obj -MF CMakeFiles\test-parse.dir\src\main.cc.obj.d -o CMakeFiles\test-parse.dir\src\main.cc.obj -c C:\Users\daruma\vscode-source\cpp\test-parse\src\main.cc

CMakeFiles/test-parse.dir/src/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-parse.dir/src/main.cc.i"
	C:\Users\daruma\bin\.gcc\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\daruma\vscode-source\cpp\test-parse\src\main.cc > CMakeFiles\test-parse.dir\src\main.cc.i

CMakeFiles/test-parse.dir/src/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-parse.dir/src/main.cc.s"
	C:\Users\daruma\bin\.gcc\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\daruma\vscode-source\cpp\test-parse\src\main.cc -o CMakeFiles\test-parse.dir\src\main.cc.s

# Object files for target test-parse
test__parse_OBJECTS = \
"CMakeFiles/test-parse.dir/src/main.cc.obj"

# External object files for target test-parse
test__parse_EXTERNAL_OBJECTS =

C:/Users/daruma/vscode-source/cpp/test-parse/bin/test-parse.exe: CMakeFiles/test-parse.dir/src/main.cc.obj
C:/Users/daruma/vscode-source/cpp/test-parse/bin/test-parse.exe: CMakeFiles/test-parse.dir/build.make
C:/Users/daruma/vscode-source/cpp/test-parse/bin/test-parse.exe: CMakeFiles/test-parse.dir/linklibs.rsp
C:/Users/daruma/vscode-source/cpp/test-parse/bin/test-parse.exe: CMakeFiles/test-parse.dir/objects1.rsp
C:/Users/daruma/vscode-source/cpp/test-parse/bin/test-parse.exe: CMakeFiles/test-parse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\daruma\vscode-source\cpp\test-parse\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable C:\Users\daruma\vscode-source\cpp\test-parse\bin\test-parse.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\test-parse.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test-parse.dir/build: C:/Users/daruma/vscode-source/cpp/test-parse/bin/test-parse.exe
.PHONY : CMakeFiles/test-parse.dir/build

CMakeFiles/test-parse.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\test-parse.dir\cmake_clean.cmake
.PHONY : CMakeFiles/test-parse.dir/clean

CMakeFiles/test-parse.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\daruma\vscode-source\cpp\test-parse C:\Users\daruma\vscode-source\cpp\test-parse C:\Users\daruma\vscode-source\cpp\test-parse\build C:\Users\daruma\vscode-source\cpp\test-parse\build C:\Users\daruma\vscode-source\cpp\test-parse\build\CMakeFiles\test-parse.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test-parse.dir/depend

