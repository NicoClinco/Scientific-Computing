#include <iostream>
#include <fstream>
#include <cassert>
#include "BvpOde.hpp"

BvpOde::BvpOde
(DiffusionEqnPDE* pPde,
 FiniteDifferenceGrid& Fgrid,
 BoundaryConditions& bCs):mpGrid(Fgrid),
                          mpBconds(bCs)
{
   mpPde = pPde;


   mNumNodesX_ = mpGrid.numNodesX_;
   mNumNodesY_ =mpGrid.numNodesY_;
   mNumNodes_ =mNumNodesX_*mNumNodesY_; //total nodes



   mpSolVec = new Vector(mNumNodes_);
   mpRhsVec = new Vector(mNumNodes_);
   mpLhsMat = new Matrix(mNumNodes_, mNumNodes_);

   mFilename = "PDE_OUTPUT.dat";
   mpLinearSystem = NULL;
}

BvpOde::~BvpOde()
{
   // Deletes memory allocated in constructor
   delete mpSolVec;
   delete mpRhsVec;
   delete mpLhsMat;
   // Only delete if Solve has been called
   if (mpLinearSystem)
   {
      delete mpLinearSystem;
   }
}

void BvpOde::Solve()
{
   PopulateMatrix();
   PopulateVector();
   //ApplyBoundaryConditions();
   // ApplyAllDirichlet();
   ApplyBoundaryConditions();
   mpLinearSystem = new LinearSystem(*mpLhsMat, *mpRhsVec); // The new calls the constructor of the Linear system
   *mpSolVec = mpLinearSystem->Solve();
    WriteSolutionFile();
}

void BvpOde::PopulateMatrix()
{
    for ( auto _intNode : mpGrid.InteriorNodes )
    {
        Node* North = mpGrid.TotalNodes[_intNode->north_];
        Node* South = mpGrid.TotalNodes[_intNode->south_];
        Node* East  = mpGrid.TotalNodes[_intNode->east_];
        Node* West  = mpGrid.TotalNodes[_intNode->west_];

        double x0 = _intNode->coordinateX_;
        double xN = North->coordinateX_;
        double xS = South->coordinateX_;
        double xE = East->coordinateX_;
        double xW = West->coordinateX_;

        double y0 = _intNode->coordinateY_;
        double yN = North->coordinateY_;
        double yS = South->coordinateY_;
        double yE = East->coordinateY_;
        double yW = West->coordinateY_;

        double alpha  = -2/((xE-x0)*(x0-xW))-2/((yN-y0)*(y0-yS));
        double alphaN = 2/((yN-yS)*(yN-y0));
        double alphaE = 2/((xE-xW)*(xE-x0));
        double alphaS = 2/((yN-yS)*(y0-yS));
        double alphaW = 2/((xE-xW)*(x0-xW));

         int NodeIndex  = _intNode->globalIndx_;
         int NorthIndex = North->globalIndx_;
         int SouthIndex = South->globalIndx_;
         int WestIndex = West->globalIndx_;
         int EastIndex = East->globalIndx_;

        (*mpLhsMat)(NodeIndex+1,WestIndex+1)   = alphaW;
        (*mpLhsMat)(NodeIndex+1,NodeIndex+1) = alpha;
        (*mpLhsMat)(NodeIndex+1,EastIndex+1) = alphaE;
        (*mpLhsMat)(NodeIndex+1,NorthIndex+1) = alphaN;
        (*mpLhsMat)(NodeIndex+1,SouthIndex+1) = alphaS;

    }

}

void BvpOde::PopulateVector()
{

   for (const auto _intNode : mpGrid.InteriorNodes){
    double x = _intNode->coordinateX_;
    double y = _intNode->coordinateY_;
    int indx = _intNode->globalIndx_;
    (*mpRhsVec)(indx+1) = mpPde->mpRhsFunc(x,y);
   }
}

/*
void BvpOde::ApplyAllDirichlet()
{
    for ( BoundaryNode* _bNode : mpGrid->BoundaryNodes)
    {
        int _BoundaryNode = _bNode->globalIndx_;

        (*mpLhsMat)(_BoundaryNode+1,_BoundaryNode+1) = 1.0;
        (*mpRhsVec)(_BoundaryNode+1) = 0.0; //Suppose that the boundary conditions are all zero.
    }

}
*/

void BvpOde::ApplyBoundaryConditions()
{

    for ( const BoundaryNode* _bNode : mpGrid.BoundaryNodes )
    {
        int _BoundaryNode = _bNode->globalIndx_;
        (*mpLhsMat)(_BoundaryNode+1,_BoundaryNode+1) = 1.0; //Dirichlet
        (*mpRhsVec)(_BoundaryNode+1) = _bNode->u_;
    }
}


void BvpOde::WriteSolutionFile()
{
   std::ofstream output_file(mFilename.c_str());
   assert(output_file.is_open());
   for (int i=0; i<mNumNodes_; i++)
   {
      double x = mpGrid.TotalNodes[i]->coordinateX_;
      double y = mpGrid.TotalNodes[i]->coordinateY_;
      output_file << "(";
      output_file << x << "," <<  y<< "): " << (*mpSolVec)(i+1) << "\n";
   }
   output_file.flush();
   output_file.close();
   std::cout<<"Solution written to "<<mFilename<<"\n";
}
//Code from AppendixC.tex line 560 save as BvpOde.cpp

