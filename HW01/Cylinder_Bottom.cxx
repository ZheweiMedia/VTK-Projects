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
  light->SetPosition(0,0,10.875);
  vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
  camera->SetPosition(0,0,500);
  
  
  int i;
  int j;
  double height1, height2, center1, center2;
  double radius = 10;  
  
      
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
      
  vtkSmartPointer<vtkCylinderSource> cylinder1 = vtkSmartPointer<vtkCylinderSource>::New();
  cylinder1->SetResolution(18);
  height1 = 100;
  cylinder1->SetHeight(height1);
  center1 = height1/2;
  cylinder1->SetCenter(0,0,0);
  cylinder1->SetRadius(radius);

  vtkSmartPointer<vtkPolyDataMapper> cylinderMapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
  cylinderMapper1->SetInputConnection (cylinder1->GetOutputPort());
  vtkSmartPointer<vtkActor> cylinderActor1 = vtkSmartPointer<vtkActor>::New();
 
  cylinderActor1->SetMapper(cylinderMapper1);
  cylinderActor1->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
  cylinderActor1->AddPosition(50,center1,0);

  vtkSmartPointer<vtkCylinderSource> cylinder2 = vtkSmartPointer<vtkCylinderSource>::New();
  cylinder2->SetResolution(18);
  height2 = 200;
  cylinder2->SetHeight(height2);
  center2 = height2/2;
  cylinder2->SetCenter(0,0,0);
  cylinder2->SetRadius(radius);

  vtkSmartPointer<vtkPolyDataMapper> cylinderMapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
  cylinderMapper2->SetInputConnection (cylinder2->GetOutputPort());
  vtkSmartPointer<vtkActor> cylinderActor2 = vtkSmartPointer<vtkActor>::New();
 
  cylinderActor2->SetMapper(cylinderMapper2);
  cylinderActor2->GetProperty()->SetColor(1.0000, 0.7882, 0.0784);
  cylinderActor2->AddPosition(0,center2,0);


  
  ren->AddActor( cylinderActor1 );
  ren->AddActor( cylinderActor2 );
  ren->SetBackground( 0.1, 0.2, 0.4 );
  ren->AddLight(light);
  ren->SetActiveCamera(camera);
	
  renWin->AddRenderer( ren );
  renWin->SetSize( 300, 300 );
      //renWin->Render();
      
  for (i = 0; i < 100; ++i)
    {
      // render the image
      renWin->Render();
      // rotate the active camera by one degree
      // ren->GetActiveCamera()->Azimuth( 1 );
    }
   



  return 0;
}
