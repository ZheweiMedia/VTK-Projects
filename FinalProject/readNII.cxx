//
// This example demonstrates how to read a series of dicom images
// and how to scroll with the mousewheel or the up/down keys
// through all slices
//
// some standard vtk headers
#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
// headers needed for this example
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
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
   vtkImageGradient* _gradientFilter;
   vtkImageShiftScale* _shiftScaleFilter;
 
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
   void ShowGradient(){
     _ImageViewer->SetInputConnection(_gradientFilter->GetOutputPort());
     _ImageViewer->SetSlice(_Slice);
     _ImageViewer->Render();
   }
   void ShowOrigin(){
    _ImageViewer->SetInputConnection(_shiftScaleFilter->GetOutputPort());
     _ImageViewer->SetSlice(_Slice);
     _ImageViewer->Render();
   }
   void MoveSliceForward() {
      if(_Slice < _MaxSlice) {
         _Slice += 1;
	 _ImageViewer->SetInputConnection(_shiftScaleFilter->GetOutputPort());
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
	 _ImageViewer->SetInputConnection(_shiftScaleFilter->GetOutputPort());
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
      else if(key.compare("g") == 0) {
	ShowGradient();
      }
      else if(key.compare("o") == 0) {
	ShowOrigin();
      }
      // forward event
      vtkInteractorStyleImage::OnKeyDown();
   }
 
 
   virtual void OnMouseWheelForward() {
      //std::cout << "Scrolled mouse wheel forward." << std::endl;
      MoveSliceForward();
      // don't forward events, otherwise the image will be zoomed 
      // in case another interactorstyle is used (e.g. trackballstyle, ...)
      // vtkInteractorStyleImage::OnMouseWheelForward();
   }
 
 
   virtual void OnMouseWheelBackward() {
      //std::cout << "Scrolled mouse wheel backward." << std::endl;
      if(_Slice > _MinSlice) {
         MoveSliceBackward();
      }
      // don't forward events, otherwise the image will be zoomed 
      // in case another interactorstyle is used (e.g. trackballstyle, ...)
      // vtkInteractorStyleImage::OnMouseWheelBackward();
   }
};
 
vtkStandardNewMacro(myVtkInteractorStyleImage);
 
 
int main(int argc, char* argv[])
{
   // Verify input arguments
   if ( argc != 2 )
   {
      std::cout << "Usage: " << argv[0]
      << " FolderName" << std::endl;
      return EXIT_FAILURE;
   }

   // for range
   double range[2];
 
   std::string folder = argv[1];
   //std::string folder = "C:\\VTK\\vtkdata-5.8.0\\Data\\DicomTestImages";
 
   // Read all the DICOM files in the specified directory.
   vtkSmartPointer<vtkDICOMImageReader> reader =
      vtkSmartPointer<vtkDICOMImageReader>::New();
   reader->SetDirectoryName(folder.c_str());
   reader->Update();

   // rescale the image
   vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->ShallowCopy(reader->GetOutput());
  image->GetScalarRange(range);
  
  vtkSmartPointer<vtkImageShiftScale> shiftScaleFilter = 
    vtkSmartPointer<vtkImageShiftScale>::New();
  
  shiftScaleFilter->SetInputConnection(reader->GetOutputPort());
  shiftScaleFilter->SetShift(-range[0]);
  shiftScaleFilter->SetScale(255/(range[1]-range[0]));
  shiftScaleFilter->SetOutputScalarTypeToUnsignedChar();
  shiftScaleFilter->Update();
 
   // Visualize original image
   vtkSmartPointer<vtkImageViewer2> imageViewer =
      vtkSmartPointer<vtkImageViewer2>::New();
   imageViewer->SetInputConnection(shiftScaleFilter->GetOutputPort());
   imageViewer->SetSize(500, 500);

   // Visualize gradient image
   // Gradient image
   vtkSmartPointer<vtkImageGaussianSmooth> gaussianSmoothFilter = 
    vtkSmartPointer<vtkImageGaussianSmooth>::New();
  gaussianSmoothFilter->SetInputConnection(shiftScaleFilter->GetOutputPort());
  gaussianSmoothFilter->Update();
  
  vtkSmartPointer<vtkImageGradient> gradientFilter =
    vtkSmartPointer<vtkImageGradient>::New();
  gradientFilter->SetInputConnection(shiftScaleFilter->GetOutputPort());
  gradientFilter->SetDimensionality(2);
  gradientFilter->Update();
 
   // slice status message
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
 
   // create an interactor with our own style (inherit from vtkInteractorStyleImage)
   // in order to catch mousewheel and key events
   vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
 
   vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle =
      vtkSmartPointer<myVtkInteractorStyleImage>::New();
 
   // make imageviewer2 and sliceTextMapper visible to our interactorstyle
   // to enable slice status message updates when scrolling through the slices
   myInteractorStyle->SetImageViewer(imageViewer);
   myInteractorStyle->SetStatusMapper(sliceTextMapper);
   myInteractorStyle->_gradientFilter = gradientFilter;
   myInteractorStyle->_shiftScaleFilter = shiftScaleFilter;
 
   imageViewer->SetupInteractor(renderWindowInteractor);
   // make the interactor use our own interactorstyle
   // cause SetupInteractor() is defining it's own default interatorstyle 
   // this must be called after SetupInteractor()
   renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
   // add slice status message and usage hint message to the renderer
   imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
   imageViewer->GetRenderer()->AddActor2D(usageTextActor);
 
   // initialize rendering and interaction
   //imageViewer->GetRenderWindow()->SetSize(400, 300);
   //imageViewer->GetRenderer()->SetBackground(0.2, 0.3, 0.4);
   imageViewer->Render();
   imageViewer->GetRenderer()->ResetCamera();
   imageViewer->Render();
   renderWindowInteractor->Start();
   return EXIT_SUCCESS;
}
