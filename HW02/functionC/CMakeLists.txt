cmake_minimum_required(VERSION 2.8)
 
PROJECT(FunctionC)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FunctionC FunctionC.cxx)
 
if(VTK_LIBRARIES)
  target_link_libraries(FunctionC ${VTK_LIBRARIES})
else()
  target_link_libraries(FunctionC vtkHybrid vtkWidgets)
endif()
