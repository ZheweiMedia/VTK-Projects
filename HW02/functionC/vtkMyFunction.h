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
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;

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

  //@{
  /**
   * Set / get the radius of the sphere. The default is 0.5.
   */
  vtkSetMacro(Radius,double);
  vtkGetMacro(Radius,double);
  //@}

  //@{
  /**
   * Set / get the center of the sphere. The default is (0,0,0).
   */
  vtkSetVector3Macro(Center,double);
  vtkGetVectorMacro(Center,double,3);
  //@}

  //@{
  /**
   * Create a bounding sphere from a set of points. The set of points is
   * defined by an array of doubles, in the order of x-y-z (which repeats for
   * each point).  An optional hints array provides a guess for the initial
   * bounding sphere; the two values in the hints array are the two points
   * expected to be the furthest apart. The output sphere consists of a
   * center (x-y-z) and a radius.
   */
protected:
  vtkSphere();
  ~vtkSphere() VTK_OVERRIDE {}

  double Radius;
  double Center[3];

private:
  //vtkSphere(const vtkSphere&) VTK_DELETE_FUNCTION;
  //void operator=(const vtkSphere&) VTK_DELETE_FUNCTION;
};



//vtkStandardNewMacro(vtkSphere);

//----------------------------------------------------------------------------
// Construct sphere with center at (0,0,0) and radius=0.5.
vtkSphere::vtkSphere()
{
  this->Radius = 0.5;

  this->Center[0] = 0.0;
  this->Center[1] = 0.0;
  this->Center[2] = 0.0;
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
void vtkSphere::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "Radius: " << this->Radius << "\n";
  os << indent << "Center: (" << this->Center[0] << ", "
     << this->Center[1] << ", " << this->Center[2] << ")\n";
}


#endif
