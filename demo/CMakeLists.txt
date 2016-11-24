#

cmake_minimum_required(VERSION 2.8)

PROJECT(volumeRender)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(volumeRender volumeRender.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(volumeRender ${VTK_LIBRARIES})
else()
  target_link_libraries(volumeRender vtkHybrid vtkWidgets)
endif()

add_executable(FixedPointVolumeRayCastMapperCT FixedPointVolumeRayCastMapperCT.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(FixedPointVolumeRayCastMapperCT ${VTK_LIBRARIES})
else()
  target_link_libraries(FixedPointVolumeRayCastMapperCT vtkHybrid vtkWidgets)
endif()
