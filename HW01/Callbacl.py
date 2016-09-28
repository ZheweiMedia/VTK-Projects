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
global actor1
global actor2



def source_to_mapper_to_actor(height):
    source = vtk.vtkCylinderSource()
    mapper = vtk.vtkPolyDataMapper()
    actor = vtk.vtkActor()
    source.SetCenter(0,0,0)
    source.SetRadius(6.0)
    source.SetHeight(height*augment_ratio)
    source.SetResolution(100)
    mapper.SetInputConnection(source.GetOutputPort())
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(0,1,0)
    return source, mapper, actor

class vtkTimerCallback():
   def __init__(self, data1, data2):
       self.timer_count = 0
       self.data1 = data1
       self.data2 = data2
 
   def execute(self,obj,event):
       print(self.timer_count)
       ren = vtk.vtkRenderer()
       for j in range(130):
           for i in range(20):
               height1 = data1[j,i]
               height2 = data2[j,i]
               source1, mapper1, actor1 = source_to_mapper_to_actor(height1)
               source2, mapper2, actor2 = source_to_mapper_to_actor(height2)
               ren.AddActor(actor1)
               ren.AddActor(actor2)
               self.actor1.AddPosition(distance_eachSubjects*i-center_of_Subjects, height1*100/2+bottomLine1,0)
               self.actor2.AddPosition(distance_eachSubjects*i-center_of_Subjects, height2*100/2+bottomLine2,0)
       iren = obj
       iren.GetRenderWindow().Render()
       self.timer_count += 1

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
    Raw_data = gzip.open('VTK_Subjects_180.pickle.gz', 'rb')
    Subjects_data, Label, ID = Pickle.load(Raw_data)
    subjectNo1 = int(numbers[0])
    subjectNo2 = int(numbers[1])
    print ("First subject is", Label[subjectNo1])
    print ('Second subject is', Label[subjectNo2])

    data1 = Subjects_data[subjectNo1*130:(subjectNo1+1)*130,:]
    data2 = Subjects_data[subjectNo2*130:(subjectNo2+1)*130,:]

    # create source
    
    
    # create a rendering window and renderer
    
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    renWin.SetSize(700,400)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)
    ren.SetBackground(0.1, 0.2, 0.4)
    renWin.Render()
    iren.Initialize()
    camera = vtk.vtkCamera()
    camera.SetPosition(0, (bottomLine1+bottomLine2)/2, -550)
    ren.SetActiveCamera(camera)

    cb = vtkTimerCallback(data1, data2)
    #cb.actor1 = actor1
    #cb.actor2 = actor2

    iren.AddObserver('TimerEvent', cb.execute)
    timerId = iren.CreateRepeatingTimer(100);
 
    #start the interaction and timer
    iren.Start()
 
  
    

    

        
if __name__ == '__main__':
    main(sys.argv)
    pass
