#ifndef FINITEDIFFERENCEGRIDHEADERDEF
#define FINITEDIFFERENCEGRIDHEADERDEF

#include <vector>
#include <iostream>
#include "Node.hpp"
#include "BoundaryNode.h"
#include "InteriorNode.h"

class FiniteDifferenceGrid
{

   friend class BvpOde;
   friend class BoundaryConditions;

private:

   std::vector<Node*> TotalNodes;
   std::vector<InteriorNode*> InteriorNodes;
   std::vector<BoundaryNode*> BoundaryNodes;

   int TotalNodes_;
   int numNodesX_ ,numNodesY_;
   double xSize_,ySize_,xLength_,yLength_;

public:
   FiniteDifferenceGrid(int numNodesX, int numNodesY,double xMin,
                        double xMax,double yMin,double yMax);

   bool EnrichThePoints();

   void PrintInternalNodes() const ;





   friend std::ostream& operator<<(std::ostream& os, const FiniteDifferenceGrid& FDifferenceGrid){
    os << "Printing the mesh coordinate: \n ";
    os << " Coordinate X | Coordinate Y  \n";
    for (  Node* _node : FDifferenceGrid.TotalNodes ){
        os << (_node)->coordinateX_ << "   " ;
        os << (_node)->coordinateY_;
        os << " \n";
    }
    return os;
   }
};




#endif
//Code from Chapter12.tex line 582 save as FiniteDifferenceGrid.hpp
