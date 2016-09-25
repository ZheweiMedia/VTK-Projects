"""
python(2.7) version of Cylinder_series.

Zhewei @ 9/25/2016

"""

import vtk
import gzip
import pickle as Pickle
import numpy

bottomLine = -100

Raw_data = gzip.open('VTK_Subjects_180.pickle.gz', 'rb')
Subjects_data, Label, ID = Pickle.load(Raw_data)

data1 = Subjects_data[0:130,:]


renWin = vtk.vtkRenderWindow()
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
camera = vtk.vtkCamera()
camera.SetPosition(0, -100, -1000)

for j in range(130):
    ren = vtk.vtkRenderer()
    ren.SetActiveCamera(camera)
    for i in range(20):

        # create source one
        height1 = data1[j,i] 
        source = vtk.vtkCylinderSource()
        source.SetCenter(0,0,0)
        source.SetRadius(8)
        source.SetResolution(30)
        source.SetHeight(height1)

        # mapper
        mapper = vtk.vtkPolyDataMapper()
        mapper.SetInputConnection(source.GetOutputPort())

        # actor
        actor = vtk.vtkActor()
        actor.SetMapper(mapper)
        # actor.GetProperty.SetColor(1, 0.38882, 0.2784)
        actor.AddPosition(25*i-250, height1/2+bottomLine, 0)

        # actor to render
        ren.AddActor(actor)
        ren.SetBackground(0.1, 0.2, 0.4)

    iren.Initialize()
    renWin.Render()
    iren.Start()
        
    
