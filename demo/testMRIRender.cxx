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
#include <vtkImageShiftScale.h>
#include <vtkVolume.h>
#include <vtkImageResliceMapper.h>
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorObserver.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkObjectFactory.h>


#include "utility_RenderAndImage.h"




class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:
  static myVtkInteractorStyleImage* New();
  vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage);
  vtkImageData* _MRI_Copy;
  vtkImageData* _oneFrame;
  vtkImageData* _MRI_image;
  vtkVolume* _MRI_ROI_volume;
  vtkImageActor* _imageActor;
  int _MinSlice;
  int _MaxSlice;
  vtkRenderer* _renderer;
 
protected:
  int _Slice;
  int* dims;
 
public:
   void SetRender(vtkRenderer* renderer) {
     _renderer = renderer;
     _Slice = _MinSlice;
     ShowFrame(_Slice);
     dims = _MRI_Copy->GetDimensions();
     _renderer->AddActor(_imageActor);
     _renderer->AddVolume(_MRI_ROI_volume);
   }
 
 
protected:

   void ShowFrame(int FrameNo){
     for(int i = 0; i < dims[0]; i++)
       for (int j = 0; j < dims[1]; j++)
         for (int k = 0; k < dims[2]; k++)
           {
             float* oneFrame_pixel =
               static_cast<float*>(_oneFrame->GetScalarPointer(i, j, 0));
             float* MRI_Copypixel =
               static_cast<float*>(_MRI_Copy->GetScalarPointer(i, j, k));
             if (k == FrameNo)
               {
                 float* MRI_pixel =
                   static_cast<float*>(_MRI_image->GetScalarPointer(i, j, k));
                 oneFrame_pixel[0] = MRI_pixel[0];
               }
             if (k < FrameNo)
               MRI_Copypixel[0] = 0.0;
           }
     vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> MRI_ROI_mapper =
       vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
     MRI_ROI_mapper->SetInputData(_MRI_Copy);
     MRI_ROI_mapper->SetBlendModeToMaximumIntensity();
  

     vtkSmartPointer<vtkVolumeProperty> MRI_ROI_Property =
       property(0, 255, 1, 'B');

     
     _MRI_ROI_volume->SetMapper(MRI_ROI_mapper);
     _MRI_ROI_volume->SetProperty(MRI_ROI_Property);

  

     vtkSmartPointer<vtkImageResliceMapper> imageMapper =
       vtkSmartPointer<vtkImageResliceMapper>::New();
     imageMapper->SetInputData(_oneFrame);

    
     _imageActor->GetMapper()->SetInputData(_oneFrame);
     _imageActor->SetPosition(0, 0, FrameNo*2);
     _imageActor->SetInterpolate(1);
   }
   /*void ShowGradient(){
     _ImageViewer->SetInputConnection(_gradientFilter->GetOutputPort());
     _ImageViewer->SetSlice(_Slice);
     _ImageViewer->Render();
   }
   void ShowOrigin(){
    _ImageViewer->SetInputConnection(_shiftScaleFilter->GetOutputPort());
     _ImageViewer->SetSlice(_Slice);
     _ImageViewer->Render();
     }*/
   void MoveSliceForward() {
      if(_Slice < _MaxSlice) {
         _Slice += 1;
         ShowFrame(_Slice);
         _renderer->AddActor(_imageActor);
         _renderer->AddVolume(_MRI_ROI_volume);
      }
   }
 
   void MoveSliceBackward() {
      if(_Slice > _MinSlice) {
         _Slice -= 1;
         ShowFrame(_Slice);
         _renderer->AddActor(_imageActor);
         _renderer->AddVolume(_MRI_ROI_volume);
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
      /* else if(key.compare("g") == 0) {
	ShowGradient();
      }
      else if(key.compare("o") == 0) {
      ShowOrigin();
      }*/
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




int main (int argc, char *argv[])
{
  if (argc < 4)
    {
      std::cerr << "Required arguments: MRI_file fMRI_file template_file ROI_index"
                << std::endl;
      return EXIT_FAILURE;
    }


  std::string MRI_name = argv[1];
  std::string fMRI_name = argv[2];
  std::string template_name = argv[3];
  int ROI_index = atoi(argv[4]);
  bool independentComponents = true;
  double frameRate = 10.0;
  int clip = 0;
  double MRI_range[2];
  double fMRI_range[2];
  
  // initial an array, and set 120 index in it
  int index[120];
  int index_lineNo = 0;
  
  // read file to get 120 index
  std::ifstream infile("ROI_index.txt");
  std::string line;
  while (std::getline(infile, line))
    {
      std::stringstream iss(line);
      iss >> index[index_lineNo];
      index_lineNo++;
    }


  // read file in
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

  // shallow copy data to imagedata, and normalize

  vtkSmartPointer<vtkImageData> MRI_image =
    vtkSmartPointer<vtkImageData>::New();
  MRI_image->ShallowCopy(MRI_Reader->GetOutput());

  vtkSmartPointer<vtkImageData> fMRI_image =
    vtkSmartPointer<vtkImageData>::New();
  fMRI_image->ShallowCopy(template_Reader->GetOutput());
  
  vtkSmartPointer<vtkImageData> template_image =
    vtkSmartPointer<vtkImageData>::New();
  template_image->ShallowCopy(template_Reader->GetOutput());

  int* dims = template_image->GetDimensions();

  //std::cout << "template dims:" << dims[0] << " "
  //        << dims[1] << " " << dims[2] << std::endl;
  //std::cout << MRI_image->GetScalarTypeAsString() << std::endl;
  //std::cout << fMRI_image->GetScalarTypeAsString() << std::endl;
  //std::cout << template_image->GetScalarTypeAsString() << std::endl;

  MRI_image->GetScalarRange(MRI_range);
  fMRI_image->GetScalarRange(fMRI_range);
  
  // image of MRI and fMRI
  vtkSmartPointer<vtkImageShiftScale> shiftScaleFilter = 
    vtkSmartPointer<vtkImageShiftScale>::New();
  
  shiftScaleFilter->SetInputConnection(MRI_Reader->GetOutputPort());
  shiftScaleFilter->SetShift(-MRI_range[0]);
  shiftScaleFilter->SetScale(255/(MRI_range[1]-MRI_range[0]));
  shiftScaleFilter->SetOutputScalarTypeToFloat();
  shiftScaleFilter->Update();

  // now save it to vtkImageData
  MRI_image->ShallowCopy(shiftScaleFilter->GetOutput());
  MRI_image->GetScalarRange(MRI_range);
  // Now get one frame
  // new a vtkImageData, assume it is (x,y,45)
  vtkSmartPointer<vtkImageData> oneFrame =
    vtkSmartPointer<vtkImageData>::New();
  oneFrame->DeepCopy(MRI_Reader->GetOutput());
  oneFrame->SetDimensions(dims[0], dims[1], 1);
  oneFrame->AllocateScalars(VTK_FLOAT,1);

  vtkSmartPointer<vtkImageData> MRI_Copy =
    vtkSmartPointer<vtkImageData>::New();
  MRI_Copy->DeepCopy(MRI_Reader->GetOutput());

  

  // Zone for template, and one frame image of MRI
  // Find the Z value of the ROI
  int Z_max = 0;
  int Z_min = 1000;
  for (int i = 0; i < dims[0]; i++)
    for (int j = 0; j < dims[1]; j++)
      for (int k = 0; k < dims[2]; k++)
        {
          short* template_pixel =
            static_cast<short*>(template_image->GetScalarPointer(i, j, k));
          float* MRI_Copy_pixel =
            static_cast<float*>(MRI_Copy->GetScalarPointer(i, j, k));

          if (template_pixel[0] == index[ROI_index])
            {
              // keep the MRI value, and get the range of Z
              if(Z_max < k)
                Z_max = k;
              if(Z_min > k)
                Z_min = k;
            }
            
          else if (MRI_Copy_pixel[0] != 0.0)
            MRI_Copy_pixel[0] = 0.0;// so it will show the outline
        }

  for(int i = 0; i < dims[0]; i++)
    for (int j = 0; j < dims[1]; j++)
      for (int k = 0; k < dims[2]; k++)
        {
          float* oneFrame_pixel =
            static_cast<float*>(oneFrame->GetScalarPointer(i, j, 0));
          float* MRI_Copypixel =
            static_cast<float*>(MRI_Copy->GetScalarPointer(i, j, k));
          if (k == Z_min)
            {
              float* MRI_pixel =
                static_cast<float*>(MRI_image->GetScalarPointer(i, j, k));
              oneFrame_pixel[0] = MRI_pixel[0];
            }
          if (k < Z_min)
            MRI_Copypixel[0] = 0.0;
        }



         
            

  std::cout << Z_min << " " << Z_max << std::endl;

  vtkSmartPointer<vtkVolume> MRI_ROI_volume =
    vtkSmartPointer<vtkVolume>::New();
  vtkSmartPointer<vtkImageActor> imageActor =
    vtkSmartPointer<vtkImageActor>::New();

  // my interactorStyle
  vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle =
    vtkSmartPointer<myVtkInteractorStyleImage>::New();

  // Create the renderers, render window, and interactor

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();

  myInteractorStyle->_imageActor = imageActor;
  myInteractorStyle->SetRender(ren);
  myInteractorStyle->_MRI_Copy = MRI_Copy;
  myInteractorStyle->_oneFrame = oneFrame;
  myInteractorStyle->_MRI_image = MRI_image;
  myInteractorStyle->_MRI_ROI_volume = MRI_ROI_volume;
  myInteractorStyle->_imageActor = imageActor;
  myInteractorStyle->_MinSlice = Z_min;
  myInteractorStyle->_MaxSlice = Z_max;

  renWin->AddRenderer(ren);
  iren->SetRenderWindow(renWin);
  iren->SetDesiredUpdateRate(frameRate / (1+clip));
  iren->GetInteractorStyle()->SetDefaultRenderer(ren);
  iren->SetInteractorStyle(myInteractorStyle);

  
  renWin->SetSize(600, 600);
  
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;



}
