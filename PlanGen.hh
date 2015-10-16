#ifndef PLANGEN_HH
#define PLANGEN_HH
#include "Infra/OpNode.h"
#include "Infra/QueryGraphWithNumbers.h"
#include "Infra/General/Reservoir.hh"
#include "Infra/General/bit_subsets.hh"

template<class Tcost>
class PlanGen {
public:
	typedef OpNode tree_t;
	typedef QueryGraphWithNumbers graph_t;
	typedef std::vector<OpNode*> opnode_vt;
public:
	PlanGen() : _reservoir(10) {}
	~PlanGen() {}
public:
    void setCostFunction(Tcost *_cost);

protected:
    virtual tree_t* execute(const opnode_vt &set) = 0;
    OpNode *createJoinTree(tree_t *t_1, tree_t *t_2, bool rightDeepOnly, bool leftDeepOnly);
protected:
	Tcost *_cost;
    graph_t *_data;
private:
    inline OpNode* join(tree_t *t_1, tree_t *t_2);
private:
	Reservoir<OpNode> _reservoir;
};

template<class Tcost>
void
PlanGen<Tcost>::setCostFunction(Tcost *_cost)
{
    this->_cost = _cost;
}

template<class Tcost>
OpNode*
PlanGen<Tcost>::join(tree_t *t_1, tree_t *t_2)
{
    OpNode *node = _reservoir.get_new_entry();
    node->setType(OpNode::join);
    node->setCost(0.0);
    node->setLeft(t_1);
    node->setRight(t_2);
    return node;
}

template<class Tcost>
OpNode*
PlanGen<Tcost>::createJoinTree(tree_t *t_1, tree_t *t_2, bool rightDeepOnly, bool leftDeepOnly)
{
    tree_t *cheapest = NULL;
    if(!rightDeepOnly)
    {
        tree_t *result = this->join(t_1,t_2);
        if(cheapest == NULL || cheapest->getCost() > result->getCost())
        {
            cheapest = result;
        }
    }
    if(!leftDeepOnly)
    {
        tree_t *result = this->join(t_2,t_1);
        if(cheapest == NULL || cheapest->getCost() > result->getCost())
        {
            cheapest = result;
        }
    }
    return cheapest;
}


#endif

