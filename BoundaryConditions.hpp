#ifndef BOUNDARYCONDITIONSHEADERDEF
#define BOUNDARYCONDITIONSHEADERDEF

#include <iostream>
#include <vector>
#include "FiniteDifferenceGrid.h"

class BoundaryConditions
{
public:
   // The boundary value class is able to
   // access the coefficients etc. of this equation
   friend class BvpOde;
   friend class FiniteDifferenceGrid;
private:
    FiniteDifferenceGrid& mesh_; //Reference to the _mesh_

    std::vector<BoundaryNode*> TopBoundary_;
    std::vector<BoundaryNode*> BottomBoundary_;
    std::vector<BoundaryNode*> LeftBoundary_;
    std::vector<BoundaryNode*> RightBoundary_;

public:

   BoundaryConditions(FiniteDifferenceGrid& Mesh):
                                            mesh_(Mesh)
   {
     for (BoundaryNode* _bNode : mesh_.BoundaryNodes){

        if (_bNode->coordinateY_ == mesh_.yLength_ )
            TopBoundary_.push_back(_bNode);

        if (_bNode->coordinateY_ == 0.0 )
            BottomBoundary_.push_back(_bNode);

        if (_bNode->coordinateX_ == mesh_.xLength_)
            RightBoundary_.push_back(_bNode);

        if (_bNode->coordinateX_ == 0)
            LeftBoundary_.push_back(_bNode);

     }

   };

   bool SetTopBoundaryCond(double (*funcTop)(double,double));

   bool SetBottomBoundaryCond(double (*funcBottom)(double,double));

   bool SetRightBoundaryCond(double (*funcRight)(double,double));

   bool SetLeftBoundaryCond(double (*funcLeft)(double,double));

   bool SetTheBC
   (
    double (*funcTop)(double,double),
    double (*funcBottom)(double,double),
    double (*funcRight)(double,double),
    double (*funcLeft)(double,double)
    );

};

#endif

