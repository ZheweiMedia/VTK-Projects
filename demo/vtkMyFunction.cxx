/*=========================================================================

=========================================================================*/
#include "vtkMyFunction.h"
#include <vtkMath.h>
#include <vtkObjectFactory.h>

vtkStandardNewMacro(vtkMyFunction);

//----------------------------------------------------------------------------
// Construct sphere with center at (0,0,0) and radius=0.5.
vtkMyFunction::vtkMyFunction()
{
  
}

//----------------------------------------------------------------------------
// Evaluate equation F(x, y, z) = x^2+ 3xy + y^2 – (cos z + 1)
double vtkMyFunction::EvaluateFunction(double x[3])
{
  return ( ((x[0]) * (x[0]) +
           3.0*(x[0]) * (x[1]) +
           (x[1]) * (x[1]) -
	    (cos(x[2])+1));
}

//----------------------------------------------------------------------------
// Evaluate sphere gradient.
void vtkMyFunction::EvaluateGradient(double x[3], double n[3])
{
  n[0] = 2.0 * (x[0]) + 3.0 * (x[1]);
  n[1] = 3.0 * (x[0]) + 2.0 * (x[1]);
  n[2] = sin(x[2]);
}
