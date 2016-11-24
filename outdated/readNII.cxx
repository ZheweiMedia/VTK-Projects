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



// helper class to format slice status message
class StatusMessage {
public:
   static std::string Format(int slice, int maxSlice) {
      std::stringstream tmp;
      tmp << "Slice Number  " << slice + 1 << "/" << maxSlice + 1;
      return tmp.str();
   }
};
 
 
// Define own interaction style
class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:
   static myVtkInteractorStyleImage* New();
   vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage);
 
protected:
   vtkImageViewer2* _ImageViewer;
   vtkTextMapper* _StatusMapper;
   int _Slice;
   int _MinSlice;
   int _MaxSlice;
 
public:
   void SetImageViewer(vtkImageViewer2* imageViewer) {
      _ImageViewer = imageViewer;
      _MinSlice = imageViewer->GetSliceMin();
      _MaxSlice = imageViewer->GetSliceMax();
      _Slice = _MinSlice;
      cout << "Slicer: Min = " << _MinSlice << ", Max = " << _MaxSlice << std::endl;
   }
 
   void SetStatusMapper(vtkTextMapper* statusMapper) {
      _StatusMapper = statusMapper;
   }
 
 
protected:
   void MoveSliceForward() {
      if(_Slice < _MaxSlice) {
         _Slice += 1;
         cout << "MoveSliceForward::Slice = " << _Slice << std::endl;
         _ImageViewer->SetSlice(_Slice);
         std::string msg = StatusMessage::Format(_Slice, _MaxSlice);
         _StatusMapper->SetInput(msg.c_str());
         _ImageViewer->Render();
      }
   }
 
   void MoveSliceBackward() {
      if(_Slice > _MinSlice) {
         _Slice -= 1;
         cout << "MoveSliceBackward::Slice = " << _Slice << std::endl;
         _ImageViewer->SetSlice(_Slice);
         std::string msg = StatusMessage::Format(_Slice, _MaxSlice);
         _StatusMapper->SetInput(msg.c_str());
         _ImageViewer->Render();
      }
   }
 
 
   virtual void OnKeyDown() {
      std::string key = this->GetInteractor()->GetKeySym();
      if(key.compare("Up") == 0) {
         //cout << "Up arrow key was pressed." << endl;
         MoveSliceForward();
      }
      else if(key.compare("Down") == 0) {
         //cout << "Down arrow key was pressed." << endl;
         MoveSliceBackward();
      }
      // forward event
      vtkInteractorStyleImage::OnKeyDown();
   }
   
};

vtkStandardNewMacro(myVtkInteractorStyleImage);


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

  // Lets' see what will happen for template file first.
  vtkSmartPointer<vtkNIFTIImageReader> templateReader =
    vtkSmartPointer<vtkNIFTIImageReader>::New();
  templateReader->SetFileName(templateFileName.c_str());
  templateReader->Update();

  vtkSmartPointer<vtkImageData> templateImage =
    vtkSmartPointer<vtkImageData>::New();
  templateImage->ShallowCopy(templateReader->GetOutput());
  templateImage->GetScalarRange(template_range);
  std::cout << template_range[0] << template_range[1] << std::endl;

  vtkSmartPointer<vtkImageShiftScale> template_shift =
    vtkSmartPointer<vtkImageShiftScale>::New();
  template_shift->SetInputConnection(templateReader->GetOutputPort());
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

  vtkSmartPointer<vtkTextProperty> sliceTextProp = vtkSmartPointer<vtkTextProperty>::New();
   sliceTextProp->SetFontFamilyToCourier();
   sliceTextProp->SetFontSize(20);
   sliceTextProp->SetVerticalJustificationToBottom();
   sliceTextProp->SetJustificationToLeft();
 
   vtkSmartPointer<vtkTextMapper> sliceTextMapper = vtkSmartPointer<vtkTextMapper>::New();
   std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(), imageViewer->GetSliceMax());
   sliceTextMapper->SetInput(msg.c_str());
   sliceTextMapper->SetTextProperty(sliceTextProp);
 
   vtkSmartPointer<vtkActor2D> sliceTextActor = vtkSmartPointer<vtkActor2D>::New();
   sliceTextActor->SetMapper(sliceTextMapper);
   sliceTextActor->SetPosition(15, 10);
 
   // usage hint message
   vtkSmartPointer<vtkTextProperty> usageTextProp = vtkSmartPointer<vtkTextProperty>::New();
   usageTextProp->SetFontFamilyToCourier();
   usageTextProp->SetFontSize(14);
   usageTextProp->SetVerticalJustificationToTop();
   usageTextProp->SetJustificationToLeft();
 
   vtkSmartPointer<vtkTextMapper> usageTextMapper = vtkSmartPointer<vtkTextMapper>::New();
   usageTextMapper->SetInput("- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n  mouse button while dragging\n- Press g for gradient\n- Press o fpr original image.");
   usageTextMapper->SetTextProperty(usageTextProp);
 
   vtkSmartPointer<vtkActor2D> usageTextActor = vtkSmartPointer<vtkActor2D>::New();
   usageTextActor->SetMapper(usageTextMapper);
   usageTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
   usageTextActor->GetPositionCoordinate()->SetValue( 0.05, 0.95);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle =
    vtkSmartPointer<myVtkInteractorStyleImage>::New();
  myInteractorStyle->SetImageViewer(imageViewer);
  imageViewer->SetupInteractor(renderWindowInteractor);
  renderWindowInteractor->SetInteractorStyle(myInteractorStyle);

  imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
  imageViewer->GetRenderer()->AddActor2D(usageTextActor);
  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;

}

