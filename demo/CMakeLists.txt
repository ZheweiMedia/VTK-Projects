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


add_executable(testMapper testMapper.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(testMapper ${VTK_LIBRARIES})
else()
  target_link_libraries(testMapper vtkHybrid vtkWidgets)
endif()

add_executable(testCutter testCutter.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(testCutter ${VTK_LIBRARIES})
else()
  target_link_libraries(testCutter vtkHybrid vtkWidgets)
endif()


add_executable(testRenderAndImage testRenderAndImage.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(testRenderAndImage ${VTK_LIBRARIES})
else()
  target_link_libraries(testRenderAndImage vtkHybrid vtkWidgets)
endif()

add_executable(testRenderMRI testRenderMRI.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(testRenderMRI ${VTK_LIBRARIES})
else()
  target_link_libraries(testRenderMRI vtkHybrid vtkWidgets)
endif()

add_executable(testContour testContour.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(testContour ${VTK_LIBRARIES})
else()
  target_link_libraries(testContour vtkHybrid vtkWidgets)
endif()


add_executable(testMRIRender testMRIRender.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(testMRIRender ${VTK_LIBRARIES})
else()
  target_link_libraries(testMRIRender vtkHybrid vtkWidgets)
endif()

add_executable(MRIRender MRIRender.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(MRIRender ${VTK_LIBRARIES})
else()
  target_link_libraries(MRIRender vtkHybrid vtkWidgets)
endif()
