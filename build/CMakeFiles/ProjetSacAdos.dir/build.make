# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/etud/stage/ProjetSacAdos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/etud/stage/ProjetSacAdos/build

# Include any dependencies generated for this target.
include CMakeFiles/ProjetSacAdos.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ProjetSacAdos.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProjetSacAdos.dir/flags.make

CMakeFiles/ProjetSacAdos.dir/src/Test.cpp.o: CMakeFiles/ProjetSacAdos.dir/flags.make
CMakeFiles/ProjetSacAdos.dir/src/Test.cpp.o: ../src/Test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/etud/stage/ProjetSacAdos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ProjetSacAdos.dir/src/Test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetSacAdos.dir/src/Test.cpp.o -c /home/etud/stage/ProjetSacAdos/src/Test.cpp

CMakeFiles/ProjetSacAdos.dir/src/Test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetSacAdos.dir/src/Test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/etud/stage/ProjetSacAdos/src/Test.cpp > CMakeFiles/ProjetSacAdos.dir/src/Test.cpp.i

CMakeFiles/ProjetSacAdos.dir/src/Test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetSacAdos.dir/src/Test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/etud/stage/ProjetSacAdos/src/Test.cpp -o CMakeFiles/ProjetSacAdos.dir/src/Test.cpp.s

CMakeFiles/ProjetSacAdos.dir/src/KpSolver.cpp.o: CMakeFiles/ProjetSacAdos.dir/flags.make
CMakeFiles/ProjetSacAdos.dir/src/KpSolver.cpp.o: ../src/KpSolver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/etud/stage/ProjetSacAdos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ProjetSacAdos.dir/src/KpSolver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetSacAdos.dir/src/KpSolver.cpp.o -c /home/etud/stage/ProjetSacAdos/src/KpSolver.cpp

CMakeFiles/ProjetSacAdos.dir/src/KpSolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetSacAdos.dir/src/KpSolver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/etud/stage/ProjetSacAdos/src/KpSolver.cpp > CMakeFiles/ProjetSacAdos.dir/src/KpSolver.cpp.i

CMakeFiles/ProjetSacAdos.dir/src/KpSolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetSacAdos.dir/src/KpSolver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/etud/stage/ProjetSacAdos/src/KpSolver.cpp -o CMakeFiles/ProjetSacAdos.dir/src/KpSolver.cpp.s

CMakeFiles/ProjetSacAdos.dir/src/KpSolverGreedy.cpp.o: CMakeFiles/ProjetSacAdos.dir/flags.make
CMakeFiles/ProjetSacAdos.dir/src/KpSolverGreedy.cpp.o: ../src/KpSolverGreedy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/etud/stage/ProjetSacAdos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ProjetSacAdos.dir/src/KpSolverGreedy.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetSacAdos.dir/src/KpSolverGreedy.cpp.o -c /home/etud/stage/ProjetSacAdos/src/KpSolverGreedy.cpp

CMakeFiles/ProjetSacAdos.dir/src/KpSolverGreedy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetSacAdos.dir/src/KpSolverGreedy.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/etud/stage/ProjetSacAdos/src/KpSolverGreedy.cpp > CMakeFiles/ProjetSacAdos.dir/src/KpSolverGreedy.cpp.i

CMakeFiles/ProjetSacAdos.dir/src/KpSolverGreedy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetSacAdos.dir/src/KpSolverGreedy.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/etud/stage/ProjetSacAdos/src/KpSolverGreedy.cpp -o CMakeFiles/ProjetSacAdos.dir/src/KpSolverGreedy.cpp.s

CMakeFiles/ProjetSacAdos.dir/src/nodeBB.cpp.o: CMakeFiles/ProjetSacAdos.dir/flags.make
CMakeFiles/ProjetSacAdos.dir/src/nodeBB.cpp.o: ../src/nodeBB.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/etud/stage/ProjetSacAdos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ProjetSacAdos.dir/src/nodeBB.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetSacAdos.dir/src/nodeBB.cpp.o -c /home/etud/stage/ProjetSacAdos/src/nodeBB.cpp

CMakeFiles/ProjetSacAdos.dir/src/nodeBB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetSacAdos.dir/src/nodeBB.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/etud/stage/ProjetSacAdos/src/nodeBB.cpp > CMakeFiles/ProjetSacAdos.dir/src/nodeBB.cpp.i

CMakeFiles/ProjetSacAdos.dir/src/nodeBB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetSacAdos.dir/src/nodeBB.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/etud/stage/ProjetSacAdos/src/nodeBB.cpp -o CMakeFiles/ProjetSacAdos.dir/src/nodeBB.cpp.s

