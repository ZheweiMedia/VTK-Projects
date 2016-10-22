cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageLaplacian)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageLaplacian  test.cxx)
 
if(VTK_LIBRARIES)
  target_link_libraries(ImageLaplacian ${VTK_LIBRARIES})
else()
  target_link_libraries(ImageLaplacian vtkHybrid vtkWidgets)
endif()
