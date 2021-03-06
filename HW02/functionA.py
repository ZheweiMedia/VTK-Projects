"""
Python progam for the HW02, 3.b 

F(x, y, z) = x^2+3xy+5yz+7xz

Zhewei @ 10/15/2016
"""

import vtk

quadric = vtk.vtkQuadric()
quadric.SetCoefficients(1, 0, 0, 3, 5, 7, 0, 0, 0, 0)

# sample function to generate data
sample = vtk.vtkSampleFunction()
sample.SetSampleDimensions(30, 30, 30)
sample.SetImplicitFunction(quadric)

# draw them as contour
contours = vtk.vtkContourFilter()
contours.SetInputConnection(sample.GetOutputPort())
contours.GenerateValues(5, 0.0, 3.0)

contMapper = vtk.vtkPolyDataMapper()
contMapper.SetInputConnection(contours.GetOutputPort())
contMapper.SetScalarRange(0.0, 3)

contActor = vtk.vtkActor()
contActor.SetMapper(contMapper)

#outline outside
outline = vtk.vtkOutlineFilter()
outline.SetInputConnection(sample.GetOutputPort())

outlineMapper = vtk.vtkPolyDataMapper()
outlineMapper.SetInputConnection(outline.GetOutputPort())

outlineActor = vtk.vtkActor()
outlineActor.SetMapper(outlineMapper)
outlineActor.GetProperty().SetColor(0,0,0)

# axes, and set the axes position
axesActor = vtk.vtkAxesActor()
position = vtk.vtkTransform()
position.Translate(-1.0, -1.0, -1.0)
axesActor.SetUserTransform(position)

# render, windowInteractor
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

ren.SetBackground(1,1,1)
ren.AddActor(contActor)
ren.AddActor(outlineActor)
ren.AddActor(axesActor)

iren.Initialize()
renWin.Render()
iren.Start()
