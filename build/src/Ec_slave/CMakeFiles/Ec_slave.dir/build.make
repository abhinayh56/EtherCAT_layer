# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build

# Include any dependencies generated for this target.
include src/Ec_slave/CMakeFiles/Ec_slave.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/Ec_slave/CMakeFiles/Ec_slave.dir/compiler_depend.make

# Include the progress variables for this target.
include src/Ec_slave/CMakeFiles/Ec_slave.dir/progress.make

# Include the compile flags for this target's objects.
include src/Ec_slave/CMakeFiles/Ec_slave.dir/flags.make

src/Ec_slave/CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/flags.make
src/Ec_slave/CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.o: /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave_base/Ec_slave_base.cpp
src/Ec_slave/CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Ec_slave/CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.o"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Ec_slave/CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.o -MF CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.o.d -o CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.o -c /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave_base/Ec_slave_base.cpp

src/Ec_slave/CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.i"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave_base/Ec_slave_base.cpp > CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.i

src/Ec_slave/CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.s"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave_base/Ec_slave_base.cpp -o CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.s

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/flags.make
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.o: /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_ek_1100.cpp
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.o"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.o -MF CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.o.d -o CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.o -c /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_ek_1100.cpp

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.i"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_ek_1100.cpp > CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.i

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.s"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_ek_1100.cpp -o CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.s

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/flags.make
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.o: /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_ek_1122.cpp
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.o"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.o -MF CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.o.d -o CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.o -c /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_ek_1122.cpp

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.i"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_ek_1122.cpp > CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.i

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.s"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_ek_1122.cpp -o CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.s

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/flags.make
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.o: /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_el_2008.cpp
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.o"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.o -MF CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.o.d -o CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.o -c /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_el_2008.cpp

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.i"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_el_2008.cpp > CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.i

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.s"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_el_2008.cpp -o CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.s

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/flags.make
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.o: /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_el_1008.cpp
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.o"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.o -MF CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.o.d -o CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.o -c /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_el_1008.cpp

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.i"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_el_1008.cpp > CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.i

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.s"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_el_1008.cpp -o CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.s

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/flags.make
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.o: /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_rfid.cpp
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.o"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.o -MF CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.o.d -o CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.o -c /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_rfid.cpp

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.i"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_rfid.cpp > CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.i

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.s"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_rfid.cpp -o CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.s

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/flags.make
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.o: /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_mact.cpp
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.o"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.o -MF CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.o.d -o CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.o -c /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_mact.cpp

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.i"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_mact.cpp > CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.i

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.s"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_mact.cpp -o CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.s

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/flags.make
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.o: /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_mact_2.cpp
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.o"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.o -MF CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.o.d -o CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.o -c /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_mact_2.cpp

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.i"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_mact_2.cpp > CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.i

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.s"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_mact_2.cpp -o CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.s

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/flags.make
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.o: /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_ingenia.cpp
src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.o: src/Ec_slave/CMakeFiles/Ec_slave.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.o"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.o -MF CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.o.d -o CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.o -c /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_ingenia.cpp

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.i"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_ingenia.cpp > CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.i

src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.s"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave/Ec_slave_ingenia.cpp -o CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.s

# Object files for target Ec_slave
Ec_slave_OBJECTS = \
"CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.o" \
"CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.o" \
"CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.o" \
"CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.o" \
"CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.o" \
"CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.o" \
"CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.o" \
"CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.o" \
"CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.o"

# External object files for target Ec_slave
Ec_slave_EXTERNAL_OBJECTS =

src/Ec_slave/libEc_slave.a: src/Ec_slave/CMakeFiles/Ec_slave.dir/__/Ec_slave_base/Ec_slave_base.cpp.o
src/Ec_slave/libEc_slave.a: src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1100.cpp.o
src/Ec_slave/libEc_slave.a: src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ek_1122.cpp.o
src/Ec_slave/libEc_slave.a: src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_2008.cpp.o
src/Ec_slave/libEc_slave.a: src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_el_1008.cpp.o
src/Ec_slave/libEc_slave.a: src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_rfid.cpp.o
src/Ec_slave/libEc_slave.a: src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact.cpp.o
src/Ec_slave/libEc_slave.a: src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_mact_2.cpp.o
src/Ec_slave/libEc_slave.a: src/Ec_slave/CMakeFiles/Ec_slave.dir/Ec_slave_ingenia.cpp.o
src/Ec_slave/libEc_slave.a: src/Ec_slave/CMakeFiles/Ec_slave.dir/build.make
src/Ec_slave/libEc_slave.a: src/Ec_slave/CMakeFiles/Ec_slave.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library libEc_slave.a"
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && $(CMAKE_COMMAND) -P CMakeFiles/Ec_slave.dir/cmake_clean_target.cmake
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ec_slave.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Ec_slave/CMakeFiles/Ec_slave.dir/build: src/Ec_slave/libEc_slave.a
.PHONY : src/Ec_slave/CMakeFiles/Ec_slave.dir/build

src/Ec_slave/CMakeFiles/Ec_slave.dir/clean:
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave && $(CMAKE_COMMAND) -P CMakeFiles/Ec_slave.dir/cmake_clean.cmake
.PHONY : src/Ec_slave/CMakeFiles/Ec_slave.dir/clean

src/Ec_slave/CMakeFiles/Ec_slave.dir/depend:
	cd /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/src/Ec_slave /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave /home/abhinayh56/Abhinay/Ethercat_IGH/EtherCAT_layer/build/src/Ec_slave/CMakeFiles/Ec_slave.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/Ec_slave/CMakeFiles/Ec_slave.dir/depend

