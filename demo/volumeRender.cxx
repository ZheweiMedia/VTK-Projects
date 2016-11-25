/*****************************************************************************
 * 1. read DICOM files in, and volume rendering. <-- done, now modify it to-->
 * 2. read a .nii file in.
 *
 *
 *
 *
 *
 ******************************************************************************/


#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkNIFTIImageReader.h>
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
#include <vtkImageShiftScale.h>
#include <sstream>
#include "utility.h"



int main (int argc, char *argv[])
{
  if (argc < 2)
    {
      std::cerr << "Required arguments: DICOM_Folder" << std::endl;
      return EXIT_FAILURE;
    }


  std::string MRI_name = argv[1];
  std::string fMRI_name = argv[2];
  std::string template_name = argv[3];
  vtkAlgorithm *reader;
  vtkImageData *input;
  double reductionFactor = 1.0;
  double opacityLevel = 2048;
  double opacityWindow = 4096;
  double frameRate = 10.0;
  int clip = 0;
  int blendType = 0;
  bool independentComponents = true;
  double _range[2];

  // Read file in, and resample, then mapper

  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> MRI_mapper =
    reader_to_mapper(MRI_name, reductionFactor);

  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> fMRI_mapper =
    reader_to_mapper(fMRI_name, reductionFactor);

  // Create a transfer function mapping scalar value to opacity

  vtkSmartPointer<vtkVolumeProperty> MRI_Property =
    property(opacityLevel, opacityWindow, independentComponents, 'G');

  vtkSmartPointer<vtkVolumeProperty> fMRI_Property =
    property(opacityLevel, opacityWindow, independentComponents, 'R');
  

  vtkSmartPointer<vtkVolume> MRI_volume =
    vtkSmartPointer<vtkVolume>::New();
  MRI_volume->SetMapper(MRI_mapper);
  MRI_volume->SetProperty(MRI_Property);

  vtkSmartPointer<vtkVolume> fMRI_volume =
    vtkSmartPointer<vtkVolume>::New();
  fMRI_volume->SetMapper(fMRI_mapper);
  fMRI_volume->SetProperty(fMRI_Property);

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

  
  renWin->SetSize(600, 600);
  renWin->Render();
  ren->AddVolume(MRI_volume);
  ren->AddVolume(fMRI_volume);
  ren->ResetCamera();
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;



}
