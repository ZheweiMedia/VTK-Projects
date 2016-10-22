#!/usr/bin/env python
import vtk
import fileinput
from vtk.test import Testing
from vtk.util.misc import vtkGetDataRoot
VTK_DATA_ROOT = vtkGetDataRoot()

# This script subtracts the 2D laplacian from an image to enhance the edges.
# Image pipeline
reader = vtk. vtkImageReader()
#reader.SetFileName("" + str(VTK_DATA_ROOT) + "/Data/fullhead15.png")
reader.SetFileName("~/Zhewei/VTK-Projects/tmp/1.jpg")

cast = vtk.vtkImageCast()
cast.SetInputConnection(reader.GetOutputPort())
cast.SetOutputScalarTypeToDouble()
cast.Update()

gaus = vtk.vtkImageGaussianSmooth()
gaus.SetStandardDeviation(0.2, 0.2)
gaus.SetInputConnection(cast.GetOutputPort())
gaus.Update()

lap = vtk.vtkImageLaplacian()
lap.SetInputConnection(gaus.GetOutputPort())
lap.SetDimensionality(2)
lap.Update()

subtract = vtk.vtkImageMathematics()
subtract.SetOperationToSubtract()
subtract.SetInput1Data(gaus.GetOutput())
subtract.SetInput2Data(lap.GetOutput())
subtract.ReleaseDataFlagOff()

#subtract BypassOn
viewer = vtk.vtkImageViewer()
#viewer DebugOn
#viewer.SetInputConnection(subtract.GetOutputPort())
viewer.SetInputData(lap.GetOutput())
#viewer.SetColorWindow(2000)
viewer.SetColorLevel(2000)
viewer.Render()
rwi=vtk.vtkRenderWindowInteractor()
viewer.SetupInteractor(rwi)
rwi.Start()
