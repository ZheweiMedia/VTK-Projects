#include <vtkSmartPointer.h>
#include <vtkImageData.h>

vtkSmartPointer<vtkImageData> ShowDifferentDirection
(vtkSmartPointer<vtkImageData>, int, int);




//functions
//

vtkSmartPointer<vtkImageData> ShowDifferentDirection
(vtkSmartPointer<vtkImageData> OriginalImage, int direction, int frameNo)
{
  int Original_3D[3];
  OriginalImage->>GetDimensions(Original_3D);
  vtkSmartPointer<vtkImageData> _2DImage =
    vtkSmartPointer<vtkImageData>::New();
  if (direction == 1)
    {
      int imageExtent[6] = { 0, Original_3D[0]-1, 0, Original_3D[1]-1, 0, 0 };
      _2DImage->SetExtent(imageExtent);
      _2DImage->AllocateScalars(VTK_DOUBLE, 1);

      for (int y = imageExtent[2]; y <= imageExtent[3]; y++)
        {
          for (int x = imageExtent[0]; x <= imageExtent[1]; x++)
            {
              double* _2D_pixel =
                static_cast<double*>(_2DImage->GetScalarPointer(x, y, 0));
              int* Or_pixel =
                static_cast<int*>(OriginalImage->GetScalarPointer(x,y,frameNo));
              _2D_pixel[0] = Or_pixel[0];
            }
        }
    }
  
}
