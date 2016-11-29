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
#include <vtkSmartVolumeMapper.h>
#include <vtkImageThreshold.h>
#include <vtkImplicitBoolean.h>
#include <vtkCutter.h>
#include <vtkBooleanOperationPolyDataFilter.h>


#include "utility_cutter.h"



int main (int argc, char *argv[])
{
  if (argc < 2)
    {
      std::cerr << "Required arguments: MRI_file fMRI_file template_file" << std::endl;
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

  int *dim;

  // Read file in, and resample, then mapper

  vtkAlgorithm *reader;
  vtkImageData *input;

  vtkSmartPointer<vtkNIFTIImageReader> template_Reader =
    vtkSmartPointer<vtkNIFTIImageReader>::New();
  template_Reader->SetFileName(template_name.c_str());
  
  vtkSmartPointer<vtkNIFTIImageReader> MRI_Reader =
    vtkSmartPointer<vtkNIFTIImageReader>::New();
  MRI_Reader->SetFileName(MRI_name.c_str());

  template_Reader->Update();
  MRI_Reader->Update();

  vtkSmartPointer<vtkImageResample> resample =
    vtkSmartPointer<vtkImageResample>::New();

  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> mapper =
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
  //mapper->SetInputConnection(reader->GetOutputPort());

  // deep copy data to imagedata

  vtkSmartPointer<vtkImageData> MRI_image =
    vtkSmartPointer<vtkImageData>::New();
  MRI_image->ShallowCopy(MRI_Reader->GetOutput());
  int* dims = MRI_image->GetDimensions();
  std::cout << dims[0] << " " << dims[1] << " " << dims[2] << std::endl;
  


  vtkSmartPointer<vtkImageData> template_image =
    vtkSmartPointer<vtkImageData>::New();
  template_image->ShallowCopy(template_Reader->GetOutput());
  
  std::cout << MRI_image->GetScalarTypeAsString() << std::endl;
  std::cout << template_image->GetScalarTypeAsString() << std::endl;

  for (int i = 0; i < dims[0]; i++)
    for (int j = 0; j < dims[1]; j++)
      for (int k = 0; k < dims[2]; k++)
        {
          short* template_pixel =
            static_cast<short*>(template_image->GetScalarPointer(i, j, k));
          float* MRI_pixel =
            static_cast<float*>(MRI_image->GetScalarPointer(i, j, k));
          if (template_pixel[0] == 4101.0)
            {
              template_pixel[0] = 255.0;
            }
          else
            {
              template_pixel[0] = 0;
              MRI_pixel[0] = MRI_pixel[0]/10;
            }
            
        }

  MRI_image->GetScalarRange(MRI_range);
  std::cout << MRI_range[0] << " " << MRI_range[1] << std::endl;

  mapper->SetInputData(MRI_image);
  mapper->SetBlendModeToMaximumIntensity();

  
  // Create a transfer function mapping scalar value to opacity and color

  vtkSmartPointer<vtkVolumeProperty> template_Property =
    property(template_range[0], template_range[1], independentComponents, 'B');
  

  

  vtkSmartPointer<vtkVolume> template_volume =
    vtkSmartPointer<vtkVolume>::New();
  template_volume->SetMapper(mapper);
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
  //ren->AddVolume(MRI_volume);
  //ren->AddVolume(fMRI_volume);
  ren->AddVolume(template_volume);
  ren->ResetCamera();
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;



}
