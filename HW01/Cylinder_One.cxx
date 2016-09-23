// First include the required header files for the VTK classes we are using.
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"

int main()
{
 
  vtkConeSource *cone = vtkConeSource::New();
  cone->SetHeight( 3.0 );
  cone->SetRadius( 1.0 );
  cone->SetResolution( 10 );

  
  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
  coneMapper->SetInputConnection( cone->GetOutputPort() );

  

  
  vtkRenderWindow *renWin = vtkRenderWindow::New();


  
  int i;
  int j;
  
  for (j = 1; j < 5; j++)
    {
      vtkRenderer *ren1= vtkRenderer::New();
      for (int k=0; k<j; k++)
	{
	  vtkActor *coneActor = vtkActor::New();
	  coneActor->SetMapper( coneMapper );
	  coneActor->AddPosition(k*5,0,0);
	  ren1->AddActor( coneActor );
	  ren1->SetBackground( 0.1, 0.2, 0.4 );
	}
       renWin->AddRenderer( ren1 );
       renWin->SetSize( 300, 300 );
      
      for (i = 0; i < 30; ++i)
	{
	  // render the image
	  renWin->Render();
	  // rotate the active camera by one degree
	  // ren1->GetActiveCamera()->Azimuth( 1 );
	 }
    }



  return 0;
}
