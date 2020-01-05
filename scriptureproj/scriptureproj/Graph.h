#ifndef GRAPH_H
#define GRAPH_H

#include<set>
#include<vector>
#include<map>
#include<algorithm>    // std::reverse
#include<string>
#include<sstream>

using std::set;
using std::map;
using std::vector;
using std::string;
using std::pair;
using std::ostringstream;
using std::endl;


class Node {
private:
	set<size_t> children; // these are the adjacencies for this particular node

	// other stuff probs
public: //some stuff here probs
	Node() {

	}
	Node(set<size_t> givenChildren) : children(givenChildren) {
		//children = givenChildren;
	}
	~Node() {

	}
	size_t size() {
		return children.size();
	}
	set<size_t> getChildren() const
	{
		return this->children;
	}
	//size_t& at(size_t index) {
	//	return 
	//}
};

class Graph {
private:
	map<size_t, Node> adjList; // this guy is our adjacency list
	vector<set<size_t>> sccVec;
	vector<size_t> postOrderNums; //They will be in reverse later.
	set<size_t> visitedList;
	//vector<size_t> p

public: //public stuff
	Graph(vector<set<size_t>> adjList) {
		//, vector<size_t> postorderVec
		//makes the postorder numbers reversed, so we can go from 
		//the start to the end instead of backwards.
		for (size_t i = 0; i < adjList.size(); i++)
		{
			Node newNode(adjList.at(i));
			pair<size_t, Node> adj = { i, newNode };
			this->adjList.insert(adj);
		}
	}
	Graph() {}
	~Graph() {}
	//gets the postorder numbers of a depthfirst search
	vector<size_t> getPostOrderNums() const {
		return this->postOrderNums;
	}
	//Gets the strongly connected components in an order
	vector<set<size_t>> getSCCs() const {
		return this->sccVec;
	}
	//Gives the graph a set of postordernumbers.
	void givePostOrderVec(vector<size_t> postOrderNums) {
		//puts them in reverse order for iteration sake
		this->postOrderNums = postOrderNums;
		return;
	}

	//pair<bool, vector<size_t>> insert() 

	string toString() const {
		
		return "not implemented";
	}
	//calculates postorder numbers by doing a depthfirst search traversal
	void doPostNumsDFS() {
		postOrderNums = {}; //Empty the postordernums first dawg!
		visitedList = {};
		//For each rule in revAdjList
		for (pair<size_t, Node> p : adjList)
		{
			depthFirstSearchPON(p.first);
		}
		return;
	}
	//recursive depthfirst search that repopulates postordernumbers from depthfirst search.
	void depthFirstSearchPON(size_t& index)
	{
		//If not visited:
		if (visitedList.find(index) == visitedList.end())
		{
			//Indicate as visited(push to visited set)
			visitedList.insert(index);
			//For each depRule in rule
			for (size_t child : adjList.at(index).getChildren())
			{
				//Depth First search(this!) on that rule in the revAdjList.
				depthFirstSearchPON(child);
			}
			//pop off the stack: add to postordernums vector
			postOrderNums.push_back(index);
		}
		return;
	}

	void findSCCsDFS() {
		visitedList = {};
		set<size_t> allVertices;
		set<size_t> emptySet;
		std::reverse(this->postOrderNums.begin(), this->postOrderNums.end()); 
			//for testing the reversal;
			//cout << postOrderNumsToString();
			//make a set with all vertices in it
			for (size_t i = 0; i < adjList.size(); i++)
			{
				allVertices.insert(i);
			}
		//While not all have been visited
		while (allVertices != visitedList)
		{
			//add the new sccSet
			sccVec.push_back(emptySet);
			size_t index = postOrderNums.at(visitedList.size());
			//start at the next index of the postOrderNums (which are reversed), to do a depthfirst search.
			depthFirstSearchSCCForest(index);
		}
		return;
	}


	void depthFirstSearchSCCForest(size_t& index) {
		//If not visited:
		//unsigned ruleNum = postOrderNums.at(index);
		if (visitedList.find(index) == visitedList.end())
		{
			//Indicate as visited(push to visited set)
			visitedList.insert(index);
			//add to current scc set
			sccVec.at(sccVec.size() - 1).insert(index);
			//For each depRule in rule
			for (size_t child : adjList.at(index).getChildren())
			{
				//Depth First search(this!) on that rule in the revAdjList.
				depthFirstSearchSCCForest(child);
			}

		}

		return;
	}

	//Finds if an integer is in the postorder numbers or not. (Don't know why you made, but hey.)
	size_t findIntInPON(size_t& toFind) const
	{
		for (size_t i = 0; i < postOrderNums.size(); ++i)
		{
			if (postOrderNums.at(i) == toFind)
			{
				return i;
			}
		}
		return 9999999;
	}
	//Tostring for postorder numbers
	string postOrderNumsToString() {
		ostringstream os;
		os << "{";
		for (size_t i = 0; i < postOrderNums.size(); i++)
		{
			if (i > 0) { os << ","; }
			os << postOrderNums.at(i);
		}
		os << "}";
		return os.str();
	}
	string sccToStringFull() {
		ostringstream os;
		for (size_t i = 0; i < sccVec.size(); i++)
		{
			os << "SCC: ";
			size_t l = 0;
			for (size_t in : sccVec.at(i))
			{
				if (l > 0) { os << ","; }
				os << in;
				l++;
			}
			os << endl;
		}
		return os.str();
	}
};



#endif //!GRAPH_H

