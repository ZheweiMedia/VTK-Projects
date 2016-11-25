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

vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>
       reader_to_mapper(std::string, double);
vtkSmartPointer<vtkVolumeProperty>
property(double, double, bool, char);







//

vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>
reader_to_mapper(std::string fileName, double reductionFactor)
{
  vtkAlgorithm *reader;
  vtkImageData *input;

  vtkSmartPointer<vtkNIFTIImageReader> niiReader =
    vtkSmartPointer<vtkNIFTIImageReader>::New();
  niiReader->SetFileName(fileName.c_str());
  niiReader->Update();
  input = niiReader->GetOutput();
  reader = niiReader;

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
  mapper->SetBlendModeToMaximumIntensity();
  if (reductionFactor < 1.0)
    mapper->SetInputConnection(resample->GetOutputPort());
  else
    mapper->SetInputConnection(reader->GetOutputPort());

  return mapper;
}


vtkSmartPointer<vtkVolumeProperty> property(double opacityLevel, double opacityWindow, bool independentComponents, char color)
{
  vtkSmartPointer<vtkPiecewiseFunction> oTFun =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
  vtkSmartPointer<vtkColorTransferFunction> cTFun =
    vtkSmartPointer<vtkColorTransferFunction>::New();
  vtkSmartPointer<vtkVolumeProperty> property =
    vtkSmartPointer<vtkVolumeProperty>::New();

  oTFun->AddSegment(opacityLevel - 0.5*opacityWindow, 0.0,
                    opacityLevel + 0.5*opacityWindow, 1.0);
  cTFun->AddRGBSegment(0.0, 1.0, 1.0, 1.0, 255.0, 1.0, 1.0, 1.0);
  cTFun->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
  if (color == 'R')
    cTFun->AddRGBPoint(255.0, 1.0, 0.0, 0.0);
  else if (color == 'G')
    cTFun->AddRGBPoint(255.0, 0.0, 1.0, 0.0);
  else
    cTFun->AddRGBPoint(255.0, 0.0, 0.0, 1.0);

  property->SetScalarOpacity(oTFun);
  property->SetColor(cTFun);
  property->SetInterpolationTypeToLinear();
  property->SetIndependentComponents(independentComponents);

  return property;
}


