#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageShiftScale.h>


vtkSmartPointer<vtkImageData> DifferentViews
(vtkSmartPointer<vtkImageData>, int, int);

vtkSmartPointer<vtkImageShiftScale> RescaleImage
(vtkSmartPointer<vtkImageData>);




//functions
//

vtkSmartPointer<vtkImageShiftScale> RescaleImage
(vtkSmartPointer<vtkImageData> OriginalImage)
{
  double _range[2];
  OriginalImage->GetScalarRange(_range);
  std::cout<<_range[0] << " " << _range[1] << std::endl;
  vtkSmartPointer<vtkImageShiftScale> _shift =
    vtkSmartPointer<vtkImageShiftScale>::New();
  _shift->SetInputData(OriginalImage);
  _shift->SetShift(-_range[0]);
  _shift->SetScale(255/(_range[1]-_range[0]));
  _shift->SetOutputScalarTypeToInt();
  _shift->Update();

  vtkSmartPointer<vtkImageData> check =
    vtkSmartPointer<vtkImageData>::New();
  check->ShallowCopy(_shift->GetOutput());
  check->GetScalarRange(_range);
  std::cout<<_range[0] << " " << _range[1] << std::endl;


  return _shift;
}



vtkSmartPointer<vtkImageData> DifferentViews
(vtkSmartPointer<vtkImageData> Original3D, int direction, int frameNo)
{
  int axis_3D[3];
  int X,Y,Z;
  Original3D->GetDimensions(axis_3D);
  X = axis_3D[0]-1;
  Y = axis_3D[1]-1;
  Z = axis_3D[2]-1;

  vtkSmartPointer<vtkImageData> _2DImage =
    vtkSmartPointer<vtkImageData>::New();

  if (direction == 1)
    {
      int imageExtent[6] = { 0, X, 0, Y, 0, 0 };
      _2DImage->SetExtent(imageExtent);
    }

  else if (direction == 2)
    {
      int imageExtent[6] = { 0, X, 0, Z, 0, 0 };
      _2DImage->SetExtent(imageExtent);
    }
    
  else if (direction == 3)
    {
      int imageExtent[6] = { 0, Y, 0, Z, 0, 0 };
      _2DImage->SetExtent(imageExtent);
    }
   
  _2DImage->AllocateScalars(VTK_DOUBLE, 1);

  if (direction == 1)
    {
      for (int i = 0; i <= X; i++)
        {
          for (int j = 0; j <= Y; j++)
            {
              double* _2D_pixel = static_cast<double*>
                (_2DImage->GetScalarPointer(i, j, 0));
              int* _Or_pixel = static_cast<int*>
                (Original3D->GetScalarPointer(i, j, frameNo));
              _2D_pixel[0] = _Or_pixel[0];
            }
        }
    }
  else if (direction == 2)
    {
      for (int i = 0; i <= X; i++)
        {
          for (int j = 0; j <= Z; j++)
            {
              double* _2D_pixel = static_cast<double*>
                (_2DImage->GetScalarPointer(i, j, 0));
              int* _Or_pixel = static_cast<int*>
                (Original3D->GetScalarPointer(i, frameNo, j));
              _2D_pixel[0] = _Or_pixel[0];
            }
        }
    }
  else if (direction == 3)
    {
      for (int i = 0; i <= Y; i++)
        {
          for (int j = 0; j <= Z; j++)
            {
              double* _2D_pixel = static_cast<double*>
                (_2DImage->GetScalarPointer(i, j, 0));
              int* _Or_pixel = static_cast<int*>
                (Original3D->GetScalarPointer(frameNo, i, j));
              _2D_pixel[0] = _Or_pixel[0];
            }
        }
    }

  return _2DImage;    
  
}
