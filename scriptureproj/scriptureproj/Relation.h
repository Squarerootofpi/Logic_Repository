#ifndef RELATION_H
#define RELATION_H
#include<set>
#include<algorithm>
#include"DatalogProgram.h"
#include"Proposition.h"

class Relation //These come from a scheme in our datalog
{
private:
	string name;
	std::set<Proposition> tuples;
	Tuple scheme;
public:
	Relation(string theName, Tuple theScheme) :
		name(theName), scheme(theScheme) {

	}
	~Relation() {

	}
	bool addTuple(Tuple theTuple) {
		return tuples.insert(theTuple).second;
	}
	int size()
	{
		return tuples.size();
	}
	std::set<Tuple> getTuples() const
	{
		return this->tuples;
	}
	string getName() const
	{
		return name;
	}
	Tuple getScheme() const {
		return scheme;
	}
	Tuple& getSchemeREL() {
		return scheme;
	}
	void changeScheme(const Tuple& newScheme)
	{
		scheme = newScheme;
	}
	//Relation toString....
	string toString() {
		/*
  S='0000', N='Woodstock', A='Treehouse', P='555-0000'
  S='1111', N='Linus', A='Piano St', P='555-1111'
  S='1212', N='Lucy', A='Home Ln', P='555-1212'
		*/
		if (tuples.size() == 0) {
			return "empty";
		}
		else {
			ostringstream os;
			for (auto tuple : tuples) //for each tuple in the set of tuples
			{

				if (!(this->scheme.size() == 0))
				{
					os << "  ";
				}
				for (unsigned int i = 0; i < tuple.size(); ++i)
					//you could also do scheme.size(), since they are the same, 
					//and tuple is representative of one tuple in it.
				{
					os << scheme.at(i) << "=" << tuple.at(i);
					if (i < scheme.size() - 1)
					{
						os << ", ";
					}
					else
					{
						os << endl;
					}
				}
			}
			return os.str();
		}
	}

	//Projects columns of a relation
	Relation project(vector<unsigned int> cols) { //cols will be the indexes of the columns to project.

		//every function should do this...
		//cout << "passed in = " << endl;
		//cout << this->toString();


		vector<string> empTuple;
		std::set<Tuple> setTuples;
		//Get initial tuples, in a SET. 
		setTuples = this->getTuples();

		Tuple newScheme(empTuple); //Empty tuple!! :)

		// copy the schemes from it that are needed.
		for (unsigned int i = 0; i < cols.size(); ++i)
		{
			unsigned int tupIndex = cols.at(i);
			newScheme.push_back(scheme.at(tupIndex)); //pushback this scheme at this index
		}

		Relation returnRel(name, newScheme); //Empty relation, with newScheme

		// copy the tuples from it that are needed
		for (auto tuple : setTuples) //for each tuple in the set of tuples
		{
			//create new tuple
			Tuple pushTuple(empTuple); //Empty tuple!! :)
			for (unsigned int i = 0; i < cols.size(); ++i)
			{
				//first tuple index to include
				unsigned int tupIndex = cols.at(i);
				pushTuple.push_back(tuple.at(tupIndex)); //pushback 
				//if (cols(tupleSize - 1 - i)) //if the index is to be deleted
			}
			returnRel.addTuple(pushTuple);
		}

		//cout << "Changed: " << endl;
		//cout << returnRel.toString();

		return returnRel;
	}
	//Selects the rows in a columnname that have the same key as compare
	Relation selectConst(string schemeCol, string compare)
	{
		Relation returnRel(name, scheme);
		unsigned int index = scheme.find(schemeCol);
		std::set<Tuple> theTuples = this->getTuples();
		for (auto tuple : theTuples) //for each tuple in the set of tuples
		{
			if (tuple.at(index) == compare)
			{
				returnRel.addTuple(tuple);
			}
		}
		return returnRel;
	}

	//Same as other select Const, just with an index instead
	Relation selectConst(unsigned int schemeIndex, string compare)
	{
		Relation returnRel(name, scheme);
		//unsigned int index = scheme.find(schemeCol);
		std::set<Tuple> theTuples = this->getTuples();
		for (auto tuple : theTuples) //for each tuple in the set of tuples
		{
			if (tuple.at(schemeIndex) == compare)
			{
				returnRel.addTuple(tuple);
			}
		}
		return returnRel;
	}
	//he implemented a slect cols that just took in 2 indexes, and then within the query it
	//checked the indexes again etc.
	Relation selectCols(string col1, string col2) {

		//Copying this scheme relation
		unsigned int i1 = scheme.find(col1);
		unsigned int i2 = scheme.find(col2);
		//cout << "i1 and i2: " << i1 << " " << i2 << endl;
		Relation returnRel(name, scheme);
		std::set<Tuple> theTuples = this->getTuples();
		for (auto tuple : theTuples) //for each tuple in the set of tuples
		{
			if (tuple.at(i1) == tuple.at(i2)) //compare the 2 values
			{
				returnRel.addTuple(tuple);
			}
		}

		return returnRel;
	}

