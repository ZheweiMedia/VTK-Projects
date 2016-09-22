// This is an example about to generate 10 sylinders in a row.
//
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkLight.h"

int main()
{
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Wait for 100 ms to show next group
  for (unsigned int j = 0; j < 15; j++)
    {
      // time.sleep(1000);
      // for iteration to get 4 spheres.
      for(unsigned int i = 0; i < 4; i++)
	{
	  vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
	  sphere->SetThetaResolution(100);
	  sphere->SetPhiResolution(50);
	  vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	  sphereMapper->SetInputConnection(sphere->GetOutputPort());
	  vtkSmartPointer<vtkActor> sphere1 = vtkSmartPointer<vtkActor>::New();
	  sphere1->SetMapper(sphereMapper);
	  sphere1->GetProperty()->SetColor(1, 0.01*i*j,0);
	  sphere1->GetProperty()->SetAmbient(0.01*i*j);
	  sphere1->AddPosition(0.5*i*j, 0, 0);

	  // add actors to the renderer.
	  ren->AddActor(sphere1);
	}
      ren->SetBackground(0.1, 0.2, 0.4);
      renWin->SetSize(400, 200);
    }

  // set up the lighting.
  vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
  light->SetFocalPoint(1.875, 0.6125, 0);
  light->SetPosition(0.875, 1.6125, 1);
  ren->AddLight(light);

  
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
