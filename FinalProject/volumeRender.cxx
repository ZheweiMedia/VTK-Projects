/*****************************************************************************
 *
 *
 * std::cout << "For example:" << std::endl;
 * std::cout << "Required arguments: 0917_MRI 0917_pp_A_0073.nii AAL2.nii" << std::endl;
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
#include <vtkSmartVolumeMapper.h>
#include "utility_2.h"



int main (int argc, char *argv[])
{
  if (argc < 3)
    {
      std::cout << "Required arguments: MRI_file fMRI_file template_file" << std::endl;
      std::cout << "For example:" << std::endl;
      std::cout << "Required arguments: 0917_MRI 0917_pp_A_0073.nii AAL2.nii" << std::endl;
      
      return EXIT_FAILURE;
    }


  std::string MRI_name = argv[1];
  std::string fMRI_name = argv[2];
  std::string template_name = argv[3];
  double reductionFactor = 1.0;
  double frameRate = 10.0;
  int clip = 0;
  int blendType = 0;
  bool independentComponents = true;
  double MRI_range[2];
  double fMRI_range[2];
  double template_range[2];

  // Read file in, and resample, then mapper

  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> MRI_mapper =
    reader_to_mapper(MRI_name, reductionFactor, MRI_range);

  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> fMRI_mapper =
    reader_to_mapper(fMRI_name, reductionFactor, fMRI_range);
  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> template_mapper =
    reader_to_mapper(template_name, reductionFactor, template_range);

  // Create a transfer function mapping scalar value to opacity and color

  vtkSmartPointer<vtkVolumeProperty> MRI_Property =
    property(MRI_range[0], MRI_range[1], independentComponents, 'R');

  vtkSmartPointer<vtkVolumeProperty> fMRI_Property =
    property(fMRI_range[0], fMRI_range[1], independentComponents, 'G');

  vtkSmartPointer<vtkVolumeProperty> template_Property =
    property(template_range[0], template_range[1], independentComponents, 'B');
  

  vtkSmartPointer<vtkVolume> MRI_volume =
    vtkSmartPointer<vtkVolume>::New();
  MRI_volume->SetMapper(MRI_mapper);
  MRI_volume->SetProperty(MRI_Property);

  vtkSmartPointer<vtkVolume> fMRI_volume =
    vtkSmartPointer<vtkVolume>::New();
  fMRI_volume->SetMapper(fMRI_mapper);
  fMRI_volume->SetProperty(fMRI_Property);

  vtkSmartPointer<vtkVolume> template_volume =
    vtkSmartPointer<vtkVolume>::New();
  template_volume->SetMapper(template_mapper);
  template_volume->SetProperty(template_Property);

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
  //ren->AddVolume(template_volume);
  ren->ResetCamera();
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;



}
