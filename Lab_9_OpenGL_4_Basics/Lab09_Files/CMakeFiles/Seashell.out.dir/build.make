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
CMAKE_SOURCE_DIR = /home/cosc/student/akp41/Documents/COSC363/Lab_9_OpenGL_4_Basics/Lab09_Files

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cosc/student/akp41/Documents/COSC363/Lab_9_OpenGL_4_Basics/Lab09_Files

# Include any dependencies generated for this target.
include CMakeFiles/Seashell.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Seashell.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Seashell.out.dir/flags.make

CMakeFiles/Seashell.out.dir/Seashell.cpp.o: CMakeFiles/Seashell.out.dir/flags.make
CMakeFiles/Seashell.out.dir/Seashell.cpp.o: Seashell.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cosc/student/akp41/Documents/COSC363/Lab_9_OpenGL_4_Basics/Lab09_Files/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Seashell.out.dir/Seashell.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Seashell.out.dir/Seashell.cpp.o -c /home/cosc/student/akp41/Documents/COSC363/Lab_9_OpenGL_4_Basics/Lab09_Files/Seashell.cpp

CMakeFiles/Seashell.out.dir/Seashell.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Seashell.out.dir/Seashell.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cosc/student/akp41/Documents/COSC363/Lab_9_OpenGL_4_Basics/Lab09_Files/Seashell.cpp > CMakeFiles/Seashell.out.dir/Seashell.cpp.i

CMakeFiles/Seashell.out.dir/Seashell.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Seashell.out.dir/Seashell.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cosc/student/akp41/Documents/COSC363/Lab_9_OpenGL_4_Basics/Lab09_Files/Seashell.cpp -o CMakeFiles/Seashell.out.dir/Seashell.cpp.s

# Object files for target Seashell.out
Seashell_out_OBJECTS = \
"CMakeFiles/Seashell.out.dir/Seashell.cpp.o"

# External object files for target Seashell.out
Seashell_out_EXTERNAL_OBJECTS =

Seashell.out: CMakeFiles/Seashell.out.dir/Seashell.cpp.o
Seashell.out: CMakeFiles/Seashell.out.dir/build.make
Seashell.out: /usr/lib/x86_64-linux-gnu/libGL.so
Seashell.out: /usr/lib/x86_64-linux-gnu/libGLU.so
Seashell.out: /usr/lib/x86_64-linux-gnu/libglut.so
Seashell.out: /usr/lib/x86_64-linux-gnu/libXi.so
Seashell.out: /usr/lib/x86_64-linux-gnu/libGLEW.so
Seashell.out: CMakeFiles/Seashell.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cosc/student/akp41/Documents/COSC363/Lab_9_OpenGL_4_Basics/Lab09_Files/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Seashell.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Seashell.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Seashell.out.dir/build: Seashell.out

.PHONY : CMakeFiles/Seashell.out.dir/build

CMakeFiles/Seashell.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Seashell.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Seashell.out.dir/clean

CMakeFiles/Seashell.out.dir/depend:
	cd /home/cosc/student/akp41/Documents/COSC363/Lab_9_OpenGL_4_Basics/Lab09_Files && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cosc/student/akp41/Documents/COSC363/Lab_9_OpenGL_4_Basics/Lab09_Files /home/cosc/student/akp41/Documents/COSC363/Lab_9_OpenGL_4_Basics/Lab09_Files /home/cosc/student/akp41/Documents/COSC363/Lab_9_OpenGL_4_Basics/Lab09_Files /home/cosc/student/akp41/Documents/COSC363/Lab_9_OpenGL_4_Basics/Lab09_Files /home/cosc/student/akp41/Documents/COSC363/Lab_9_OpenGL_4_Basics/Lab09_Files/CMakeFiles/Seashell.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Seashell.out.dir/depend
