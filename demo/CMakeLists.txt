cmake_minimum_required(VERSION 2.8)
PROJECT(cylinderSurface)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(cylinderSurface MACOSX_BUNDLE cylinderSurface)

if(VTK_LIBRARIES)
    target_link_libraries(cylinderSurface ${VTK_LIBRARIES})
else()
    target_link_libraries(cylinderSurface vtkHybrid vtkWidgets)
endif()
