/*****************************************************************************
 * 1. read AAL .nii file in.
 * 2. show MRI or fMRI original image.
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
#include <vtkImageMapper.h>
#include <vtkImageShiftScale.h>
#include <sstream>
#include <vtkSmartVolumeMapper.h>
#include <vtkPolyDataToImageStencil.h>
#include <vtkImageStencil.h>
#include <vtkBooleanOperationPolyDataFilter.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkActor2D.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkImageResliceMapper.h>
#include <vtkImageSincInterpolator.h>
#include <vtkImageResize.h>
#include <vtkPolyDataMapper.h>
#include <vtkSurfaceReconstructionFilter.h>
#include <vtkContourFilter.h>
#include <vtkMarchingCubes.h>
#include <vtkImageStack.h>
#include <vtkImageSlice.h>
#include <vtkProperty.h>










#include "utility_RenderAndImage.h"



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

  // read file in, and rescale
  vtkSmartPointer<vtkNIFTIImageReader> template_Reader =
    vtkSmartPointer<vtkNIFTIImageReader>::New();
  template_Reader->SetFileName(template_name.c_str());
  
  vtkSmartPointer<vtkNIFTIImageReader> MRI_Reader =
    vtkSmartPointer<vtkNIFTIImageReader>::New();
  MRI_Reader->SetFileName(MRI_name.c_str());

  vtkSmartPointer<vtkNIFTIImageReader> fMRI_Reader =
    vtkSmartPointer<vtkNIFTIImageReader>::New();
  fMRI_Reader->SetFileName(fMRI_name.c_str());

  template_Reader->Update();
  MRI_Reader->Update();
  fMRI_Reader->Update();

  // shallow copy data to imagedata

  vtkSmartPointer<vtkImageData> MRI_image =
    vtkSmartPointer<vtkImageData>::New();
  MRI_image->ShallowCopy(MRI_Reader->GetOutput());

  vtkSmartPointer<vtkImageData> fMRI_image =
    vtkSmartPointer<vtkImageData>::New();
  fMRI_image->ShallowCopy(template_Reader->GetOutput());
  
  vtkSmartPointer<vtkImageData> template_image =
    vtkSmartPointer<vtkImageData>::New();
  template_image->ShallowCopy(template_Reader->GetOutput());

  int* dims = MRI_image->GetDimensions();
  std::cout << dims[0] << " " << dims[1] << " " << dims[2] << std::endl;
  
  std::cout << MRI_image->GetScalarTypeAsString() << std::endl;
  std::cout << fMRI_image->GetScalarTypeAsString() << std::endl;
  std::cout << template_image->GetScalarTypeAsString() << std::endl;

  MRI_image->GetScalarRange(MRI_range);
  fMRI_image->GetScalarRange(fMRI_range);
  template_image->GetScalarRange(template_range);
  std::cout << MRI_range[0] << " " << MRI_range[1] << std::endl;

  std::cout << "Here:" << dims[0] << " " << dims[1] << std::endl;

  // image of MRI and fMRI
  // Need to re-normalize
  vtkSmartPointer<vtkImageShiftScale> shiftScaleFilter = 
    vtkSmartPointer<vtkImageShiftScale>::New();
  
  shiftScaleFilter->SetInputConnection(MRI_Reader->GetOutputPort());
  shiftScaleFilter->SetShift(-MRI_range[0]);
  shiftScaleFilter->SetScale(255/(MRI_range[1]-MRI_range[0]));
  shiftScaleFilter->SetOutputScalarTypeToFloat();
  shiftScaleFilter->Update();

  // now save it to vtkImageData
  std::cout << "Here:" << dims[0] << " " << dims[1] << std::endl;
  MRI_image->ShallowCopy(shiftScaleFilter->GetOutput());
  MRI_image->GetScalarRange(MRI_range);
  std::cout << MRI_range[0] << " " << MRI_range[1] << std::endl;
  dims = MRI_image->GetDimensions();
  std::cout << "Here:" << dims[0] << " " << dims[1] << std::endl;
  // Now get one frame
  // new a vtkImageData, assume it is (x,y,45)
  vtkSmartPointer<vtkImageData> oneFrame =
    vtkSmartPointer<vtkImageData>::New();
  oneFrame->DeepCopy(MRI_Reader->GetOutput());
  oneFrame->SetDimensions(dims[0], dims[1], 1);
  oneFrame->AllocateScalars(VTK_FLOAT,1);
  std::cout << "Here:" << dims[0] << " " << dims[1] << std::endl;


  // Zone for template, and one frame image of MRI
  for (int i = 0; i < dims[0]; i++)
    for (int j = 0; j < dims[1]; j++)
      for (int k = 0; k < dims[2]; k++)
        {
          short* template_pixel =
            static_cast<short*>(template_image->GetScalarPointer(i, j, k));

          if (template_pixel[0] == index[ROI_index])
            template_pixel[0] = 255.0;
          else
            template_pixel[0] = 0.0;

          float* oneFrame_pixel =
            static_cast<float*>(oneFrame->GetScalarPointer(i, j, 0));
          if (k == 45)
            {
              float* MRI_pixel =
                static_cast<float*>(MRI_image->GetScalarPointer(i, j, k));
              oneFrame_pixel[0] = MRI_pixel[0];
            }
            
        }

  vtkSmartPointer<vtkMarchingCubes> surface = 
    vtkSmartPointer<vtkMarchingCubes>::New();
  surface->SetInputData(template_image);
  surface->SetValue(0, 255.0);


  

  vtkSmartPointer<vtkImageDataGeometryFilter> templateDataGeometryFilter = 
    vtkSmartPointer<vtkImageDataGeometryFilter>::New();
  templateDataGeometryFilter->SetInputData(template_image);
  templateDataGeometryFilter->Update();

  vtkSmartPointer<vtkImageData> templateImage =
    vtkSmartPointer<vtkImageData>::New();
  templateImage->ShallowCopy(surface->GetOutput());

  vtkSmartPointer<vtkPolyDataMapper> contourMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(surface->GetOutputPort());
  //contourMapper->ScalarVisibilityOff();
  contourMapper->ImmediateModeRenderingOn();

  vtkSmartPointer<vtkActor> contourActor =
  vtkSmartPointer<vtkActor>::New();
  //contourActor->GetBackfaceProperty()->SetOpacity(0.7);
  contourActor->ForceOpaqueOn();
  contourActor->SetMapper( contourMapper );
  



  /*
  vtkSmartPointer<vtkImageActor> imageActor = vtkSmartPointer<vtkImageActor>::New();
  imageActor->GetMapper()->SetInputData(oneFrame);
  imageActor->SetPosition(0.0, 0.0, 0.0);
  imageActor->SetInterpolate(1);*/

  vtkSmartPointer<vtkImageResliceMapper> imageMapper =
    vtkSmartPointer<vtkImageResliceMapper>::New();
  imageMapper->SetInputData(oneFrame);
  vtkSmartPointer<vtkImageActor> imageActor =
    vtkSmartPointer<vtkImageActor>::New();
  imageActor->SetMapper(imageMapper);
  imageActor->SetPosition(0, 0, -10);
  //imageActor->SetInterpolate(1);

  /*vtkSmartPointer<vtkImageSlice> imageSlice1 = vtkSmartPointer<vtkImageSlice>::New();
  imageSlice1->SetMapper(imageMapper);
  vtkSmartPointer<vtkImageSlice> imageSlice2 = vtkSmartPointer<vtkImageSlice>::New();
  imageSlice1->GetMapper()->SetInputConnection(surface->GetOutputPort());

  vtkSmartPointer<vtkImageStack> imageStack = vtkSmartPointer<vtkImageStack>::New();
  imageStack->AddImage(imageSlice1);
  imageStack->AddImage(imageSlice2);*/
  

  
  
  

  

  
  // Create the renderers, render window, and interactor

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  renWin->AddRenderer(ren);
  iren->SetRenderWindow(renWin);
  //iren->SetDesiredUpdateRate(frameRate / (1+clip));
  //iren->GetInteractorStyle()->SetDefaultRenderer(ren);

  
  renWin->SetSize(600, 600);
  //renWin->Render();
  //ren->AddVolume(MRI_volume);
  //ren->AddVolume(fMRI_volume);
  
  ren->AddActor(imageActor);
  //ren->AddActor(contourActor);
  ren->AddViewProp( contourActor );
  //ren->AddVolume(oneFrame_volume);
  //ren->AddVolume(template_volume);
  //ren->ResetCamera();
  //ren->AddViewProp(imageStack);
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;



}
