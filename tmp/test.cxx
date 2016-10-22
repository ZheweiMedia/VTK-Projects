#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkImageLaplacian.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageCast.h>
#include <vtkImageReader.h>
#include <vtkImageGaussianSmooth.h>
 
int main(int argc, char* argv[])
{
  std::string inputFilename = argv[1];
  // Create an image
  vtkSmartPointer<vtkImageReader> source =
    vtkSmartPointer<vtkImageReader>::New();
  source->SetFileName(inputFilename.c_str());
  source->Update();
 
  vtkSmartPointer<vtkImageCast> castOriginal =
    vtkSmartPointer<vtkImageCast>::New();
  castOriginal->SetInputConnection(source->GetOutputPort());
  castOriginal->SetOutputScalarTypeToFloat();
  castOriginal->Update();

  /*vtkSmartPointer<vtkImageGaussianSmooth> gaus =
    vtkSmartPointer<vtkImageGaussianSmooth>::New();
  gaus->SetStandardDeviation(0.2, 0.2);
  gaus->SetInputConnection(castOriginal->GetOutputPort());
  gaus->Update();*/
  
 
  vtkSmartPointer<vtkImageLaplacian> laplacianFilter = 
    vtkSmartPointer<vtkImageLaplacian>::New();
  laplacianFilter->SetInputConnection(castOriginal->GetOutputPort());
  laplacianFilter->Update();
 
  vtkSmartPointer<vtkImageCast> castLaplacian =
    vtkSmartPointer<vtkImageCast>::New();
  castLaplacian->SetInputConnection(laplacianFilter->GetOutputPort());
  castLaplacian->SetOutputScalarTypeToFloat();
  castLaplacian->Update();
 
  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};
 
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    castOriginal->GetOutputPort());
 
  vtkSmartPointer<vtkImageActor> laplacianActor =
    vtkSmartPointer<vtkImageActor>::New();
  laplacianActor->GetMapper()->SetInputConnection(
    castLaplacian->GetOutputPort());
 
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600,300);
 
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
 
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle( style );
 
  interactor->SetRenderWindow(renderWindow);
 
  // Setup both renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(leftViewport);
 
  vtkSmartPointer<vtkRenderer> laplacianRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  laplacianRenderer->SetViewport(rightViewport);
 
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(laplacianRenderer);
 
  originalRenderer->AddActor(originalActor);
  laplacianRenderer->AddActor(laplacianActor);
 
  originalRenderer->ResetCamera();
  laplacianRenderer->ResetCamera();
 
  renderWindow->Render();
  interactor->Start();
 
  return EXIT_SUCCESS;
}
