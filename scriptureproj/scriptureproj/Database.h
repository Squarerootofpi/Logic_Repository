#ifndef DATABASE_H
#define DATABASE_H
#include<map>
#include"LogicTree.h"

//How do that??? String to relation?
//This maps the strings (or the names of the schemes) to the relations
//Strings are the names of each relation, or in other words, the name of the scheme
class Database : public std::map<size_t, LogicTree>
{
public:
	Database() {

	}
	~Database() {

	}
	string toString() {
		//return "";
		std::ostringstream os;
		map<size_t, LogicTree>::iterator it;
		int relationNum = 1;
		for (it = this->begin(); it != this->end(); it++)
		{
			os << " start " << it->first  // string (key)
				<< ':' << std::endl
				<< it->second.toString()   // Each relation's tostring
				<< "Relation " << relationNum << std::endl;
			++relationNum;
		}
		return os.str();
	}
private:
};

#endif //DATABASE_H