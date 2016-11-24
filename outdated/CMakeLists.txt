cmake_minimum_required(VERSION 2.8)
 
PROJECT(readNII)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(readNII readNII.cxx)
 
if(VTK_LIBRARIES)
  target_link_libraries(readNII ${VTK_LIBRARIES})
else()
  target_link_libraries(readNII vtkHybrid vtkWidgets)
endif()

add_executable(readNIITest readNIITest.cxx)
 
if(VTK_LIBRARIES)
  target_link_libraries(readNIITest ${VTK_LIBRARIES})
else()
  target_link_libraries(readNIITest vtkHybrid vtkWidgets)
endif()

