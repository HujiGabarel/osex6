# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/cmake-build-debug

# Include any dependencies generated for this target.
include tests/CMakeFiles/testRunner.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/testRunner.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/testRunner.dir/flags.make

tests/CMakeFiles/testRunner.dir/SampleClient.cpp.o: tests/CMakeFiles/testRunner.dir/flags.make
tests/CMakeFiles/testRunner.dir/SampleClient.cpp.o: ../tests/SampleClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/testRunner.dir/SampleClient.cpp.o"
	cd /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/cmake-build-debug/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testRunner.dir/SampleClient.cpp.o -c /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/tests/SampleClient.cpp

tests/CMakeFiles/testRunner.dir/SampleClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testRunner.dir/SampleClient.cpp.i"
	cd /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/cmake-build-debug/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/tests/SampleClient.cpp > CMakeFiles/testRunner.dir/SampleClient.cpp.i

tests/CMakeFiles/testRunner.dir/SampleClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testRunner.dir/SampleClient.cpp.s"
	cd /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/cmake-build-debug/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/tests/SampleClient.cpp -o CMakeFiles/testRunner.dir/SampleClient.cpp.s

# Object files for target testRunner
testRunner_OBJECTS = \
"CMakeFiles/testRunner.dir/SampleClient.cpp.o"

# External object files for target testRunner
testRunner_EXTERNAL_OBJECTS =

tests/testRunner: tests/CMakeFiles/testRunner.dir/SampleClient.cpp.o
tests/testRunner: tests/CMakeFiles/testRunner.dir/build.make
tests/testRunner: libMapReduceFramework.a
tests/testRunner: lib/libgtest_main.a
tests/testRunner: lib/libgtest.a
tests/testRunner: tests/CMakeFiles/testRunner.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testRunner"
	cd /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/cmake-build-debug/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testRunner.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/testRunner.dir/build: tests/testRunner

.PHONY : tests/CMakeFiles/testRunner.dir/build

tests/CMakeFiles/testRunner.dir/clean:
	cd /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/cmake-build-debug/tests && $(CMAKE_COMMAND) -P CMakeFiles/testRunner.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/testRunner.dir/clean

tests/CMakeFiles/testRunner.dir/depend:
	cd /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3 /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/tests /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/cmake-build-debug /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/cmake-build-debug/tests /mnt/c/Users/t9058090/Documents/courses/os/ex3/ex3/cmake-build-debug/tests/CMakeFiles/testRunner.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/testRunner.dir/depend

