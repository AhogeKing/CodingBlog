# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/xavier/Documents/compiler/frontend_new

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/xavier/Documents/compiler/frontend_new/build

# Include any dependencies generated for this target.
include CMakeFiles/output.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/output.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/output.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/output.dir/flags.make

CMakeFiles/output.dir/codegen:
.PHONY : CMakeFiles/output.dir/codegen

CMakeFiles/output.dir/src/lexcial.cpp.o: CMakeFiles/output.dir/flags.make
CMakeFiles/output.dir/src/lexcial.cpp.o: /Users/xavier/Documents/compiler/frontend_new/src/lexcial.cpp
CMakeFiles/output.dir/src/lexcial.cpp.o: CMakeFiles/output.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/xavier/Documents/compiler/frontend_new/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/output.dir/src/lexcial.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/output.dir/src/lexcial.cpp.o -MF CMakeFiles/output.dir/src/lexcial.cpp.o.d -o CMakeFiles/output.dir/src/lexcial.cpp.o -c /Users/xavier/Documents/compiler/frontend_new/src/lexcial.cpp

CMakeFiles/output.dir/src/lexcial.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/output.dir/src/lexcial.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/xavier/Documents/compiler/frontend_new/src/lexcial.cpp > CMakeFiles/output.dir/src/lexcial.cpp.i

CMakeFiles/output.dir/src/lexcial.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/output.dir/src/lexcial.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/xavier/Documents/compiler/frontend_new/src/lexcial.cpp -o CMakeFiles/output.dir/src/lexcial.cpp.s

CMakeFiles/output.dir/src/main.cpp.o: CMakeFiles/output.dir/flags.make
CMakeFiles/output.dir/src/main.cpp.o: /Users/xavier/Documents/compiler/frontend_new/src/main.cpp
CMakeFiles/output.dir/src/main.cpp.o: CMakeFiles/output.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/xavier/Documents/compiler/frontend_new/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/output.dir/src/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/output.dir/src/main.cpp.o -MF CMakeFiles/output.dir/src/main.cpp.o.d -o CMakeFiles/output.dir/src/main.cpp.o -c /Users/xavier/Documents/compiler/frontend_new/src/main.cpp

CMakeFiles/output.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/output.dir/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/xavier/Documents/compiler/frontend_new/src/main.cpp > CMakeFiles/output.dir/src/main.cpp.i

CMakeFiles/output.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/output.dir/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/xavier/Documents/compiler/frontend_new/src/main.cpp -o CMakeFiles/output.dir/src/main.cpp.s

CMakeFiles/output.dir/src/syntax.cpp.o: CMakeFiles/output.dir/flags.make
CMakeFiles/output.dir/src/syntax.cpp.o: /Users/xavier/Documents/compiler/frontend_new/src/syntax.cpp
CMakeFiles/output.dir/src/syntax.cpp.o: CMakeFiles/output.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/xavier/Documents/compiler/frontend_new/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/output.dir/src/syntax.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/output.dir/src/syntax.cpp.o -MF CMakeFiles/output.dir/src/syntax.cpp.o.d -o CMakeFiles/output.dir/src/syntax.cpp.o -c /Users/xavier/Documents/compiler/frontend_new/src/syntax.cpp

CMakeFiles/output.dir/src/syntax.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/output.dir/src/syntax.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/xavier/Documents/compiler/frontend_new/src/syntax.cpp > CMakeFiles/output.dir/src/syntax.cpp.i

CMakeFiles/output.dir/src/syntax.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/output.dir/src/syntax.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/xavier/Documents/compiler/frontend_new/src/syntax.cpp -o CMakeFiles/output.dir/src/syntax.cpp.s

# Object files for target output
output_OBJECTS = \
"CMakeFiles/output.dir/src/lexcial.cpp.o" \
"CMakeFiles/output.dir/src/main.cpp.o" \
"CMakeFiles/output.dir/src/syntax.cpp.o"

# External object files for target output
output_EXTERNAL_OBJECTS =

output: CMakeFiles/output.dir/src/lexcial.cpp.o
output: CMakeFiles/output.dir/src/main.cpp.o
output: CMakeFiles/output.dir/src/syntax.cpp.o
output: CMakeFiles/output.dir/build.make
output: CMakeFiles/output.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/xavier/Documents/compiler/frontend_new/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable output"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/output.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/output.dir/build: output
.PHONY : CMakeFiles/output.dir/build

CMakeFiles/output.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/output.dir/cmake_clean.cmake
.PHONY : CMakeFiles/output.dir/clean

CMakeFiles/output.dir/depend:
	cd /Users/xavier/Documents/compiler/frontend_new/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/xavier/Documents/compiler/frontend_new /Users/xavier/Documents/compiler/frontend_new /Users/xavier/Documents/compiler/frontend_new/build /Users/xavier/Documents/compiler/frontend_new/build /Users/xavier/Documents/compiler/frontend_new/build/CMakeFiles/output.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/output.dir/depend

