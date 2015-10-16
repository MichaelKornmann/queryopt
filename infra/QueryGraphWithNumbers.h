#ifndef QUERYGRAPHWITHNUMBERS_H
#define QUERYGRAPHWITHNUMBERS_H
#include "QueryGraph.h"

class QueryGraphWithNumbers : public QueryGraph {


public:
	typedef uint32_t cardinality;
	// associate a cardinality with each node
    // in the example shown below holds R_{0} = 1, R_{1} = 4 and so on ...
    typedef std::vector<cardinality> cardinalityvector;
    // associate a selectivity with each predicate
    // f_{i,j} = f_{j,i} 
    // in the example shown below holds f_{0,2} = 0.2 
	typedef std::vector<std::vector<double>> selectivityvector;


    // sample values:
    //
    // cardinalityvector:  1, 4, 5, 2, 1
    //
    // selectivityvector: (2) 0.20   (3)  0.23   etc...
    //                    (3) 0.10   (4)  0.01   
    //                    (5) 0.30   (50) 0.10           
    //                    (7) 0.20   (99) 0.02              
    //                    (8) 0.12

public:
	QueryGraphWithNumbers(){}
	QueryGraphWithNumbers(const size_t n);
	~QueryGraphWithNumbers(){}
	


private:
	cardinalityvector _cvector;
	selectivityvector _svector;

};

#endif
