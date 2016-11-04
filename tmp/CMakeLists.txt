cmake_minimum_required(VERSION 2.8)
 
PROJECT(Shadows)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Shadows Shadows.cxx)
 
if(VTK_LIBRARIES)
  target_link_libraries(Shadows ${VTK_LIBRARIES})
else()
  target_link_libraries(Shadows vtkHybrid vtkWidgets)
endif()
