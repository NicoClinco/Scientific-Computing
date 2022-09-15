#include <cassert>
#include "FiniteDifferenceGrid.h"
#include "BoundaryNode.h"
#include "Node.hpp"
#include "InteriorNode.h"

FiniteDifferenceGrid::FiniteDifferenceGrid(int numNodesX, int numNodesY,double xMin,
                                              double xMax,double yMin,double yMax)
{
   double stepsizeX = (xMax-xMin)/((double)(numNodesX-1));
   double stepsizeY = (yMax - yMin)/((double)(numNodesY-1));

   int TotalNodes_ = numNodesX*numNodesY;

   numNodesX_ = numNodesX;
   numNodesY_ = numNodesY;

   xLength_ = xMax-xMin;
   yLength_ = yMax-yMin;

   xSize_ = stepsizeX;
   ySize_ = stepsizeY;

   int globalIndex = 0;
   std::cout << "Creating the mesh with :" <<TotalNodes_<< " nodes \n";
   for (int i=0;i<numNodesY;i++){
    for (int j=0;j<numNodesX;j++){
        double coordX = xMin + j*xSize_;
        double coordY = yMin + i*ySize_;
      if( i == 0 || j == 0  || i == numNodesY-1 || j == numNodesX-1 ){
             BoundaryNode* CurrentNode = new BoundaryNode(globalIndex,coordX,coordY);

             BoundaryNodes.push_back(CurrentNode);
             TotalNodes.push_back(CurrentNode);

      }else{
             InteriorNode* CurrentNode =new InteriorNode(globalIndex,coordX,coordY);

             InteriorNodes.push_back(CurrentNode);
             TotalNodes.push_back(CurrentNode);
      }


    globalIndex++;
    }

   }
   assert(globalIndex == TotalNodes_);
   EnrichThePoints();
}

bool FiniteDifferenceGrid::EnrichThePoints()
{
    for ( auto _intPoint : (*this).InteriorNodes )
    {
       _intPoint->north_ = _intPoint->globalIndx_ + numNodesX_;
       _intPoint->south_ = _intPoint->globalIndx_ - numNodesX_;
       _intPoint->east_  = _intPoint->globalIndx_ +1 ;
       _intPoint->west_  = _intPoint->globalIndx_ -1 ;

    }
    return true;
}

void FiniteDifferenceGrid::PrintInternalNodes() const {

    for ( const auto _intPoint : (*this).InteriorNodes ){
        std::cout<< "Node : " << _intPoint->globalIndx_ ;
        std::cout << " north :" << _intPoint->north_;
        std::cout<<"   south : " <<_intPoint->south_;
        std::cout<<"   west : " <<_intPoint->west_;
        std::cout<<" east: " <<_intPoint->east_<<std::endl;
    }

}



//Code from AppendixC.tex line 537 save as FiniteDifferenceGrid.cpp
