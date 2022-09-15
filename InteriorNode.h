
#ifndef INTERIORNODE_H_INCLUDED
#define INTERIORNODE_H_INCLUDED
#include "Node.hpp"

class InteriorNode:
    public Node
{
    friend class FiniteDifferenceGrid;
    friend class BvpOde;
protected:
    int north_, south_,east_,west_ ={0};
public:
    InteriorNode(int globalIndex,double coordX,double coordY):Node(globalIndex,coordX,coordY)
    {};
    virtual ~InteriorNode() = default;

};

#endif // INTERIORNODE_H_INCLUDED
