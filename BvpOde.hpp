#ifndef BVPODEHEADERDEF
#define BVPODEHEADERDEF

#include <string>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "LinearSystem.hpp"
#include "FiniteDifferenceGrid.h"
#include "DiffusionEqnPDE.hpp"
#include "BoundaryConditions.hpp"

class BvpOde
{
private:
   // Only allow instance to be created from a PDE, boundary
   // conditions, and number of nodes in the mesh (the
   // copy constructor is private)
   // BvpOde(const BvpOde& otherBvpOde){}

   // Number of nodes in the grid
   int mNumNodesX_;
   int mNumNodesY_;
   int mNumNodes_; //total nodes

   FiniteDifferenceGrid& mpGrid;

   // Pointer to instance of an ODE
   DiffusionEqnPDE* mpPde;

   // Reference to the bconditions
   BoundaryConditions& mpBconds;

   // Vector for solution to unknowns
   Vector* mpSolVec;

   // Right-hand side vector
   Vector* mpRhsVec;

   // Matrix for linear system
   Matrix* mpLhsMat;

   // Linear system that arises
   LinearSystem* mpLinearSystem;

   // Allow user to specify the output file or
   // use a default name
   std::string mFilename;


   // Methods for setting up linear system and solving it
   void PopulateMatrix();
   void PopulateVector();
   // void ApplyBoundaryConditions();
   void ApplyAllDirichlet();

public:
    BvpOde(const BvpOde& otherBvpOde)=delete;

    BvpOde(DiffusionEqnPDE* pPde,FiniteDifferenceGrid& Fgrid,BoundaryConditions& bCs);
   // As memory is dynamically allocated the destructor
   // is overridden
   ~BvpOde();

   void SetFilename(const std::string& name)
   {
      mFilename = name;
   }
   void ApplyBoundaryConditions();
   void Solve();
   void WriteSolutionFile();
};

#endif
//Code from Chapter12.tex line 611 save as BvpOde.hpp
