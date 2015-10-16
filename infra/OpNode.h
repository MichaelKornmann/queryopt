#ifndef OPNODE_H
#define OPNODE_H
#include <fstream>
#include <vector>

class OpNode {


typedef size_t id;

public:
	OpNode();
    OpNode(const id nId);
	~OpNode(){}

public:
    enum type {join, relation};

public:
    void writeToFile(std::ofstream &output) const;
	
    inline OpNode *getLeft() const
	{
		return _left;
	}
	
	inline OpNode *getRight() const
	{
		return _right;
	}
	
	inline const id getID() const
	{
        return _nId;
	}

	inline void setID(const id nId)
	{
		_nId = nId;
	}	
	
	inline void setLeft(OpNode *nTree)
	{
		_left = nTree;	
	}

	inline void setRight(OpNode *nTree)
    {
        _right = nTree;
    }

    inline void setCost(const float nCost)
	{
		_nCost = nCost;
	}
	
	inline const float getCost() const
	{
		return _nCost;	
	}

    inline bool isRelation() const
    {
        return (this->_nType == relation);
    }
	
    inline void setType(const type nType) 
    {
        _nType = nType;
    }

private:
	OpNode *_left; 
	OpNode *_right;
	id _nId;
	float _nCost;
    type _nType;
    static id count;

};

#endif
