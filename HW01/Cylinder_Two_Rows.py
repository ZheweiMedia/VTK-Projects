"""
python(2.7) version of Cylinder_series.

Zhewei @ 9/25/2016

"""
from __future__ import print_function
import vtk
import sys, gzip
import pickle as Pickle
import numpy

bottomLine1 = -100
bottomLine2 = 30
distance_eachSubjects = 20
center_of_Subjects = 200
augment_ratio = 100
timeFrame = 130
featureNo = 20



def source_to_mapper_to_actor(height,mapper):
    
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.SetScale(1,height,1)
    actor.GetProperty().SetColor(0,1,0)
    return actor

def data_to_float(dataList):
    data_listNew = list()
    for data in dataList:
        data_listNew.append(float(data))
    return data_listNew

def main(args):
    if len(args) < 3:
        usage( args[0] )
        pass
    else:
        work( args[1:] )
        pass
    pass

def usage (programm):
    print ("usage: python2.7 %s numer1 number2"%(programm))
    print ('       number1 and number2 are integers in [0,180]')

def work(numbers):
    Raw_data = gzip.open('VTK_Data.pickle.gz', 'rb')
    Subjects_data, Label, ID, Age, Weight = Pickle.load(Raw_data)
    Age = data_to_float(Age)
    Weight = data_to_float(Weight)
    subjectNo1 = int(numbers[0])
    subjectNo2 = int(numbers[1])
    print ("First subject is", Label[subjectNo1])
    print ('Second subject is', Label[subjectNo2])
    
    #print (Age)
    #print (Weight)

    data1 = Subjects_data[subjectNo1*130:(subjectNo1+1)*130,:]
    data2 = Subjects_data[subjectNo2*130:(subjectNo2+1)*130,:]
    # create a rendering window and renderer
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)
    camera = vtk.vtkCamera()
    camera.SetPosition(0, (bottomLine1+bottomLine2)/2, -550)
    ren.SetActiveCamera(camera)
    
    cylinderSource = vtk.vtkCylinderSource()
    cylinderSource.SetResolution(8)
    cylinderSource.SetRadius(6.0)
    cylinderSource.SetHeight(augment_ratio)
 
    #Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(cylinderSource.GetOutputPort())
    

    for j in range(1,timeFrame-1):
        for i in range(featureNo):
            # create source
            height1 = data1[j,i]
            height2 = data2[j,i]
            actor1 = source_to_mapper_to_actor(height1, mapper)
            actor2 = source_to_mapper_to_actor(height2, mapper)
                 
            actor1.AddPosition(distance_eachSubjects*i-center_of_Subjects, height1*100/2+bottomLine1,25*j)
            actor2.AddPosition(distance_eachSubjects*i-center_of_Subjects, height2*100/2+bottomLine2,25*j)

            # assign actor to the renderer
            ren.AddActor(actor1)
            ren.AddActor(actor2)
            ren.SetBackground(0.1, 0.2, 0.4)
    renWin.AddRenderer(ren)
    renWin.SetSize(700,400)
    iren.Initialize()
    renWin.Render()
    iren.Start()


        
if __name__ == '__main__':
    main(sys.argv)
    pass
