#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <chrono> 
#include <string>
#include <random>
#include "QueryGraph.h"
#include <cassert>

#include <iostream>

QueryGraph::QueryGraph(const size_t n) : _gvector(n)
{

}

bool QueryGraph::hasEdge(const id nodeId1, const id nodeId2) const
{
	assert(nodeId1<_gvector.size()&&nodeId2<_gvector.size());
	const nodevector &alist = _gvector.at(nodeId1);
	for(nodevector::const_iterator ait = alist.begin() ; ait != alist.end() ; ait++)
	{
		if(*ait == nodeId2)
		{
			return true;
		}
			
	}
	return false;
}

void QueryGraph::clear()
{
	for(graphvector::iterator git = _gvector.begin() ; git != _gvector.end() ; git++)
	{
		(*git).clear();
	}	
}

void QueryGraph::addEdge(const id nodeId1, const id nodeId2)
{
	assert(!this->hasEdge(nodeId1,nodeId2));
	this->addAdjacentNode(nodeId1,nodeId2);
	this->addAdjacentNode(nodeId2,nodeId1);
}

void QueryGraph::removeEdge(const id nodeId1, const id nodeId2)
{	
	assert(this->hasEdge(nodeId1,nodeId2));
	this->removeAdjacentNode(nodeId2, nodeId1);
	this->removeAdjacentNode(nodeId1, nodeId2);
}

void QueryGraph::formRandomQuery()
{
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disEdges(0, _gvector.size()-1);
	while(!depthIsConnected())
	{
		int nodeId1 = disEdges(gen);
		int nodeId2 = disEdges(gen);
		if(!this->hasEdge(nodeId1,nodeId2))
		{
			this->addEdge(nodeId1,nodeId2);
		}
	}
	for(int i = 0 ; i < 2*_gvector.size() ; i++)
	{
		int nodeId1 = disEdges(gen);
		int nodeId2 = disEdges(gen);
		if(!this->hasEdge(nodeId1,nodeId2))
		{
			this->addEdge(nodeId1,nodeId2);
		}
	}
}

void QueryGraph::formCliqueQuery()
{
	assert(_gvector.size()>1);
	for (int i = 0 ; i < _gvector.size() ; i++)
	{
		for (int j = 0 ; j < _gvector.size() ; j++)
		{
			if(i!=j)
			{
				_gvector[i].push_back(j);	
			}
		}
	}
}

void QueryGraph::formCircleQuery()
{
	assert(_gvector.size()>1);
	this->formChainQuery();
	(_gvector.end()-1)->push_back(0);
}

void QueryGraph::formStarQuery()
{
	assert(_gvector.size()>1);
	size_t count = 1;
	for (graphvector::iterator git = (_gvector.begin()+1) ; git != _gvector.end() ; git++)
	{
		(_gvector.begin())->push_back(count);
		count++;
		git->push_back(0);
	
	}
}

void QueryGraph::formChainQuery()
{
	size_t count = 0;
	for (graphvector::iterator git = _gvector.begin() ; git != _gvector.end() ; git++)
	{
		if((git+1) != _gvector.end())
		{
			git->push_back(count+1);
			(git+1)->push_back(count);
		}
		count++;
	}
}

void QueryGraph::addAdjacentNode(const id nodeId1, const id nodeId2)
{
	if(!hasEdge(nodeId1,nodeId2))
	{ 
		(_gvector.at(nodeId1)).push_back(nodeId2);
	}
}

void QueryGraph::removeAdjacentNode(const id nodeId1, const id nodeId2)
{
	if(!hasEdge(nodeId1,nodeId2))
	{
		return;
	}  
	nodevector &alist = (_gvector.at(nodeId1));
	for(nodevector::iterator ait = alist.begin() ; ait != alist.end() ; ait++)
	{
		if(*ait == nodeId2)
		{
			alist.erase(ait);
			return;
		}		
	}
}

const QueryGraph::nodevector &QueryGraph::getAdjacentNodes(id nodeId) const
{
	assert(nodeId<=_gvector.size());
	return _gvector.at(nodeId);
}

void QueryGraph::depthFirstVisit(id nodeId, std::vector<bool> &v) const
{
	const nodevector &alist = _gvector.at(nodeId);
	for(nodevector::const_iterator ait = alist.begin() ; ait != alist.end() ; ait++)
	{
		if(!v[*ait])
		{
			v[*ait]=true;
			this->depthFirstVisit(*ait,v);
		}
	}
}

bool QueryGraph::depthIsConnected() const
{
	std::vector<bool> v;
	int count = 0;
	for(int i = 0 ; i<_gvector.size() ; i++)
	{
		v.push_back(false);
	}
	for(int i = 0 ; i<_gvector.size() ; i++)
	{
		if(!v[i])
		{
			count++;
		}
		if(count>1)
		{
			return false;
		}
		else
		{
			v[i] = true;
			this->depthFirstVisit(i,v);
		}
	}
	return true;
}

bool QueryGraph::breadthIsConnected() const
{
	std::vector<bool> v;
	std::queue<id> q;
	int count = 0;
	for(int i = 0 ; i<_gvector.size() ; i++)
	{
		v.push_back(false);
	}
	for(int i = 0 ; i<_gvector.size() ; i++)
	{
		if(!v[i])
		{
			count++;
		}
		if(count>1)
		{
			return false;
		}
		else
		{
			q.push(i);
			v[i] = true;
			while(!q.empty())
			{
				int w = q.front();
				q.pop();
				const nodevector &alist = _gvector.at(w);
				for(nodevector::const_iterator ait = alist.begin() ; ait != alist.end() ; ait++)
				{
					if(!v[*ait])
					{
						v[*ait] = true;
						q.push(*ait);
					}
				}

			}
		}
	}
	return true; 
}

void QueryGraph::readFromFile(std::ifstream &input) 
{
    std::string line;
    while(getline(input,line))
    {
    	std::stringstream lineStream(line);
    	nodevector *alist = new nodevector;
    	std::string cell;    
		while( getline(lineStream,cell,',') )
		{

			id a = std::stoul(cell,NULL,0); 
			alist->push_back(a);
		}
		_gvector.push_back(*alist);
    }
}

void QueryGraph::writeToFile(std::ofstream &output) const
{
	for (graphvector::const_iterator git = _gvector.begin() ; git != _gvector.end() ; git++)
	{
		for(nodevector::const_iterator ait = (*git).begin() ; ait != (*git).end() ; ait++)
		{
			if((ait+1) == (*git).end())
			{
				output << *ait << std::endl; 
				break;
			}
			else
			{
				output << *ait << ",";
			}
		}
	}
}


void QueryGraph::formCyclicQuery()
{

}

void QueryGraph::formGridQuery()
{

}

void QueryGraph::formTreeQuery()
{

}

