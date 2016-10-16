cmake_minimum_required(VERSION 2.8)
 
PROJECT(QuadraticSurface)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(QuadraticSurface MACOSX_BUNDLE QuadraticSurface)
 
if(VTK_LIBRARIES)
  target_link_libraries(QuadraticSurface ${VTK_LIBRARIES})
else()
  target_link_libraries(QuadraticSurface vtkHybrid vtkWidgets)
endif()
