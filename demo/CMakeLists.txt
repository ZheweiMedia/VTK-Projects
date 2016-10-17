cmake_minimum_required(VERSION 2.8)
PROJECT(demo)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(cylinderSurface cylinderSurface.cxx)


if(VTK_LIBRARIES)
    target_link_libraries(cylinderSurface ${VTK_LIBRARIES})
else()
    target_link_libraries(cylinderSurface vtkHybrid vtkWidgets)
endif()

add_executable(trip cylinder_trip.cxx)
if(VTK_LIBRARIES)
    target_link_libraries(trip  ${VTK_LIBRARIES})
else()
    target_link_libraries(trip vtkHybrid vtkWidgets)
endif()