CMakeFiles/ProjetSacAdos.dir/src/KpSolverBB.cpp.o: CMakeFiles/ProjetSacAdos.dir/flags.make
CMakeFiles/ProjetSacAdos.dir/src/KpSolverBB.cpp.o: ../src/KpSolverBB.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/etud/stage/ProjetSacAdos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ProjetSacAdos.dir/src/KpSolverBB.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetSacAdos.dir/src/KpSolverBB.cpp.o -c /home/etud/stage/ProjetSacAdos/src/KpSolverBB.cpp

CMakeFiles/ProjetSacAdos.dir/src/KpSolverBB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetSacAdos.dir/src/KpSolverBB.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/etud/stage/ProjetSacAdos/src/KpSolverBB.cpp > CMakeFiles/ProjetSacAdos.dir/src/KpSolverBB.cpp.i

CMakeFiles/ProjetSacAdos.dir/src/KpSolverBB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetSacAdos.dir/src/KpSolverBB.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/etud/stage/ProjetSacAdos/src/KpSolverBB.cpp -o CMakeFiles/ProjetSacAdos.dir/src/KpSolverBB.cpp.s

CMakeFiles/ProjetSacAdos.dir/src/KpSolverDP.cpp.o: CMakeFiles/ProjetSacAdos.dir/flags.make
CMakeFiles/ProjetSacAdos.dir/src/KpSolverDP.cpp.o: ../src/KpSolverDP.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/etud/stage/ProjetSacAdos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ProjetSacAdos.dir/src/KpSolverDP.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetSacAdos.dir/src/KpSolverDP.cpp.o -c /home/etud/stage/ProjetSacAdos/src/KpSolverDP.cpp

CMakeFiles/ProjetSacAdos.dir/src/KpSolverDP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetSacAdos.dir/src/KpSolverDP.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/etud/stage/ProjetSacAdos/src/KpSolverDP.cpp > CMakeFiles/ProjetSacAdos.dir/src/KpSolverDP.cpp.i

CMakeFiles/ProjetSacAdos.dir/src/KpSolverDP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetSacAdos.dir/src/KpSolverDP.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/etud/stage/ProjetSacAdos/src/KpSolverDP.cpp -o CMakeFiles/ProjetSacAdos.dir/src/KpSolverDP.cpp.s

# Object files for target ProjetSacAdos
ProjetSacAdos_OBJECTS = \
"CMakeFiles/ProjetSacAdos.dir/src/Test.cpp.o" \
"CMakeFiles/ProjetSacAdos.dir/src/KpSolver.cpp.o" \
"CMakeFiles/ProjetSacAdos.dir/src/KpSolverGreedy.cpp.o" \
"CMakeFiles/ProjetSacAdos.dir/src/nodeBB.cpp.o" \
"CMakeFiles/ProjetSacAdos.dir/src/KpSolverBB.cpp.o" \
"CMakeFiles/ProjetSacAdos.dir/src/KpSolverDP.cpp.o"

# External object files for target ProjetSacAdos
ProjetSacAdos_EXTERNAL_OBJECTS =

ProjetSacAdos: CMakeFiles/ProjetSacAdos.dir/src/Test.cpp.o
ProjetSacAdos: CMakeFiles/ProjetSacAdos.dir/src/KpSolver.cpp.o
ProjetSacAdos: CMakeFiles/ProjetSacAdos.dir/src/KpSolverGreedy.cpp.o
ProjetSacAdos: CMakeFiles/ProjetSacAdos.dir/src/nodeBB.cpp.o
ProjetSacAdos: CMakeFiles/ProjetSacAdos.dir/src/KpSolverBB.cpp.o
ProjetSacAdos: CMakeFiles/ProjetSacAdos.dir/src/KpSolverDP.cpp.o
ProjetSacAdos: CMakeFiles/ProjetSacAdos.dir/build.make
ProjetSacAdos: CMakeFiles/ProjetSacAdos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/etud/stage/ProjetSacAdos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ProjetSacAdos"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProjetSacAdos.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProjetSacAdos.dir/build: ProjetSacAdos

.PHONY : CMakeFiles/ProjetSacAdos.dir/build

CMakeFiles/ProjetSacAdos.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProjetSacAdos.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProjetSacAdos.dir/clean

CMakeFiles/ProjetSacAdos.dir/depend:
	cd /home/etud/stage/ProjetSacAdos/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/etud/stage/ProjetSacAdos /home/etud/stage/ProjetSacAdos /home/etud/stage/ProjetSacAdos/build /home/etud/stage/ProjetSacAdos/build /home/etud/stage/ProjetSacAdos/build/CMakeFiles/ProjetSacAdos.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProjetSacAdos.dir/depend

