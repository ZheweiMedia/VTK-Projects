#include <vtkVersion.h>
#include <vtkSmartPointer.h>
 
#include <vtkActor.h>
#include <vtkDelaunay2D.h>
#include <vtkLookupTable.h>
#include <vtkMath.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkTextureMapToCylinder.h>
#include <vtkTriangleStrip.h>
#include <vtkCellArray.h>


 
// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif
 
int main(int, char *[])
{
  // Create a grid of points (height/terrian map)
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();

  vtkSmartPointer<vtkTriangleStrip> triangleStrip =
    vtkSmartPointer<vtkTriangleStrip>::New();
 
  double centerX, centerY, centerZ;
  centerX = 0.0;
  centerY = 0.0;
  centerZ = 0.0;
  double heightZ = 3.0;
  double Radius = 5.0;

  // we need to draw circles, so GrideSize is 360 degrees now.
  unsigned int GridSize = 360;
  double xx, yy, zz;
  unsigned int step = 5;
  triangleStrip->GetPointIds()->SetNumberOfIds((GridSize/step)*heightZ);
  unsigned int index = 0;
  unsigned int index2 = 0;

  for(unsigned int z = 0; z < heightZ; z++)
  
    {
	for(unsigned int x = 0; x < GridSize; x += 5)
	  {
	    xx = cos(x)*Radius + vtkMath::Random(-.2, .2);
	    yy = sin(x)*Radius + vtkMath::Random(-.2, .2);
	    zz = z + vtkMath::Random(-.2, .2);
	    points->InsertNextPoint(xx, yy, zz);
	    triangleStrip->GetPointIds()->SetId(index++,index2++);
	  }
    }

  vtkSmartPointer<vtkCellArray> cells = 
    vtkSmartPointer<vtkCellArray>::New();
  cells->InsertNextCell(triangleStrip);
  // Add the grid points to a polydata object
  vtkSmartPointer<vtkPolyData> inputPolyData = 
    vtkSmartPointer<vtkPolyData>::New();
  inputPolyData->SetPoints(points);
  inputPolyData->SetStrips(cells);
  
  
  
 
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(inputPolyData);
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.1, .2, .3);
 
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
