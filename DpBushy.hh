#ifndef DPBUSHY_HH
#define DPBUSHY_HH
#include "PlanGen.hh"
#include <random>

template <class Tcost>
class DpBushy : public PlanGen<Tcost> {
public:
	typedef OpNode tree_t;
	typedef uint32_t              set_t;
	typedef std::vector<OpNode*>  opnode_vt;
public:
	DpBushy(){}
	~DpBushy(){}
public:
	tree_t* execute(const opnode_vt &set);
public:
	static opnode_vt* generateRandomSet(size_t size); 	
};

template <class Tcost>
typename DpBushy<Tcost>::tree_t*
DpBushy<Tcost>::execute(const opnode_vt &set)
{   
   	size_t size = set.size();
  	size_t lastElem = (1 << size) - 1;
   	tree_t *bestTree[lastElem];
   	for(set_t i = 0 ; i < size ; ++i)
   	{
   		bestTree[(1 << i)] = *(&set[i]);
   	}
	for(set_t s = 1 ; s < lastElem ; ++s)
   	{
   		if(bestTree[s] != nullptr)
		{ 
		    continue;	
		}
		for (BvTrueNonEmptySubsets<uint32_t> s_1(s); s_1.isValid() ; ++s_1)
		{
			// s_2 = s/s_1
			set_t s_2 = s|(!(*s_1));
			tree_t *currTree = this->createJoinTree(bestTree[*s_1], bestTree[s_2], true, true);
			if( (bestTree[s] == nullptr) || bestTree[s]->getCost() > currTree->getCost()) 
			{
				bestTree[s] = currTree;
			}			
		}
	}
	return bestTree[lastElem];
}

template <class Tcost>
typename DpBushy<Tcost>::opnode_vt*
DpBushy<Tcost>::generateRandomSet(size_t size)
{
	opnode_vt *set = new opnode_vt;
	std::random_device rd;
    	std::mt19937 gen(rd());
    	std::uniform_real_distribution<> dis(0,1);
	for (size_t i = 0 ; i < size ; i++)
	{
		tree_t *tree = new tree_t(i);
		tree->setCost(dis(gen));	
		set->push_back(tree);
	}
	return set;
}


#endif
