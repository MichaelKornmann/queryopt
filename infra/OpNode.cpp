#include "OpNode.h"
#include <iostream>

OpNode::id OpNode::count = 0;

OpNode::OpNode()
{
    _nType = OpNode::relation;
    _left = NULL;
    _right = NULL;
    _nId = count;
    OpNode::count++;
}

OpNode::OpNode(const OpNode::id nId)
{
    _nType = OpNode::relation;
    _left = nullptr;
    _right = nullptr;
    _nId = nId;    
}

void OpNode::writeToFile(std::ofstream &os) const
{
    os <<"(" << " " << this->_nId << " "; 
 
    // To-Do print node data
    
    if( getLeft() != nullptr)
    {
        getLeft()->writeToFile(os);
    }
    else
    {
        os << "NULL" << " ";    
    }

    if( getRight() != nullptr)
    {
        getRight()->writeToFile(os);
    }
    else
    {
        os << "NULL" << " ";
    }

    os << ")" << " ";
    
}


