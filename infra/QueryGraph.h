#ifndef QUERYGRAPH_H
#define QUERYGRAPH_H
#include <vector>
#include <fstream>
#include <string>

class QueryGraph {

public:
	typedef size_t id;
	typedef std::vector<id> nodevector;
	typedef std::vector<nodevector> graphvector;

public:
	QueryGraph(){}
	QueryGraph(const size_t n);
	~QueryGraph(){}

public:
	bool hasEdge(const id nodeId1, const id nodeId2) const;
	void addEdge(const id nodeId1, const id nodeId2);
	void removeEdge(const id nodeId1, const id nodeId2);
	void formStarQuery();
	void formChainQuery();
	void formCliqueQuery();
	void formCircleQuery();
	void formRandomQuery();
	void clear();
	void depthFirstVisit(id nodeId, std::vector<bool> &v) const;
	bool breadthIsConnected() const;
	bool depthIsConnected() const;
	const nodevector &getAdjacentNodes(id nodeId) const;
	void writeToFile(std::ofstream &output) const;
	void readFromFile(std::ifstream &input);
	
	inline graphvector &getGraphVector()
	{
		return this->_gvector;
	}

	void formCyclicQuery();
	void formGridQuery();
	void formTreeQuery();
	static int getSelectivity(size_t cardinality1, size_t cardinality2);
	void writeGraphToFile(std::ofstream &output) const;
	void createFromFile(std::ifstream &input);
	static int measureExecutionTime(QueryGraph *graph, bool (QueryGraph::*fptr)()const, std::string methodName);

public:
	graphvector _gvector; 

private:
	void addAdjacentNode(const id nodeId1, const id nodeId2);
	void removeAdjacentNode(const id nodeId1, const id nodeId2);	
};

#endif
