/*
The fist part of VTK final project:
1. read MRI, fMRI and template data in.
2. Set different transparence for different images.
3. key for nevigation.

Zhewei 11/14/2016
 */

#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkNIFTIImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageShiftScale.h>
#include <vtkImageData.h>


int main(int argc, char* argv[])
{
  // Verify input arguments
  // So we have three images, 
  if (argc != 4)
    {
      std::cout << "Usage: " << argv[0]
                << "MRI_file fMRI_file template_file" << std::endl;
      return EXIT_FAILURE;
    }

  std::string MRIFileName = argv[1];
  std::string fMRIFileName = argv[2];
  std::string templateFileName = argv[3];

  // template file is different with others, it is a series.
  // Lets' see what will happen for template file first.
  vtkSmartPointer<vtkNIFTIImageReader> templateReader =
    vtkSmartPointer<vtkNIFTIImageReader>::New();
  templateReader->SetFileName(templateFileName.c_str());
  templateReader->Update();

  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(templateReader->GetOutputPort());
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;

}

