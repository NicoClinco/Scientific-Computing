#include <cassert>
#include "BoundaryConditions.hpp"

bool BoundaryConditions::SetTopBoundaryCond(double (*funcTop)(double,double))
{
    for (BoundaryNode* _bN : TopBoundary_){
        double x = _bN->coordinateX_;
        double y = _bN->coordinateY_;
        _bN->u_ = funcTop(x,y);
    }
    return true;
};

bool BoundaryConditions::SetBottomBoundaryCond(double (*funcBottom)(double,double))
{
    for (BoundaryNode* _bN : BottomBoundary_){
        double x = _bN->coordinateX_;
        double y = _bN->coordinateY_;
        _bN->u_ = funcBottom(x,y);
    }
    return true;

}

bool BoundaryConditions::SetRightBoundaryCond(double (*funcRight)(double,double))
{
    for (BoundaryNode* _bN : RightBoundary_){
        double x = _bN->coordinateX_;
        double y = _bN->coordinateY_;
        _bN->u_ = funcRight(x,y);
    }
  return true;
}

bool BoundaryConditions::SetLeftBoundaryCond(double (*funcLeft)(double,double))
{
    for (BoundaryNode* _bN : LeftBoundary_){
        double x = _bN->coordinateX_;
        double y = _bN->coordinateY_;
        _bN->u_ = funcLeft(x,y);
    }
    return true;
}
bool BoundaryConditions::SetTheBC
(
 double (*funcTop)(double,double) ,
 double (*funcBottom)(double,double),
 double (*funcRight)(double,double),
 double (*funcLeft)(double,double)
)
{
    SetTopBoundaryCond(funcTop);
    SetBottomBoundaryCond(funcBottom);
    SetRightBoundaryCond(funcRight);
    SetLeftBoundaryCond(funcLeft);
    return true;
}



