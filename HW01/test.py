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
 
class vtkTimerCallback():
   def __init__(self, data1, data2):
       self.timer_count = 0
       self.data1 = data1
       self.data2 = data2
 
   def execute(self,obj,event):
       print(self.timer_count)
       # self.actor.SetPosition(0, self.timer_count, 0);
       for i in range(20):
          height1 = self.data1[self.timer_count,i]
          height2 = self.data2[self.timer_count,i]
          #height1 = 0
          #height2 = 100
          self.actor1.SetPosition(distance_eachSubjects*1-center_of_Subjects, height1*100/2+bottomLine1,0)
          self.actor2.SetPosition(distance_eachSubjects*1-center_of_Subjects, height2*100/2+bottomLine2,0)
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
    Raw_data = gzip.open('VTK_Data.pickle.gz', 'rb')
    Subjects_data, Label, ID, Age, Weight = Pickle.load(Raw_data)
    subjectNo1 = int(numbers[0])
    subjectNo2 = int(numbers[1])
    data1 = Subjects_data[subjectNo1*130:(subjectNo1+1)*130,:]
    data2 = Subjects_data[subjectNo2*130:(subjectNo2+1)*130,:]
    print ("First subject is", Label[subjectNo1])
    print ('Second subject is', Label[subjectNo2])

    #Create a sphere
    cylinderSource = vtk.vtkCylinderSource()
    cylinderSource.SetResolution(8)
    cylinderSource.SetRadius(6.0)
    cylinderSource.SetHeight(0.8*augment_ratio)
 
    #Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(cylinderSource.GetOutputPort())
    actor1 = vtk.vtkActor()
    actor2 = vtk.vtkActor()
    actor1.SetMapper(mapper)
    actor2.SetMapper(mapper)
    # prop = actor.GetProperty()
 
    # Setup a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()

    camera = vtk.vtkCamera()
    camera.SetPosition(0, (bottomLine1+bottomLine2)/2, -550)
    renderer.SetActiveCamera(camera)
 
    renderWindow.AddRenderer(renderer);
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
 
    #Add the actor to the scene
    renderer.AddActor(actor1)
    renderer.AddActor(actor2)
    renderer.SetBackground(1,1,1) # Background color white

    renderWindow.SetSize(700,400)
    #Render and interact
    renderWindow.Render()
 
    # Initialize must be called prior to creating timer events.
    renderWindowInteractor.Initialize()
 
    # Sign up to receive TimerEvent
    cb = vtkTimerCallback(data1, data2)
    cb.actor1 = actor1
    cb.actor2 = actor2
    renderWindowInteractor.AddObserver('TimerEvent', cb.execute)
    timerId = renderWindowInteractor.CreateRepeatingTimer(1000);

    
    #start the interaction and timer
    renderWindowInteractor.Start()
 



if __name__ == '__main__':
    main(sys.argv)
    pass
