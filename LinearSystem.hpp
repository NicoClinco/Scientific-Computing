#ifndef LINEARSYSTEMHEADERDEF
#define LINEARSYSTEMHEADERDEF
#include "Vector.hpp"
#include "Matrix.hpp"

class LinearSystem
{
private:
   int mSize; // size of linear system
   Matrix* mpA;  // matrix for linear system
   Vector* mpb;  // vector for linear system

   // Only allow constructor that specifies matrix and
   // vector to be used.
   LinearSystem(const LinearSystem& otherLinearSystem){}; //disallow copy constructor
public:
   LinearSystem(const Matrix& A, const Vector& b);

   // destructor frees memory allocated
   virtual ~LinearSystem();

   // Method for solving system
   virtual Vector Solve();
};

#endif
//Code from AppendixC.tex line 314 save as LinearSystem.hpp
