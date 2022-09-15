# Finite-difference example code

This directory contains different classes which are useful to solve a simple 2D problem in a rectangle.
This work is the 2D-extension of the code explained in the book : "Guide To Scientific Computing in C++".

  

The classes vector, matrix are explained in the book
The class FiniteDifferenceGrid is responsable to create the rectangular mesh
The class DiffusionEqnPDE is an interface-class to handle the problem in general
The class BoundaryConditions allows to set Dirichlet Boundary condition specifies trough functions
The class BvpOde handles the problem and it contains a reference to the mesh and to the BoundaryConditions 


