/*********************************************************
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************/

#include <vtkSmartPointer.h>
#include <vtkNIFTIImageReader.h>
#include <vtkImageResample.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeProperty.h>
#include <sstream>
#include <vtkSmartVolumeMapper.h>
#include <vtkImageData.h>


vtkSmartPointer<vtkImageData>
       reader_rescale(std::string, const double, double*);


vtkSmartPointer<vtkVolumeProperty>
       property(const double, const double, const bool, const char);




//

vtkSmartPointer<vtkImageData>
reader_rescale(std::string fileName, double* range)
{
  vtkAlgorithm *reader;
  vtkImageData *input;

  vtkSmartPointer<vtkNIFTIImageReader> niiReader =
    vtkSmartPointer<vtkNIFTIImageReader>::New();
  niiReader->SetFileName(fileName.c_str());
  niiReader->Update();
  input = niiReader->GetOutput();
  reader = niiReader;

  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->ShallowCopy(niiReader->GetOutput());
  image->GetScalarRange(range);

  vtkSmartPointer<vtkImageShiftScale> shiftScaleFilter = 
    vtkSmartPointer<vtkImageShiftScale>::New();
  
  shiftScaleFilter->SetInputConnection(niiReader->GetOutputPort());
  shiftScaleFilter->SetShift(-range[0]);
  shiftScaleFilter->SetScale(255/(range[1]-range[0]));
  shiftScaleFilter->SetOutputScalarTypeToFloat();
  shiftScaleFilter->Update();

  image->ShallowCopy(shiftScaleFilter->GetOutput());

  return image;
}





vtkSmartPointer<vtkVolumeProperty> property(const double opacity_Bottom,
                                            const double opacity_Top,
                                            const bool independentComponents,
                                            const char color)
{
  vtkSmartPointer<vtkPiecewiseFunction> oTFun =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
  vtkSmartPointer<vtkColorTransferFunction> cTFun =
    vtkSmartPointer<vtkColorTransferFunction>::New();
  vtkSmartPointer<vtkVolumeProperty> property =
    vtkSmartPointer<vtkVolumeProperty>::New();

  oTFun->AddPoint(opacity_Bottom, 0.2);
  oTFun->AddPoint(opacity_Top-0.1, 0.99);
  oTFun->AddPoint(opacity_Top, 1.0);
  std::cout << opacity_Top << std::endl;


  cTFun->AddRGBPoint(0.0, 1.0, 1.0, 1.0);
  if (color == 'R')
    cTFun->AddRGBPoint(255.0, 1.0, 0.0, 0.0);
  else if (color == 'G')
    cTFun->AddRGBPoint(255.0, 0.0, 1.0, 0.0);
  else
    {
      cTFun->AddRGBPoint(255.0, 0.0,0.0, 1.0);
    }

  property->SetScalarOpacity(oTFun);
  property->SetColor(cTFun);
  property->SetInterpolationTypeToLinear();
  property->SetIndependentComponents(independentComponents);

  return property;
}


