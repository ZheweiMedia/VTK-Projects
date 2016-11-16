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
// headers needed for this example
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkNIFTIImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
// needed to easily convert int to std::string
#include <sstream>
#include <vtkImageShiftScale.h>
#include <vtkImageData.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageGradient.h>






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
  //templateReader->GetDataSpacing(template_3D);
  //std::cout << template_3D[0]<<" "<<template_3D[1] << " "
  //          << template_3D[2]<<std::endl;
  std::cout << templateReader->GetFilePattern() << std::endl;

  vtkSmartPointer<vtkImageData> templateImage =
    vtkSmartPointer<vtkImageData>::New();
  templateImage->DeepCopy(templateReader->GetOutput());
  templateImage->GetScalarRange(template_range);
  templateImage->GetDimensions(template_3D);
  std::cout << template_range[0] << " " << template_range[1] << std::endl;
  std::cout << template_3D[0]<<" "<<template_3D[1] << " "
            << template_3D[2]<<std::endl;
  // find out how to clip one frame for visulization

  vtkSmartPointer<vtkImageData> _2DImage =
    vtkSmartPointer<vtkImageData>::New();
  int imageExtent[6] = { 0, template_3D[0]-1, 0, template_3D[1]-1, 0, 0 };
  _2DImage->SetExtent(imageExtent);
  _2DImage->AllocateScalars(VTK_DOUBLE, 1);

  for (int y = imageExtent[2]; y <= imageExtent[3]; y++)
    {
      for (int x = imageExtent[0]; x <= imageExtent[1]; x++)
        {
          double* _2D_pixel = static_cast<double*>(_2DImage->
                                               GetScalarPointer(x, y, 0));
          int* Or_pixel = static_cast<int*>(templateImage->
                                                  GetScalarPointer(x,y,50));
          _2D_pixel[0] = Or_pixel[0];
        }
    }
  _2DImage->GetScalarRange(template_range);
  std::cout << template_range[0] << " " << template_range[1] << std::endl;
  vtkSmartPointer<vtkImageShiftScale> template_shift =
    vtkSmartPointer<vtkImageShiftScale>::New();
  template_shift->SetInputData(_2DImage);
  template_shift->SetShift(-template_range[0]);
  template_shift->SetScale(255/(template_range[1]-template_range[0]));
  template_shift->SetOutputScalarTypeToUnsignedChar();
  template_shift->Update();

  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(template_shift->GetOutputPort());
  std::cout << imageViewer->GetSliceMin() << std::endl;
  std::cout << imageViewer->GetSliceMax() << std::endl;

  std::cout << imageViewer->GetSlice() << std::endl;

  //imageViewer->SetSlice(3);

  

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->Render();
 
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;

}

