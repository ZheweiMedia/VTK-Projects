








/*=========================================================================
For HW02 3.c

F(x, y, z) = x^2+ 3xy + y^2 – (cos z + 1)

For F is not a quadric function. We need to implement our own funcion

Zhewei @ 10/15/2016
=========================================================================*/


#ifndef vtkMyFunction_h
#define vtkMyFunction_h

#include <vtkCommonDataModelModule.h> // For export macro
#include <vtkImplicitFunction.h>

class VTKCOMMONDATAMODEL_EXPORT vtkMyFunction : public vtkImplicitFunction
{
public:
  vtkTypeMacro(vtkMyFunction, vtkImplicitFunction);
  
  static vtkMyFunction *New();

  //@{
  /**
   * Evaluate  equation F(x, y, z) = x^2+ 3xy + y^2 – (cos z + 1)
   */
  double EvaluateFunction(double x[3]) VTK_OVERRIDE;
  double EvaluateFunction(double x, double y, double z)
    {return this->vtkImplicitFunction::EvaluateFunction(x, y, z); } ;
  //@}

  /**
   * Evaluate function gradient.
   */
  void EvaluateGradient(double x[3], double n[3]) VTK_OVERRIDE;
  

protected:
  vtkMyFunction();
  ~vtkMyFunction() VTK_OVERRIDE {}

private:
  //vtkMyFunction(const vtkMyFunction&) VTK_DELETE_FUNCTION;
  //void operator=(const vtkMyFunction&) VTK_DELETE_FUNCTION;
};

#endif
*/
