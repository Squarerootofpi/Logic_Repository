#ifndef SCANNER_H
#define SCANNER_H

#include"Proposition.h"
#include<set>

using std::getline;

class Scanner
{
private:
	vector<Proposition> thePropositions;
	std::set<size_t> axioms;
	vector<string> sources;
	std::set<size_t> IDs;
	vector<std::set<size_t>> adjList;
public:
	Scanner() {}

	~Scanner() {}
	vector<Proposition> getProps()
	{
		return thePropositions;
	}
	std::set<size_t> getAxioms() {
		return axioms;
	}
	vector<string> getSources() {
		return sources;
	}
	std::set<size_t> getIDs() {
		return IDs;
	}
	vector<std::set<size_t>> getAdjList() {
		return adjList;
	}
	void dropData() {
		thePropositions = {};
		axioms = {};
		sources = {};
		IDs = {};
		adjList = {};
		return;
	}

	//The main file for scanner, bulk is in this.
	void scan(char* argv[])
	{
		dropData();
		ifstream inputFile;
		inputFile.open(argv[1]);
		if (!inputFile)
		{
			cout << "input opening error" << endl;
			throw("input opening error");
		}
		if (inputFile)
		{
			//I am happy silently. :)
		}

		start(inputFile);
		//tostring called within main
		//Now it is scanned and parsed.
		//cout << "scanning done!" << endl;
		inputFile.close();

	}
	//START STATE
	int start(ifstream& in) //reference the input file

	{
		//make all objects in here!!
		//Make propositions
		if (propositions(in))
		{
			cout << "Successfully added propositions." << endl;
		}
		else
		{
			cout << "No propositions in proper formatting, stopping scan." << endl;
			return 1;
		}
		if (doAxioms(in))
		{
			cout << "Axioms added." << endl;
		}
		else { cout << "No axioms added, errors will arise." << endl; }
		if (doSources(in))
		{
			cout << "Sources added. " << endl;
		}
		else { cout << "None added." << endl; }


		return 0;
	}
	
	//returns true if any propositions were added
	bool propositions(ifstream& in) {
		string command;
		getline(in, command);
		//cout << command;
		if (command != "Propositions") {
			return false;
		}
		while (sProposition(in))
		{
			cout << "One added" << endl;
		}


		return true;
	}
	bool doSources(ifstream& in) {
		
		return true;
	}
	bool doAxioms(ifstream& in) {
		bool hasAxioms = false;
		string command;
		getline(in, command);
		//cout << command;
		int counter = 0;
		while (command != "Axioms") {
			getline(in, command);
			counter++;
			if (counter == 6) { return false; }
		}
		getline(in, command);

		std::stringstream ss;
		ss << command;
		string temp;
		while (std::getline(ss, temp, ' ')) {
			size_t tInt = std::stoi(temp);
			axioms.insert(tInt);
			hasAxioms = true;
		}
		return hasAxioms;
	}

	bool sProposition(ifstream& in) {
		bool added = false;
		//string p;
		string id;
		string ad;
		string ed;
		string dep;
		std::getline(in, id);
		//cout << id << " is the inputted string" << endl;
		while (!charStart(id)) //check to see if starts with char
		{
			std::getline(in, id);
		}
		//starts with P: and has an atomic proposition after it.
		//appropriate match, or the follow set. If not, get another line.
		if (matchFront(id, "P: ", 3) && id.size() > 3)
		{
			id = id.substr(3, id.size());
		}
		else { return false; }
		std::getline(in, ad);
		if (matchFront(ad, "AD: ", 4) && ad.size() > 4)
		{
			ad = ad.substr(4, ad.size());
		}
		else { return false; }
		std::getline(in, ed);
		if (matchFront(ed, "ED: ", 4))
		{

			ed = ed.substr(4, ed.size());
		}
		std::getline(in, dep);
		if (matchFront(dep, "Dependencies: ", 14))
		{
			if (dep.size() > 14)
			{
				dep = dep.substr(14, dep.size());
			}
		}
		return addProp(id, ad, ed, dep);
	}
	bool charStart(string& s)
	{
		//if the size is 0, starts with a space, or a return.
		if (s.size() == 0 || s.at(0) == ' ' || s.at(0) == '\n')
		{
			return false;
		}
	}
	bool matchFront(string& str, string match, unsigned int num)
	{
		if (str.substr(0,num) == match)
		{
			return true;
		}
		return false;
	}
	//Add proposition, using just correct parsed string inputs
	bool addProp(string ID, string AD, string ED, string deps)
	{
		bool hasDependent = false;
		std::stringstream ss;// deps);
		ss << deps;
		set<size_t> depInts;
		string temp;
		while (std::getline(ss, temp, ' ')) {
			size_t tInt = std::stoi(temp);
			depInts.insert(tInt);
			hasDependent = true;
		}
		if (hasDependent)
		{
			size_t tID = std::stoi(ID);
			if (IDs.insert(tID).second)
			{
				Proposition prop(tID, AD, ED, depInts);
				thePropositions.push_back(prop);
				adjList.push_back(depInts);
			}
		}
		return hasDependent; //if no dependents, it won't add it, and will return false.
	}
	string toString()
	{
		ostringstream os;
		os << "Propositions" << endl << endl;
		for (size_t i = 0; i < thePropositions.size(); i++)
		{
			os << thePropositions.at(i).toString();
			os << endl;
		}
		//os << endl;
		os << "Axioms" << endl;
		unsigned int counter = 0;
		for (size_t i : axioms)
		{
			if (counter > 0)
			{
				os << ' ';
			}
			os << i;
			
			counter++;
		}
		return os.str();
	}
};


#endif // !SCANNER_H
