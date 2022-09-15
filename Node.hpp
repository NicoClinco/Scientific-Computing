#ifndef NODEHEADERDEF
#define NODEHEADERDEF

class Node
{
    friend class FiniteDifferenceGrid;
    friend class BvpOde;
    friend class BoundaryConditions;
protected:
    int globalIndx_;
    double u_;
    // int north_, south_,east_,west_ ={0};
public:

   double coordinateX_;
   double coordinateY_;

   Node(int globalIndx,
        double coordX,
        double coordY):globalIndx_(globalIndx),
                       coordinateX_(coordX),
                       coordinateY_(coordY)
    {};

    virtual ~Node() = default;



};

#endif
//Code from Chapter12.tex line 566 save as Node.hpp
