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
 
// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif
 
int main(int, char *[])
{
  // Create a grid of points (height/terrian map)
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();

  // Create grid points for cylinder
  vtkSmartPointer<vtkPoints> cylinderPoints =
    vtkSmartPointer<vtkPoints>::New();
 
  unsigned int GridSize = 20;
  double xx, yy, zz;
  double x_cylinder, y_cylinder, z_cylinder;
  double degree;
  double radius = 4;
  for(unsigned int x = 0; x < GridSize; x++)
    {
    for(unsigned int y = 0; y < GridSize; y++)
      {
      xx = x + vtkMath::Random(-.2, .2);
      yy = y + vtkMath::Random(-.2, .2);
      zz = vtkMath::Random(-.5, .5);
      points->InsertNextPoint(xx, yy, zz);

      // map to cylinder
      // yy now is Z, and xx map to degree
      degree = xx/radius*2;
      z_cylinder = yy;
      x_cylinder = (radius+zz)*cos(degree);
      y_cylinder = (radius+zz)*sin(degree);
      cylinderPoints->InsertNextPoint(x_cylinder, y_cylinder, z_cylinder);
      }
    }
 
  // Add the grid points to a polydata object
  vtkSmartPointer<vtkPolyData> inputPolyData = 
    vtkSmartPointer<vtkPolyData>::New();
  inputPolyData->SetPoints(points);

 
  // Triangulate the grid points
  vtkSmartPointer<vtkDelaunay2D> delaunay = 
    vtkSmartPointer<vtkDelaunay2D>::New();
  
  delaunay->SetInputData(inputPolyData);
  delaunay->Update();
  // the polyData for plane
  vtkPolyData* planePolyData = delaunay->GetOutput();

  // the polyData for cylinder
  vtkSmartPointer<vtkPolyData> cylinderPolyData = 
    vtkSmartPointer<vtkPolyData>::New();
  //cylinderPolyData->SetPoints(cylinderPoints);
  cylinderPolyData->DeepCopy(planePolyData);
  cylinderPolyData->SetPoints(cylinderPoints);
 
  double bounds[6];
  planePolyData->GetBounds(bounds);
 
  // Find min and max z
  double minz = bounds[4];
  double maxz = bounds[5];
 
  // Create the color map
  vtkSmartPointer<vtkLookupTable> colorLookupTable = 
    vtkSmartPointer<vtkLookupTable>::New();
  colorLookupTable->SetTableRange(minz, maxz);
  colorLookupTable->Build();
 
  // Generate the colors for each point based on the color map
  vtkSmartPointer<vtkUnsignedCharArray> colors = 
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName("Colors");
 
  for(int i = 0; i < planePolyData->GetNumberOfPoints(); i++)
    {
    double p[3];
    planePolyData->GetPoint(i,p);
 
    double dcolor[3];
    colorLookupTable->GetColor(p[2], dcolor);
    unsigned char color[3];
    for(unsigned int j = 0; j < 3; j++)
      {
      color[j] = static_cast<unsigned char>(255.0 * dcolor[j]);
      }
 
    colors->InsertNextTupleValue(color);
    }

  // Orginal plane code
  planePolyData->GetPointData()->SetScalars(colors);
  
  //replace the point value with the cylinder value
  
  cylinderPolyData->GetPointData()->SetScalars(colors);
 
  // Create a mapper and actor for plane
  vtkSmartPointer<vtkPolyDataMapper> plane_mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  plane_mapper->SetInputData(planePolyData);
  
  vtkSmartPointer<vtkActor> plane_actor = 
    vtkSmartPointer<vtkActor>::New();
  plane_actor->SetMapper(plane_mapper);

  // Create a mapper and actor for cylinder
  vtkSmartPointer<vtkPolyDataMapper> cylinder_mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cylinder_mapper->SetInputData(cylinderPolyData);
  
  vtkSmartPointer<vtkActor> cylinder_actor = 
    vtkSmartPointer<vtkActor>::New();
  cylinder_actor->SetMapper(cylinder_mapper);
 
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> plane_renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  
  vtkSmartPointer<vtkRenderer> cylinder_renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(plane_renderer);
  renderWindow->AddRenderer(cylinder_renderer);
  renderWindow->SetSize(600,300);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  // Add the actor to the scene
  plane_renderer->AddActor(plane_actor);
  plane_renderer->SetViewport(0.0, 0.0, 0.5, 1.0);
  plane_renderer->SetBackground(.1, .2, .3);
  cylinder_renderer->AddActor(cylinder_actor);
  cylinder_renderer->SetViewport(0.5, 0.0, 1.0, 1.0);
  cylinder_renderer->SetBackground(.2, .3, .4);
  
 
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
