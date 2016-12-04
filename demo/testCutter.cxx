/*****************************************************************************
 * 1. read DICOM files in, and volume rendering. <-- done, now modify it to-->
 * 2. read a .nii file in.
 *
 *
 *
 *
 *
 ******************************************************************************/

#include <fstream>
#include <sstream>
#include <string>
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
      std::cerr << "Required arguments: MRI_file fMRI_file template_file ROI_index"
                << std::endl;
      return EXIT_FAILURE;
    }


  std::string MRI_name = argv[1];
  std::string fMRI_name = argv[2];
  std::string template_name = argv[3];
  int ROI_index = atoi(argv[4]);
  double reductionFactor = 1.0;
  double frameRate = 10.0;
  int clip = 0;
  int blendType = 0;
  bool independentComponents = true;
  double MRI_range[2];
  double fMRI_range[2];
  double template_range[2];

  int *dim;
  // initial an array, and set 120 index in it
  int index[120];
  int index_lineNo = 0;

  // Read file in, and resample, then mapper

  vtkAlgorithm *reader;
  vtkImageData *input;

  // read file to get 120 index
  std::ifstream infile("ROI_index.txt");
  std::string line;
  while (std::getline(infile, line))
    {
      std::stringstream iss(line);
      iss >> index[index_lineNo];
      index_lineNo++;
    }

  std::cout << index[80] << std::endl;


  vtkSmartPointer<vtkImageData> MRI_image =
    reader_rescale(MRI_name, MRI_range);

  vtkSmartPointer<vtkImageData> fMRI_image =
    reader_rescale(fMRI_name, fMRI_range);

  vtkSmartPointer<vtkNIFTIImageReader> template_Reader =
    vtkSmartPointer<vtkNIFTIImageReader>::New();
  template_Reader->SetFileName(template_name.c_str());
  template_Reader->Update();

  vtkSmartPointer<vtkImageData> template_image =
    vtkSmartPointer<vtkImageData>::New();
  template_image->ShallowCopy(template_Reader->GetOutput());


  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> MRI_mapper =
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> fMRI_mapper =
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> template_mapper =
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();

  // shallow copy data to imagedata

  MRI_image->GetScalarRange(MRI_range);
  fMRI_image->GetScalarRange(fMRI_range);
  template_image->GetScalarRange(template_range);

  int* dims = MRI_image->GetDimensions();
  std::cout << dims[0] << " " << dims[1] << " " << dims[2] << std::endl;
  
  std::cout << MRI_image->GetScalarTypeAsString() << std::endl;
  std::cout << fMRI_image->GetScalarTypeAsString() << std::endl;
  std::cout << template_image->GetScalarTypeAsString() << std::endl;
  

  for (int i = 0; i < dims[0]; i++)
    for (int j = 0; j < dims[1]; j++)
      for (int k = 0; k < dims[2]; k++)
        {
          float* MRI_pixel =
            static_cast<float*>(MRI_image->GetScalarPointer(i, j, k));
          float* fMRI_pixel =
            static_cast<float*>(fMRI_image->GetScalarPointer(i, j, k));
          short* template_pixel =
            static_cast<short*>(template_image->GetScalarPointer(i, j, k));
          

          if (template_pixel[0] == index[ROI_index])
            {
              template_pixel[0] = 255.0;
            }
          else
            {
              template_pixel[0] = 0;
              MRI_pixel[0] = MRI_pixel[0]/10;
              fMRI_pixel[0] = fMRI_pixel[0]/10;
            }
            
        }

  MRI_image->GetScalarRange(MRI_range);
  fMRI_image->GetScalarRange(fMRI_range);
  std::cout << fMRI_range[0] << " " << fMRI_range[1] << std::endl;

  MRI_mapper->SetInputData(MRI_image);
  MRI_mapper->SetBlendModeToMaximumIntensity();

  fMRI_mapper->SetInputData(fMRI_image);
  fMRI_mapper->SetBlendModeToMaximumIntensity();

  template_mapper->SetInputData(template_image);
  template_mapper->SetBlendModeToMaximumIntensity();

  
  // Create a transfer function mapping scalar value to opacity and color

  vtkSmartPointer<vtkVolumeProperty> MRI_Property =
    property(MRI_range[0], MRI_range[1], independentComponents, 'G');

  vtkSmartPointer<vtkVolumeProperty> fMRI_Property =
    property(fMRI_range[0], fMRI_range[1], independentComponents, 'R');

  vtkSmartPointer<vtkVolumeProperty> template_Property =
    property(template_range[0], template_range[1], independentComponents, 'B');
  

  

  vtkSmartPointer<vtkVolume> MRI_volume =
    vtkSmartPointer<vtkVolume>::New();
  vtkSmartPointer<vtkVolume> fMRI_volume =
    vtkSmartPointer<vtkVolume>::New();
  vtkSmartPointer<vtkVolume> template_volume =
    vtkSmartPointer<vtkVolume>::New();

  MRI_volume->SetMapper(MRI_mapper);
  MRI_volume->SetProperty(MRI_Property);

  fMRI_volume->SetMapper(fMRI_mapper);
  fMRI_volume->SetProperty(fMRI_Property);

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
