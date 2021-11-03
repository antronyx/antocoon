# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_SOURCE_DIR = /home/antronyx/antocoon

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/antronyx/antocoon

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/antronyx/antocoon/CMakeFiles /home/antronyx/antocoon//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/antronyx/antocoon/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Antocoon

# Build rule for target.
Antocoon: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Antocoon
.PHONY : Antocoon

# fast build rule for target.
Antocoon/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Antocoon.dir/build.make CMakeFiles/Antocoon.dir/build
.PHONY : Antocoon/fast

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Antocoon.dir/build.make CMakeFiles/Antocoon.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Antocoon.dir/build.make CMakeFiles/Antocoon.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Antocoon.dir/build.make CMakeFiles/Antocoon.dir/main.cpp.s
.PHONY : main.cpp.s

menu.o: menu.cpp.o
.PHONY : menu.o

# target to build an object file
menu.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Antocoon.dir/build.make CMakeFiles/Antocoon.dir/menu.cpp.o
.PHONY : menu.cpp.o

menu.i: menu.cpp.i
.PHONY : menu.i

# target to preprocess a source file
menu.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Antocoon.dir/build.make CMakeFiles/Antocoon.dir/menu.cpp.i
.PHONY : menu.cpp.i

menu.s: menu.cpp.s
.PHONY : menu.s

# target to generate assembly for a file
menu.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Antocoon.dir/build.make CMakeFiles/Antocoon.dir/menu.cpp.s
.PHONY : menu.cpp.s

social.o: social.cpp.o
.PHONY : social.o

# target to build an object file
social.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Antocoon.dir/build.make CMakeFiles/Antocoon.dir/social.cpp.o
.PHONY : social.cpp.o

social.i: social.cpp.i
.PHONY : social.i

# target to preprocess a source file
social.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Antocoon.dir/build.make CMakeFiles/Antocoon.dir/social.cpp.i
.PHONY : social.cpp.i

social.s: social.cpp.s
.PHONY : social.s

# target to generate assembly for a file
social.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Antocoon.dir/build.make CMakeFiles/Antocoon.dir/social.cpp.s
.PHONY : social.cpp.s

tree.o: tree.cpp.o
.PHONY : tree.o

# target to build an object file
tree.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Antocoon.dir/build.make CMakeFiles/Antocoon.dir/tree.cpp.o
.PHONY : tree.cpp.o

tree.i: tree.cpp.i
.PHONY : tree.i

# target to preprocess a source file
tree.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Antocoon.dir/build.make CMakeFiles/Antocoon.dir/tree.cpp.i
.PHONY : tree.cpp.i

tree.s: tree.cpp.s
.PHONY : tree.s

# target to generate assembly for a file
tree.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Antocoon.dir/build.make CMakeFiles/Antocoon.dir/tree.cpp.s
.PHONY : tree.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Antocoon"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... menu.o"
	@echo "... menu.i"
	@echo "... menu.s"
	@echo "... social.o"
	@echo "... social.i"
	@echo "... social.s"
	@echo "... tree.o"
	@echo "... tree.i"
	@echo "... tree.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

