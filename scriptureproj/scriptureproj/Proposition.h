#ifndef PROPOSITION_H
#define PROPOSITION_H

#include<string>
#include<vector>
#include<set>
#include<sstream>

using std::set;
using std::vector;
using std::string;


class Proposition
{
private:
	size_t id; //ID
	string atomicDescription; // AD
	string extraDescription; // ED
	set<size_t> dependencies; //ID's of the propositions it's dependent on
public:
	Proposition();
	~Proposition();
	//Get atomic description
	string getAD();
	//Get Extra description
	string getED();
	set<size_t> getDeps(); //ID's of the propositions it's dependent on
	//tostring
	string toString();
	Proposition(size_t inId, string inAtomicDescription, string inExtraDescription,
		set<size_t> inDependencies);
};

//Constructor 
Proposition::Proposition(size_t inId, string inAtomicDescription, string inExtraDescription, 
	set<size_t> inDependencies) : id(inId), atomicDescription(inAtomicDescription),
	extraDescription(inExtraDescription), dependencies(inDependencies)
{
}

//Default Constructor
Proposition::Proposition()
{
}
string Proposition::toString() 
{
	std::ostringstream os;
	string s;
	os << "P: " << id << endl;
	os << "AD: " << atomicDescription << endl;
	os << "ED: " << extraDescription << endl;
	os << "Dependencies: ";
	unsigned int counter = 0;
	for (size_t i : dependencies)
	{
		if (counter > 0) { os << " "; }
		os << i;
		counter++;
	}
	os << endl;
	/*
	
P: 3
AD: God created us
ED: Specifically, God created all of humankind on the earth. All religions, races, peoples, etc.
Dependencies: 2
	*/
	return os.str(); 
}
string Proposition::getAD() { return atomicDescription; }
string Proposition::getED() { return extraDescription; }
set<size_t> Proposition::getDeps() { return dependencies; } //ID's of the propositions it's dependent on

Proposition::~Proposition()
{
}



#endif // !PROPOSITION_H
