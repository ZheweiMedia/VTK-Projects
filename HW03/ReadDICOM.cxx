#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageShiftScale.h>
#include <vtkImageData.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageGradient.h>





 
int main(int argc, char* argv[])
{
  // Verify input arguments
  if ( argc != 2 )
    {
    std::cout << "Usage: " << argv[0]
              << " Filename(.img)" << std::endl;
    return EXIT_FAILURE;
    }
 
  std::string inputFilename = argv[1];
  double range[2];
 
  // Read all the DICOM files in the specified directory.
  vtkSmartPointer<vtkDICOMImageReader> reader =
    vtkSmartPointer<vtkDICOMImageReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();
  
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->ShallowCopy(reader->GetOutput());
  image->GetScalarRange(range);
  
  vtkSmartPointer<vtkImageShiftScale> shiftScaleFilter = 
    vtkSmartPointer<vtkImageShiftScale>::New();
  
  shiftScaleFilter->SetInputConnection(reader->GetOutputPort());
  shiftScaleFilter->SetShift(-range[0]);
  shiftScaleFilter->SetScale(255/(range[1]-range[0]));
  shiftScaleFilter->SetOutputScalarTypeToUnsignedChar();
  shiftScaleFilter->Update();
  
  vtkSmartPointer<vtkImageGaussianSmooth> gaussianSmoothFilter = 
    vtkSmartPointer<vtkImageGaussianSmooth>::New();
  gaussianSmoothFilter->SetInputConnection(shiftScaleFilter->GetOutputPort());
  gaussianSmoothFilter->Update();
  
  vtkSmartPointer<vtkImageGradient> gradientFilter =
    vtkSmartPointer<vtkImageGradient>::New();
  gradientFilter->SetInputConnection(shiftScaleFilter->GetOutputPort());
  gradientFilter->SetDimensionality(2);
  gradientFilter->Update();
 
  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(gradientFilter->GetOutputPort());
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->Render();
 
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
