#include <iostream>


// #include "FiniteDifferenceGrid.h"

#include "BvpOde.hpp"
#include <cmath>

double RightFunction(double x, double y){
    return -4*(1-x*x-y*y)*exp(-x*x-y*y);
}


double RightConds(double x, double y){
 return exp(-(1+y*y));
}
double TopConds(double x, double y){
    return exp(-4-x*x);
}
double BottomConds(double x, double y){
    return exp(-x*x);
}
double LeftConds(double x, double y){
    return exp(-y*y);
}


int main()
{

    DiffusionEqnPDE PDE(1,1,RightFunction,0,1,0,2);

    FiniteDifferenceGrid fGrid(12,24,0,1,0,2);

    BoundaryConditions BCS(fGrid);

    BCS.SetBottomBoundaryCond(BottomConds);
    BCS.SetTopBoundaryCond(TopConds);
    BCS.SetRightBoundaryCond(RightConds);
    BCS.SetLeftBoundaryCond(LeftConds);


    BvpOde BoundaryProblem(&PDE,fGrid,BCS);

    BoundaryProblem.SetFilename("FirstProblem.txt");

    BoundaryProblem.Solve();




    return 0;
}
