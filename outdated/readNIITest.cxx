/*
The fist part of VTK final project:
1. read MRI, fMRI and template data in.
2. Set different transparence for different images.
3. key for nevigation.

Zhewei 11/14/2016
 */

#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
// headers needed for this project
#include <vtkImageViewer2.h>
#include <vtkNIFTIImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkImageResliceMapper.h>
#include <vtkImageSlice.h>
// needed to easily convert int to std::string
#include <sstream>
#include <vtkImageShiftScale.h>
#include <vtkImageData.h>
#include "utility.h"



int main(int argc, char* argv[])
{
  // Verify input arguments
  // So we have three images,

  if (argc != 4)
    {
      std::cout << "Usage: " << argv[0]
                << " MRI_file fMRI_file template_file" << std::endl;
      return EXIT_FAILURE;
    }

  std::string MRIFileName = argv[1];
  std::string fMRIFileName = argv[2];
  std::string templateFileName = argv[3];
  double template_range[2];
  double MRI_range[2];
  double fMRI_range[2];
  int template_3D[3];

  // Lets' see what will happen for template file first.
  vtkSmartPointer<vtkNIFTIImageReader> templateReader =
    vtkSmartPointer<vtkNIFTIImageReader>::New();
  templateReader->SetFileName(templateFileName.c_str());
templateReader->Update();

  vtkSmartPointer<vtkImageData> templateImage =
    vtkSmartPointer<vtkImageData>::New();
  templateImage->DeepCopy(templateReader->GetOutput());
  templateImage->GetScalarRange(template_range);

  // find out how to clip one frame for visulization
  // Three views, each view show different frame

  vtkSmartPointer<vtkImageData> _2DImage_direction1 =
    DifferentViews(templateImage, 1, 50);
  vtkSmartPointer<vtkImageData> _2DImage_direction2 =
    DifferentViews(templateImage, 2, 50);
  vtkSmartPointer<vtkImageData> _2DImage_direction3 =
    DifferentViews(templateImage, 3, 50);

  vtkSmartPointer<vtkImageShiftScale> _Image_1_Rescale =
    RescaleImage(_2DImage_direction1);
  vtkSmartPointer<vtkImageShiftScale> _Image_2_Rescale =
    RescaleImage(_2DImage_direction2);
  vtkSmartPointer<vtkImageShiftScale> _Image_3_Rescale =
    RescaleImage(_2DImage_direction3);


  // Visualize
  vtkSmartPointer<vtkImageResliceMapper> _Image_1_Mapper =
    vtkSmartPointer<vtkImageResliceMapper>::New();
  vtkSmartPointer<vtkImageResliceMapper> _Image_2_Mapper =
    vtkSmartPointer<vtkImageResliceMapper>::New();
  vtkSmartPointer<vtkImageResliceMapper> _Image_3_Mapper =
    vtkSmartPointer<vtkImageResliceMapper>::New();
  _Image_1_Mapper->SetInputConnection(_Image_1_Rescale->GetOutputPort());
  _Image_2_Mapper->SetInputConnection(_Image_2_Rescale->GetOutputPort());
  _Image_3_Mapper->SetInputConnection(_Image_3_Rescale->GetOutputPort());

  vtkSmartPointer<vtkImageSlice> _ImageActor_1 =
    vtkSmartPointer<vtkImageSlice>::New();
  vtkSmartPointer<vtkImageSlice> _ImageActor_2 =
    vtkSmartPointer<vtkImageSlice>::New();
  vtkSmartPointer<vtkImageSlice> _ImageActor_3 =
    vtkSmartPointer<vtkImageSlice>::New();
  _ImageActor_1->SetMapper(_Image_1_Mapper);
  _ImageActor_2->SetMapper(_Image_2_Mapper);
  _ImageActor_3->SetMapper(_Image_3_Mapper);

  vtkSmartPointer<vtkRenderer> _Image_1_renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderer> _Image_2_renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderer> _Image_3_renderer =
    vtkSmartPointer<vtkRenderer>::New();
  _Image_1_renderer->AddActor(_ImageActor_1);
  _Image_1_renderer->SetViewport(0.0, 0.5, 0.5, 1);
  _Image_1_renderer->SetBackground( 0.2, 0.0, 0.2 );
  _Image_2_renderer->AddActor(_ImageActor_2);
  _Image_2_renderer->SetViewport(0.5, 0.5, 1.0, 1.0);
  _Image_2_renderer->SetBackground( 0.2, 0.2, 0.0 );
  _Image_3_renderer->AddActor(_ImageActor_3);
  _Image_3_renderer->SetViewport(0.0, 0.0, 0.5, 0.5);
  _Image_3_renderer->SetBackground( 0.0, 0.2, 0.2 );

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(_Image_1_renderer);
  renderWindow->AddRenderer(_Image_2_renderer);
  renderWindow->AddRenderer(_Image_3_renderer);
  renderWindow->SetSize(1000,1000);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;

}
