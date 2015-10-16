#ifndef COST_HH
#define COST_HH
#include "Infra/OpNode.h"
#include "Infra/QueryGraphWithNumbers.h"

class Cost {

public:
	Cost(){}
	~Cost(){}
public:
	virtual double calculate(const OpNode &tree) const = 0;
<<<<<<< HEAD
    void setData(const QueryGraphWithNumbers *graph_t);
private:
    QueryGraphWithNumbers *_graph;     
    
};

=======
    	void setData(const QueryGraphWithNumbers *graph_t);
private:
    	QueryGraphWithNumbers *_graph;     
    
};

// change this to a constructor
>>>>>>> 44f0e9fcba0f96676bc8739926b1f6b6c377301a
void Cost::setData(QueryGraphWithNumbers *graph_t)
{
    this->_graph = graph_t;
}

#endif
