// First include the required header files for the VTK classes we are using.
#include "vtkCylinderSource.h"
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkLight.h"
#include "stdlib.h"
#include <iostream>

int main()
{
  
  
 

  vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
  light->SetFocalPoint(1.875, 0.6125, 0);
  light->SetPosition(-10.875, 0, 0);
  vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
  camera->SetPosition(-500,-100,0);
  
  
  int i;
  int j;
  double height;
  double radius = 10;
  double center = height/2 -100;
  
  for (j = 1; j < 15; j++)
    {
      
      vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
      
      vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
      cylinder->SetResolution(18);

      vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
      cylinderMapper->SetInputConnection (cylinder->GetOutputPort());
      vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
      height = rand()%100;
      cylinder->SetHeight(height);
      center = height/2;
      cylinder->SetCenter(0,0,0);
      std::cout << height << ' '<< center <<std::endl;
      cylinder->SetRadius(radius);
      cylinderActor->SetMapper(cylinderMapper);
      cylinderActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
	  
      //coneActor->AddPosition(k*5,0,0);
      cylinderActor->AddPosition(0,center,0);
      ren->AddActor( cylinderActor );
      ren->SetBackground( 0.1, 0.2, 0.4 );
      ren->AddLight(light);
      ren->SetActiveCamera(camera);
	
      renWin->AddRenderer( ren );
      renWin->SetSize( 300, 300 );
      //renWin->Render();
      
       for (i = 0; i < 30; ++i)
	{
	  // render the image
	  renWin->Render();
	  // rotate the active camera by one degree
	  // ren->GetActiveCamera()->Azimuth( 1 );
	  }
    }



  return 0;
}
