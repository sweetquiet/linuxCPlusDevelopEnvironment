# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/Desktop/CPlusSourceCode/RedisNSERVER

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/Desktop/CPlusSourceCode/RedisNSERVER/build

# Include any dependencies generated for this target.
include src/CMakeFiles/nserver-mysql-redis.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/nserver-mysql-redis.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/nserver-mysql-redis.dir/flags.make

src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o: src/CMakeFiles/nserver-mysql-redis.dir/flags.make
src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o: ../src/mysqlclient.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/Desktop/CPlusSourceCode/RedisNSERVER/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o"
	cd /root/Desktop/CPlusSourceCode/RedisNSERVER/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o   -c /root/Desktop/CPlusSourceCode/RedisNSERVER/src/mysqlclient.c

src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.i"
	cd /root/Desktop/CPlusSourceCode/RedisNSERVER/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /root/Desktop/CPlusSourceCode/RedisNSERVER/src/mysqlclient.c > CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.i

src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.s"
	cd /root/Desktop/CPlusSourceCode/RedisNSERVER/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /root/Desktop/CPlusSourceCode/RedisNSERVER/src/mysqlclient.c -o CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.s

src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o.requires:
.PHONY : src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o.requires

src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o.provides: src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o.requires
	$(MAKE) -f src/CMakeFiles/nserver-mysql-redis.dir/build.make src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o.provides.build
.PHONY : src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o.provides

src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o.provides.build: src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o

src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o: src/CMakeFiles/nserver-mysql-redis.dir/flags.make
src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o: ../src/redisclient.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/Desktop/CPlusSourceCode/RedisNSERVER/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o"
	cd /root/Desktop/CPlusSourceCode/RedisNSERVER/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o   -c /root/Desktop/CPlusSourceCode/RedisNSERVER/src/redisclient.c

src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nserver-mysql-redis.dir/redisclient.c.i"
	cd /root/Desktop/CPlusSourceCode/RedisNSERVER/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /root/Desktop/CPlusSourceCode/RedisNSERVER/src/redisclient.c > CMakeFiles/nserver-mysql-redis.dir/redisclient.c.i

src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nserver-mysql-redis.dir/redisclient.c.s"
	cd /root/Desktop/CPlusSourceCode/RedisNSERVER/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /root/Desktop/CPlusSourceCode/RedisNSERVER/src/redisclient.c -o CMakeFiles/nserver-mysql-redis.dir/redisclient.c.s

src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o.requires:
.PHONY : src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o.requires

src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o.provides: src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o.requires
	$(MAKE) -f src/CMakeFiles/nserver-mysql-redis.dir/build.make src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o.provides.build
.PHONY : src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o.provides

src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o.provides.build: src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o

src/CMakeFiles/nserver-mysql-redis.dir/main.c.o: src/CMakeFiles/nserver-mysql-redis.dir/flags.make
src/CMakeFiles/nserver-mysql-redis.dir/main.c.o: ../src/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/Desktop/CPlusSourceCode/RedisNSERVER/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/nserver-mysql-redis.dir/main.c.o"
	cd /root/Desktop/CPlusSourceCode/RedisNSERVER/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/nserver-mysql-redis.dir/main.c.o   -c /root/Desktop/CPlusSourceCode/RedisNSERVER/src/main.c

src/CMakeFiles/nserver-mysql-redis.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nserver-mysql-redis.dir/main.c.i"
	cd /root/Desktop/CPlusSourceCode/RedisNSERVER/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /root/Desktop/CPlusSourceCode/RedisNSERVER/src/main.c > CMakeFiles/nserver-mysql-redis.dir/main.c.i

src/CMakeFiles/nserver-mysql-redis.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nserver-mysql-redis.dir/main.c.s"
	cd /root/Desktop/CPlusSourceCode/RedisNSERVER/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /root/Desktop/CPlusSourceCode/RedisNSERVER/src/main.c -o CMakeFiles/nserver-mysql-redis.dir/main.c.s

src/CMakeFiles/nserver-mysql-redis.dir/main.c.o.requires:
.PHONY : src/CMakeFiles/nserver-mysql-redis.dir/main.c.o.requires

src/CMakeFiles/nserver-mysql-redis.dir/main.c.o.provides: src/CMakeFiles/nserver-mysql-redis.dir/main.c.o.requires
	$(MAKE) -f src/CMakeFiles/nserver-mysql-redis.dir/build.make src/CMakeFiles/nserver-mysql-redis.dir/main.c.o.provides.build
.PHONY : src/CMakeFiles/nserver-mysql-redis.dir/main.c.o.provides

src/CMakeFiles/nserver-mysql-redis.dir/main.c.o.provides.build: src/CMakeFiles/nserver-mysql-redis.dir/main.c.o

# Object files for target nserver-mysql-redis
nserver__mysql__redis_OBJECTS = \
"CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o" \
"CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o" \
"CMakeFiles/nserver-mysql-redis.dir/main.c.o"

# External object files for target nserver-mysql-redis
nserver__mysql__redis_EXTERNAL_OBJECTS =

bin/nserver-mysql-redis: src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o
bin/nserver-mysql-redis: src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o
bin/nserver-mysql-redis: src/CMakeFiles/nserver-mysql-redis.dir/main.c.o
bin/nserver-mysql-redis: src/CMakeFiles/nserver-mysql-redis.dir/build.make
bin/nserver-mysql-redis: src/CMakeFiles/nserver-mysql-redis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/nserver-mysql-redis"
	cd /root/Desktop/CPlusSourceCode/RedisNSERVER/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nserver-mysql-redis.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/nserver-mysql-redis.dir/build: bin/nserver-mysql-redis
.PHONY : src/CMakeFiles/nserver-mysql-redis.dir/build

src/CMakeFiles/nserver-mysql-redis.dir/requires: src/CMakeFiles/nserver-mysql-redis.dir/mysqlclient.c.o.requires
src/CMakeFiles/nserver-mysql-redis.dir/requires: src/CMakeFiles/nserver-mysql-redis.dir/redisclient.c.o.requires
src/CMakeFiles/nserver-mysql-redis.dir/requires: src/CMakeFiles/nserver-mysql-redis.dir/main.c.o.requires
.PHONY : src/CMakeFiles/nserver-mysql-redis.dir/requires

src/CMakeFiles/nserver-mysql-redis.dir/clean:
	cd /root/Desktop/CPlusSourceCode/RedisNSERVER/build/src && $(CMAKE_COMMAND) -P CMakeFiles/nserver-mysql-redis.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/nserver-mysql-redis.dir/clean

src/CMakeFiles/nserver-mysql-redis.dir/depend:
	cd /root/Desktop/CPlusSourceCode/RedisNSERVER/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/Desktop/CPlusSourceCode/RedisNSERVER /root/Desktop/CPlusSourceCode/RedisNSERVER/src /root/Desktop/CPlusSourceCode/RedisNSERVER/build /root/Desktop/CPlusSourceCode/RedisNSERVER/build/src /root/Desktop/CPlusSourceCode/RedisNSERVER/build/src/CMakeFiles/nserver-mysql-redis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/nserver-mysql-redis.dir/depend

