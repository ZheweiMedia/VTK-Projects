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


int main()
{
  double bottomLine = -100;
 

  vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
  //light->SetPosition(0, 0, 100);
  vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
  camera->SetPosition(0,-100,-1000);
  
 
  for (int j = 1; j < 50; j++)
    {
      
      vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
      
      
      //ren->AddLight(light);
      ren->SetActiveCamera(camera);
      for (int k=1; k<20; k++)
	{
	  vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
	  vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	  cylinderMapper->SetInputConnection (cylinder->GetOutputPort());
	  double height = rand()%75;
	  double radius = 5;
	  cylinder->SetResolution(18);
	  cylinder->SetHeight(height);
	  cylinder->SetRadius(radius);
	  vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
	  
	  cylinderActor->SetMapper(cylinderMapper);
	  cylinderActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
	  
	  cylinderActor->AddPosition(25*k-250,height/2+bottomLine,0);
	  ren->AddActor( cylinderActor );
	  ren->SetBackground( 0.1, 0.2, 0.4 );
	}
      renWin->AddRenderer( ren );
      renWin->SetSize( 600, 300 );
      
      for (int i = 0; i < 10; ++i)
	{
	  // render the image
	  renWin->Render();
	  // rotate the active camera by one degree
	  // ren->GetActiveCamera()->Azimuth( 1 );
	 }
    }



  return 0;
}
