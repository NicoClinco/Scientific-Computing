#ifndef BOUNDARYNODE_H_INCLUDED
#define BOUNDARYNODE_H_INCLUDED
#include "Node.hpp"

class BoundaryNode:
    public Node
{
    friend class FiniteDifferenceGrid;
    friend class BvpOde;
    protected:
        int NeatPointIndx;

public:
    BoundaryNode(int globalIndex,double coordX,double coordY):Node(globalIndex,coordX,coordY)
    {};
    virtual ~BoundaryNode() = default;
};


#endif // BOUNDARYNODE_H_INCLUDED
