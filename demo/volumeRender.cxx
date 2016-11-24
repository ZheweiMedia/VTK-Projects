// read DICOM files in, and volume rendering.


#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageResample.h>
#include <vtkFiniteDifferenceGradientEstimator.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsReader.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkInteractorObserver.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
    {
      std::cerr << "Required arguments: DICOM_Folder" << std::endl;
      return EXIT_FAILURE;
    }


  char *dirname = argv[1];
  vtkAlgorithm *reader;
  vtkImageData *input;
  double reductionFactor = 1.0;
  double opacityLevel = 2048;
  double opacityWindow = 4096;
  double frameRate = 10.0;
  int clip = 0;
  int blendType = 0;
  bool independentComponents = true;

  // Create the renderers, render window, and interactor

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  renWin->AddRenderer(ren);
  iren->SetRenderWindow(renWin);
  iren->SetDesiredUpdateRate(frameRate / (1+clip));
  iren->GetInteractorStyle()->SetDefaultRenderer(ren);
  

  // Read file in
  vtkSmartPointer<vtkDICOMImageReader> dicomReader =
    vtkSmartPointer<vtkDICOMImageReader>::New();
  dicomReader->SetDirectoryName(dirname);
  dicomReader->Update();
  input = dicomReader->GetOutput();
  reader = dicomReader;

  // resample the data
  vtkSmartPointer<vtkImageResample> resample =
    vtkSmartPointer<vtkImageResample>::New();
  if ( reductionFactor < 1.0 )
    {
      resample->SetInputConnection( reader->GetOutputPort());
      resample->SetAxisMagnificationFactor(0, reductionFactor);
      resample->SetAxisMagnificationFactor(1, reductionFactor);
      resample->SetAxisMagnificationFactor(2, reductionFactor);
    }

  // Create a transfer function mapping scalar value to opacity
  vtkSmartPointer<vtkPiecewiseFunction> oTFun =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
  oTFun->AddSegment(opacityLevel - 0.5*opacityWindow, 0.0,
                    opacityLevel + 0.5*opacityWindow, 1.0);

  vtkSmartPointer<vtkColorTransferFunction> cTFun =
    vtkSmartPointer<vtkColorTransferFunction>::New();
  cTFun->AddRGBSegment(0.0, 1.0, 1.0, 1.0, 55.0, 1.0, 1.0, 1.0);
  cTFun->AddRGBPoint(0.0, 0.0, 0.1, 0.0);
  cTFun->AddRGBPoint(255.0, 0.0, 0.7, 0.0 );

  vtkSmartPointer<vtkVolumeProperty> property =
    vtkSmartPointer<vtkVolumeProperty>::New();
  property->SetScalarOpacity(oTFun);
  property->SetColor(cTFun);
  property->SetInterpolationTypeToLinear();
  property->SetIndependentComponents(independentComponents);

  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> mapper =
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
  mapper->SetBlendModeToMaximumIntensity();
  if ( reductionFactor < 1.0 )
    mapper->SetInputConnection( resample->GetOutputPort());
  else
    mapper->SetInputConnection( reader->GetOutputPort());

  vtkSmartPointer<vtkVolume> volume =
    vtkSmartPointer<vtkVolume>::New();
  volume->SetMapper(mapper);
  volume->SetProperty(property);

  
  renWin->SetSize(600, 600);
  renWin->Render();
  ren->AddVolume(volume);
  ren->ResetCamera();
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;



}
