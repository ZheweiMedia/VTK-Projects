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


vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>
                reader_to_mapper(std::string, const double, double*);


vtkSmartPointer<vtkVolumeProperty>
       property(const double, const double, const bool, const char);




//

vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>
reader_to_mapper(std::string fileName, const double reductionFactor, double* range)
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

  vtkSmartPointer<vtkImageResample> resample =
    vtkSmartPointer<vtkImageResample>::New();
  if ( reductionFactor < 1.0)
    {
      resample->SetInputConnection(reader->GetOutputPort());
      resample->SetAxisMagnificationFactor(0, reductionFactor);
      resample->SetAxisMagnificationFactor(1, reductionFactor);
      resample->SetAxisMagnificationFactor(2, reductionFactor);
    }

  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> mapper =
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
  if (reductionFactor < 1.0)
    {
      mapper->SetInputConnection(resample->GetOutputPort());
      image->ShallowCopy(resample->GetOutput());
      image->GetScalarRange(range);
    }
  else
    {
      mapper->SetInputConnection(reader->GetOutputPort());
      image->ShallowCopy(niiReader->GetOutput());
      image->GetScalarRange(range);
    }
   mapper->SetBlendModeToMaximumIntensity();

  return mapper;
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

  oTFun->AddPoint(0.0, 0.0);
  oTFun->AddPoint(3000, 0.0);
  oTFun->AddPoint(7500, 1.0);
  oTFun->AddPoint(7500.1, 0.0);
  oTFun->AddPoint(10000.0, 0.0);


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


