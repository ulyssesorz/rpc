# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /usr/bin/cmake3

# The command to remove a file.
RM = /usr/bin/cmake3 -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/rpc/example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/rpc/example/build

# Include any dependencies generated for this target.
include caller/CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include caller/CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include caller/CMakeFiles/client.dir/flags.make

caller/CMakeFiles/client.dir/CallUserService.o: caller/CMakeFiles/client.dir/flags.make
caller/CMakeFiles/client.dir/CallUserService.o: ../caller/CallUserService.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/rpc/example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object caller/CMakeFiles/client.dir/CallUserService.o"
	cd /root/rpc/example/build/caller && /opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/CallUserService.o -c /root/rpc/example/caller/CallUserService.cpp

caller/CMakeFiles/client.dir/CallUserService.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/CallUserService.i"
	cd /root/rpc/example/build/caller && /opt/rh/devtoolset-7/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/rpc/example/caller/CallUserService.cpp > CMakeFiles/client.dir/CallUserService.i

caller/CMakeFiles/client.dir/CallUserService.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/CallUserService.s"
	cd /root/rpc/example/build/caller && /opt/rh/devtoolset-7/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/rpc/example/caller/CallUserService.cpp -o CMakeFiles/client.dir/CallUserService.s

caller/CMakeFiles/client.dir/__/src/User.pb.o: caller/CMakeFiles/client.dir/flags.make
caller/CMakeFiles/client.dir/__/src/User.pb.o: ../src/User.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/rpc/example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object caller/CMakeFiles/client.dir/__/src/User.pb.o"
	cd /root/rpc/example/build/caller && /opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/__/src/User.pb.o -c /root/rpc/example/src/User.pb.cc

caller/CMakeFiles/client.dir/__/src/User.pb.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/__/src/User.pb.i"
	cd /root/rpc/example/build/caller && /opt/rh/devtoolset-7/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/rpc/example/src/User.pb.cc > CMakeFiles/client.dir/__/src/User.pb.i

caller/CMakeFiles/client.dir/__/src/User.pb.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/__/src/User.pb.s"
	cd /root/rpc/example/build/caller && /opt/rh/devtoolset-7/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/rpc/example/src/User.pb.cc -o CMakeFiles/client.dir/__/src/User.pb.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/CallUserService.o" \
"CMakeFiles/client.dir/__/src/User.pb.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

caller/client: caller/CMakeFiles/client.dir/CallUserService.o
caller/client: caller/CMakeFiles/client.dir/__/src/User.pb.o
caller/client: caller/CMakeFiles/client.dir/build.make
caller/client: caller/CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/rpc/example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable client"
	cd /root/rpc/example/build/caller && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
caller/CMakeFiles/client.dir/build: caller/client

.PHONY : caller/CMakeFiles/client.dir/build

caller/CMakeFiles/client.dir/clean:
	cd /root/rpc/example/build/caller && $(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : caller/CMakeFiles/client.dir/clean

caller/CMakeFiles/client.dir/depend:
	cd /root/rpc/example/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/rpc/example /root/rpc/example/caller /root/rpc/example/build /root/rpc/example/build/caller /root/rpc/example/build/caller/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : caller/CMakeFiles/client.dir/depend
