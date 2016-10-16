/*=========================================================================
  Program:   Visualization Toolkit
  Module:    vtkSphere.cxx
  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.
     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
=========================================================================*/
#include "vtkMyFunction.h"
#include <vtkMath.h>
//#include <vtkObjectFactory.h>

vtkStandardNewMacro(vtkSphere1);

//----------------------------------------------------------------------------
// Construct sphere with center at (0,0,0) and radius=0.5.
vtkSphere1::vtkSphere()
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
  return ( return ( ((x[0]) * (x[0]) +
           3.0*(x[0]) * (x[1]) +
           (x[1]) * (x[1]) -
	    (cos(x[2])+1));
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
