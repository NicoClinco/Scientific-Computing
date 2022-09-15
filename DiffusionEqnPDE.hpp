#ifndef DIFFUSIONEQNPDEHEADERDEF
#define DIFFUSIONEQNPDEHEADERDEF

class DiffusionEqnPDE
{
   // The boundary value class is able to
   // access the coefficients etc. of this equation
   friend class BvpOde;

private:
   // Coefficients on LHS of ODE
   double mCoeffOfUxx;
   double mCoeffOfUyy;

   // Function on RHS of PDE
   double (*mpRhsFunc)(double x,double y); // --> Pointer to a f(x,y) :rhs

   // Interval for domain
   double mXmin;
   double mXmax;
   double mYmin;
   double mYmax;

public:
   DiffusionEqnPDE(double coeffUxx, double coeffUyy,
             double (*righthandSide)(double,double),
                   double xMinium, double xMaxium,
                    double yMinium, double yMaxium):
                                                    mCoeffOfUxx(coeffUxx),
                                                    mCoeffOfUyy(coeffUyy),
                                                    mpRhsFunc{*righthandSide},
                                                    mXmin(xMinium),
                                                    mXmax(xMaxium),
                                                    mYmin(yMinium),
                                                    mYmax(yMaxium)
   {};
};

#endif
//Code from Chapter12.tex line 456 save as SecondOrderOde.hpp
