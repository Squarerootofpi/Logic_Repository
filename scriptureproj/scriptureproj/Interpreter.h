#ifndef INTERPRETER_H
#define INTERPRETER_H

#include"Scanner.h"

class Interpreter
{
private:
	DatalogProgram datalog;
	Database db;
	vector<vector<Proposition>>  ;

public:
	Interpreter();
	~Interpreter();


};

Interpreter::Interpreter()
{
}

Interpreter::~Interpreter()
{
}



#endif //INTERPRETER_H