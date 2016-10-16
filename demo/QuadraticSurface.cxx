#include <vtkSmartPointer.h>
//#include <vtkQuadric.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include "vtkMyFunction.h"


int main(int, char *[])
{
  // Create the quadric function definition
  vtkSmartPointer<vtkSphere> myFunction =
    vtkSmartPointer<vtkSphere>::New();

  //vtkSmartPointer<vtkQuadric> quadric =
  //vtkSmartPointer<vtkQuadric>::New();
  //quadric->SetCoefficients(.5,1,.2,0,.1,0,0,.2,0,0);
  
  // Sample the quadric function
  vtkSmartPointer<vtkSampleFunction> sample = 
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(50,50,50);
  sample->SetImplicitFunction(myFunction);
  double value = 2.0;
  double xmin = -value, xmax = value, ymin = -value, ymax = value, zmin = -value, zmax = value;
  sample->SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax);
 
 
  vtkSmartPointer<vtkContourFilter> contourFilter =
    vtkSmartPointer<vtkContourFilter>::New();
  contourFilter->SetInputConnection(sample->GetOutputPort());
  contourFilter->GenerateValues(5, 0.0, 3.0);
  contourFilter->Update();
 
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(contourFilter->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green
 
  renderWindow->Render();
  renderWindowInteractor->Start();	
 
  return EXIT_SUCCESS;
}
