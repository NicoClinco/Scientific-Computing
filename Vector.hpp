#ifndef VECTORHEADERDEF
#define VECTORHEADERDEF

#include <iostream>
#include <vector>

class Vector
{
private:
   double* mData; // data stored in vector
   int mSize; // size of vector
   int CheckIndex(int i,int Imin,int Imax) const ;

public:
   Vector(){};
   Vector(const Vector& otherVector);
   Vector(int size);
   ~Vector();
   int GetSize() const;
   double& operator[](int i); // zero-based indexing

   double Read(int i) const; //Read only-based access
   double& operator()(int i); // one-based indexing
   // assignment
   Vector& operator=(const Vector& otherVector);
   Vector operator+() const; // unary +
   Vector operator-() const; // unary -
   Vector operator+(const Vector& v1) const; // binary +
   Vector operator-(const Vector& v1) const; // binary -
   // scalar multiplication
   Vector operator*(double a) const;
   // p-norm method
   double CalculateNorm(int p=2) const;
   // declare length function as a friend
   friend std::ostream& operator<<(std::ostream& output,const Vector& v);

   friend int length(const Vector& v);
};

// Prototype signature of length() friend function
int length(const Vector& v);

#endif
//Code from Chapter10.tex line 20 save as Vector.hpp