	//SelectCols, but with unsigned ints instead of strings
	Relation selectCols(unsigned int col1, unsigned int col2) {

		//Copying this scheme relation
		//unsigned int i1 = scheme.find(col1);
		//unsigned int i2 = scheme.find(col2);
		//cout << "i1 and i2: " << i1 << " " << i2 << endl;
		Relation returnRel(name, scheme);
		std::set<Tuple> theTuples = this->getTuples();
		for (auto tuple : theTuples) //for each tuple in the set of tuples
		{
			if (tuple.at(col1) == tuple.at(col2)) //compare the 2 values
			{
				returnRel.addTuple(tuple);
			}
		}

		return returnRel;
	}

	Relation rename(string newName, string old) {

		//every function should do this...
		Relation r = self();
		Tuple oldScheme = r.getScheme();
		for (unsigned int i = 0; i < oldScheme.size(); ++i)
		{
			if (oldScheme.at(i) == old)
			{
				oldScheme.at(i) = newName;
				break; //Found it, and it is now renamed
			}
		}


		r.changeScheme(oldScheme);


		return r;
	}
	//Aggressive Rename, without checking
	Relation renameCol(string newName, unsigned int index) {

		//every function should do this...
		Relation r = self();
		Tuple oldScheme = r.getScheme();
		oldScheme.at(index) = newName;

		r.changeScheme(oldScheme);

		return r;
	}
	/*
	if it already existed ? if (mySet.insert(myTuple).second)
		If it already existed, do nothing
		If it is a new tuple, print out and add to DB relation
	*/
	//Union of two relations (with same name assumed!!!)
	Relation& unoin(Relation& unWith) {
		for (auto tuple : unWith.getTuples())//unsigned int i = 0; i < joinWith.size(); i++)
		{
			if (tuples.insert(tuple).second) //(mySet.insert(myTuple).second
			{
				//cout << tuple.toString() << endl;
			}
		}
		return *this;
	}
	/*
	This joins another relation on the right, and returns another relation.
   Combine the two Schemes
   Go through every pair of tuples
	   See if you can combine the tuples
	   Does every column that is supposed to match actually match?
	   If the tuples can be combined, then combine them
   */
	Relation join(const Relation& joinWith) {
		//	Combine the two Schemes
		Tuple joinWScheme = joinWith.getScheme(); //Permanent copies in here to speed processing

		Tuple newSchema = this->scheme;
		//unsigned int jWsize = joinWScheme.size();
		unsigned int indexInNew = 9999999;
		unsigned int indexInJoined = 9999999;
		vector<std::pair<unsigned int, unsigned int>> joinOns;


		for (string& s : joinWith.getScheme()) //for each string in joinwscheme
		{

			//if ()
			indexInNew = newSchema.find(s);
			if (indexInNew == 9999999) // if we don't find s in the newSchema already, 
			{
				//if it's a constant, 
				newSchema.push_back(s);
			}
			else //It is found!!! Have to join on this col. at least.
			{ //newSchema.find(s) returns the index of that scheme etc...
				indexInJoined = joinWScheme.find(s);
				//cout << "joining schemes at index " << indexInNew << " and at index " << indexInJoined << endl;
				//Pushback the vector where they are joining indexes etc...
				std::pair<unsigned int, unsigned int> thisthat = { indexInNew, indexInJoined };
				joinOns.push_back(thisthat);
			}
		}
		//newSchema.join(joinWScheme, joinOns); //Joins the schemes according to what we calculated

		//make the new relation we'll populate! :)
		Relation r(name, newSchema);
		//Go through every pair of tuples
		for (const Tuple& leftT : this->getTuples()) //for each tuple in this relation
		{
			for (const Tuple& rightT : joinWith.getTuples())
			{
				//See if you can combine the tuples
				if (leftT.isJoinable(rightT, joinOns))
				{
					r.addTuple(leftT.join(rightT, joinOns));
					//Put this into the new relation r
				}
			}
		}

		//Does every column that is supposed to match actually match ?

		//If the tuples can be combined, then combine them

		return r;
	}
	//A deep copy of itself 
	Relation self()
	{
		Relation returnRel(name, scheme); //Copy of this scheme
		std::set<Tuple> theTuples = this->getTuples();
		for (auto tuple : theTuples) //for each tuple in the set of tuples
		{
			returnRel.addTuple(tuple);
		}
		return returnRel;
	}

};

#endif //RELATION_H
