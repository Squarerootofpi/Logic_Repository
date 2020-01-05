#ifndef LOGICTREE_H
#define LOGICTREE_H
#include"Scanner.h"
#include"Graph.h"

class LogicTree
{
private:
	vector<Proposition> thePropositions;
	set<size_t> axioms;
	vector<string> sources;
	set<size_t> IDs;
	//vector<set<size_t>> adjList;
	Graph tree;
public:
	LogicTree();
	~LogicTree();
	LogicTree(vector<Proposition> props, set<size_t> axs, vector<string> srcs, set<size_t> givenIDs, vector<set<size_t>> adjList);

	string toString();
};

LogicTree::LogicTree()
{
}

LogicTree::LogicTree(vector<Proposition> props, set<size_t> axs, vector<string> srcs, set<size_t> givenIDs, vector<set<size_t>> adjList)
	: thePropositions(props), axioms(axs), sources(srcs), IDs(givenIDs)
{
	Graph g(adjList);
	tree = g;
}

LogicTree::~LogicTree()
{
}

string LogicTree::toString() {
	return "LogicTree toString not implemented" + '\n';
}

#endif // !LOGICTREE_H
