/*=========================================================================
  Program:   Visualization Toolkit
  Module:    vtkSphere.h
  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.
     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#ifndef vtkMy_h
#define vtkMy_h

#include <vtkCommonDataModelModule.h> // For export macro
#include <vtkImplicitFunction.h>
#include <vtkMath.h>

class VTKCOMMONDATAMODEL_EXPORT vtkSphere : public vtkImplicitFunction
{
public:
  vtkTypeMacro(vtkSphere, vtkImplicitFunction);
  /**
   * Construct sphere with center at (0,0,0) and radius=0.5.
   */
  static vtkSphere *New();

  //@{
  /**
   * Evaluate sphere equation ((x-x0)^2 + (y-y0)^2 + (z-z0)^2) - R^2.
   */
  double EvaluateFunction(double x[3]) VTK_OVERRIDE;
  double EvaluateFunction(double x, double y, double z)
    {return this->vtkImplicitFunction::EvaluateFunction(x, y, z); } ;
  //@}

  /**
   * Evaluate sphere gradient.
   */
  void EvaluateGradient(double x[3], double n[3]) VTK_OVERRIDE;


protected:
  vtkSphere();
  ~vtkSphere() VTK_OVERRIDE {};

private:
  //vtkSphere(const vtkSphere&) VTK_DELETE_FUNCTION;
  //void operator=(const vtkSphere&) VTK_DELETE_FUNCTION;
};



//vtkStandardNewMacro(vtkSphere);

//----------------------------------------------------------------------------
// Construct sphere with center at (0,0,0) and radius=0.5.
vtkSphere::vtkSphere()
{
  
}

//----------------------------------------------------------------------------
// Evaluate sphere equation F(x, y, z) = x^2+ 3xy + y^2 – (cos z + 1)
double vtkSphere::EvaluateFunction(double x[3])
{
  return (  (x[0]) * (x[0]) + 3.0*(x[0]) * (x[1]) + (x[1]) * (x[1]) - (cos(x[2])+1));
}

//----------------------------------------------------------------------------
// Evaluate sphere gradient.
void vtkSphere::EvaluateGradient(double x[3], double n[3])
{
  n[0] = 2.0 * (x[0]) + 3.0 * (x[1]);
  n[1] = 3.0 * (x[0]) + 2.0 * (x[1]);
  n[2] = sin(x[2]);
}

//----------------------------------------------------------------------------


#endif
