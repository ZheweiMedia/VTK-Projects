# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/medialab/Zhewei/VTK-Projects/HW01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/medialab/Zhewei/VTK-Projects/HW01

# Include any dependencies generated for this target.
include CMakeFiles/DiffuseSpheres.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DiffuseSpheres.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DiffuseSpheres.dir/flags.make

CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o: CMakeFiles/DiffuseSpheres.dir/flags.make
CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o: DiffuseSpheres.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/medialab/Zhewei/VTK-Projects/HW01/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o -c /home/medialab/Zhewei/VTK-Projects/HW01/DiffuseSpheres.cxx

CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/medialab/Zhewei/VTK-Projects/HW01/DiffuseSpheres.cxx > CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.i

CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/medialab/Zhewei/VTK-Projects/HW01/DiffuseSpheres.cxx -o CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.s

CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o.requires:

.PHONY : CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o.requires

CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o.provides: CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o.requires
	$(MAKE) -f CMakeFiles/DiffuseSpheres.dir/build.make CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o.provides.build
.PHONY : CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o.provides

CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o.provides.build: CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o


# Object files for target DiffuseSpheres
DiffuseSpheres_OBJECTS = \
"CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o"

# External object files for target DiffuseSpheres
DiffuseSpheres_EXTERNAL_OBJECTS =

DiffuseSpheres: CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o
DiffuseSpheres: CMakeFiles/DiffuseSpheres.dir/build.make
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOMINC-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkGeovisCore-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkproj4-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOSQL-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtksqlite-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkInteractionImage-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkImagingStatistics-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOMovie-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkoggtheora-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOExodus-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkDomainsChemistryOpenGL2-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkDomainsChemistry-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkImagingMath-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOPLY-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOInfovis-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtklibxml2-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkRenderingContextOpenGL2-7.0.so.1
DiffuseSpheres: /usr/lib/x86_64-linux-gnu/libpython2.7.so
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkWrappingTools-7.0.a
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkRenderingImage-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkImagingStencil-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOParallelXML-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkViewsContext2D-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOParallel-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIONetCDF-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersGeneric-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersParallelImaging-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkRenderingVolumeOpenGL2-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOAMR-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersSMP-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersVerdict-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersTexture-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersFlowPaths-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOVideo-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersSelection-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOEnSight-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkRenderingLOD-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOLSDyna-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkViewsInfovis-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersProgrammable-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersPython-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkImagingMorphological-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOImport-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOExport-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersHyperTree-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkexoIIc-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkjsoncpp-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkNetCDF_cxx-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkNetCDF-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersParallel-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkhdf5_hl-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkhdf5-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersAMR-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkParallelCore-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOLegacy-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkverdict-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOXML-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOGeometry-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOXMLParser-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkexpat-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkInfovisLayout-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkViewsCore-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkInteractionWidgets-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersHybrid-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersModeling-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkInteractionStyle-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkRenderingVolume-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkChartsCore-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkInfovisCore-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersImaging-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkWrappingPython27Core-7.0.so.1
DiffuseSpheres: /usr/lib/x86_64-linux-gnu/libpython2.7.so
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkImagingGeneral-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkImagingSources-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkRenderingAnnotation-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkImagingColor-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkRenderingOpenGL2-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkImagingHybrid-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOImage-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkIOCore-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkDICOMParser-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkmetaio-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkpng-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtktiff-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkjpeg-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkglew-7.0.so.1
DiffuseSpheres: /usr/lib/x86_64-linux-gnu/libSM.so
DiffuseSpheres: /usr/lib/x86_64-linux-gnu/libICE.so
DiffuseSpheres: /usr/lib/x86_64-linux-gnu/libX11.so
DiffuseSpheres: /usr/lib/x86_64-linux-gnu/libXext.so
DiffuseSpheres: /usr/lib/x86_64-linux-gnu/libXt.so
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkRenderingLabel-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkRenderingContext2D-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkRenderingFreeType-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkRenderingCore-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkCommonColor-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersExtraction-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersStatistics-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkImagingFourier-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkImagingCore-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkalglib-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersGeometry-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersSources-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkfreetype-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkzlib-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersGeneral-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkCommonComputationalGeometry-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkFiltersCore-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkCommonExecutionModel-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkCommonDataModel-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkCommonMisc-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkCommonSystem-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtksys-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkCommonTransforms-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkCommonMath-7.0.so.1
DiffuseSpheres: /home/medialab/VTK-7.0/VTK-build/lib/libvtkCommonCore-7.0.so.1
DiffuseSpheres: CMakeFiles/DiffuseSpheres.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/medialab/Zhewei/VTK-Projects/HW01/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DiffuseSpheres"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DiffuseSpheres.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DiffuseSpheres.dir/build: DiffuseSpheres

.PHONY : CMakeFiles/DiffuseSpheres.dir/build

CMakeFiles/DiffuseSpheres.dir/requires: CMakeFiles/DiffuseSpheres.dir/DiffuseSpheres.cxx.o.requires

.PHONY : CMakeFiles/DiffuseSpheres.dir/requires

CMakeFiles/DiffuseSpheres.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DiffuseSpheres.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DiffuseSpheres.dir/clean

CMakeFiles/DiffuseSpheres.dir/depend:
	cd /home/medialab/Zhewei/VTK-Projects/HW01 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/medialab/Zhewei/VTK-Projects/HW01 /home/medialab/Zhewei/VTK-Projects/HW01 /home/medialab/Zhewei/VTK-Projects/HW01 /home/medialab/Zhewei/VTK-Projects/HW01 /home/medialab/Zhewei/VTK-Projects/HW01/CMakeFiles/DiffuseSpheres.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DiffuseSpheres.dir/depend

