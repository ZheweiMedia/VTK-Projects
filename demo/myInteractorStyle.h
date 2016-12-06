class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:
   static myVtkInteractorStyleImage* New();
   vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage);
   vtkImageData* _MRI;
   vtkImageData* _oneFrame;
   vtkVolume* _MRI_ROI_volume;
   vtmImageActor* _imageActor;
   int _MinSlice;
   int _MaxSlice;
 
protected:
   vtkImageViewer2* _ImageViewer;
   vtkTextMapper* _StatusMapper;
   
   int _Slice;
 
public:
   void SetRender(vtkRenderer* renderer) {
     _renderer = renderer;
     _Slice = _MinSlice;
     ShowFrame(_Slice);
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
               static_cast<float*>(oneFrame->GetScalarPointer(i, j, 0));
             float* MRI_Copypixel =
               static_cast<float*>(MRI_Copy->GetScalarPointer(i, j, k));
             if (k == FrameNo)
               {
                 float* MRI_pixel =
                   static_cast<float*>(MRI_image->GetScalarPointer(i, j, k));
                 oneFrame_pixel[0] = MRI_pixel[0];
               }
             if (k < FrameNo)
               MRI_Copypixel[0] = 0.0;
           }
     vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> MRI_ROI_mapper =
       vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
     MRI_ROI_mapper->SetInputData(MRI_Copy);
     MRI_ROI_mapper->SetBlendModeToMaximumIntensity();
  

     vtkSmartPointer<vtkVolumeProperty> MRI_ROI_Property =
       property(0, 255, independentComponents, 'B');

     
     _MRI_ROI_volume->SetMapper(MRI_ROI_mapper);
     _MRI_ROI_volume->SetProperty(MRI_ROI_Property);

  

     vtkSmartPointer<vtkImageResliceMapper> imageMapper =
       vtkSmartPointer<vtkImageResliceMapper>::New();
     imageMapper->SetInputData(oneFrame);

    
     _imageActor->GetMapper()->SetInputData(oneFrame);
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


