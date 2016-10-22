cmake_minimum_required(VERSION 2.8)
 
PROJECT(ColoredElevationMap)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ColoredElevationMap MACOSX_BUNDLE ColoredElevationMap)
 
if(VTK_LIBRARIES)
  target_link_libraries(ColoredElevationMap ${VTK_LIBRARIES})
else()
  target_link_libraries(ColoredElevationMap vtkHybrid vtkWidgets)
endif()
