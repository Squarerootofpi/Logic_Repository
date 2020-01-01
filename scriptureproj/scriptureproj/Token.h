#ifndef TOKEN_H
#define TOKEN_H
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<ostream>
#include<string>
#include<sstream>
#include<vector>

using std::ifstream;
using std::endl;
using std::cout;


enum TokenType
{
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
	MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT,
	UNDEFINED, ENDF,

	PROPOSITIONS, PROPID, 

};
/*
This implimentation works in g++ compiler, but not within VS, So I am choosing to not use it, although I like it better.
static const char * EnumStrings[] = { "COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH", "MULTIPLY",
	"ADD", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "COMMENT",
	"UNDEFINED", "EOF" };

const char * getTextForEnum(int enumVal)
{
	return EnumStrings[enumVal];
}
*/

/*std::string const getTextForEnum(TokenType ttype)
{
	switch (ttype)
	{
	case COMMA:
		return "COMMA";
		break;
	case PERIOD:
		return "PERIOD";
		break;
	case Q_MARK:
		return "Q_MARK";
		break;
	case LEFT_PAREN:
		return "LEFT_PAREN";
		break;
	case RIGHT_PAREN:
		return "RIGHT_PAREN";
		break;
	case COLON:
		return "COLON";
		break;
	case COLON_DASH:
		return "COLON_DASH";
		break;
	case MULTIPLY:
		return "MULTIPLY";
		break;
	case ADD:
		return "ADD";
		break;
	case SCHEMES:
		return "SCHEMES";
		break;
	case FACTS:
		return "FACTS";
		break;
	case RULES:
		return "RULES";
		break;
	case QUERIES:
		return "QUERIES";
		break;
	case ID:
		return "ID";
		break;
	case STRING:
		return "STRING";
		break;
	case COMMENT:
		return "COMMENT";
		break;
	case ENDF:
		return "EOF";
		break;
	case UNDEFINED:
		return "UNDEFINED";
		break;
	default: //undefined
		return "not recognized?";
		break;
	}
	return "don't know how you got here.";
}*/

using std::string;
using std::ostringstream;
using std::ostream;


class Token
{
private:
	string name;
	int line;
	TokenType type;

public:
	//constructor
	Token(string theName = "", int theLine = -1, TokenType theType = UNDEFINED) : name(theName), line(theLine), type(theType) {}
	Token(char theName, int theLine, TokenType theType) : line(theLine), type(theType)
	{
		string c(1, theName);
		name = c;
	}
	//Token() : name("defaultname"), line(-1), type(UNDEFINED) {}
	~Token() {}
	/** for editing default constructors*/
	void edit(string newName, int newLine, TokenType tType)
	{
		name = newName;
		line = newLine;
		type = tType;
	}
	TokenType getType() {
		return type;
	}
	string getName()
	{
		return name;
	}
	string toString() const {
		//(FACTS,"Facts",1)
		ostringstream os;
		string stype = "";

		switch (type) //This looks ugly, but I tried like 10 other ways and kept on having problems in VS. 
		{			//I decided to not divorce my IDE just yet. :)
		case COMMA:
			stype = "COMMA";
			break;
		case PERIOD:
			stype = "PERIOD";
			break;
		case Q_MARK:
			stype = "Q_MARK";
			break;
		case LEFT_PAREN:
			stype = "LEFT_PAREN";
			break;
		case RIGHT_PAREN:
			stype = "RIGHT_PAREN";
			break;
		case COLON:
			stype = "COLON";
			break;
		case COLON_DASH:
			stype = "COLON_DASH";
			break;
		case MULTIPLY:
			stype = "MULTIPLY";
			break;
		case ADD:
			stype = "ADD";
			break;
		case SCHEMES:
			stype = "SCHEMES";
			break;
		case FACTS:
			stype = "FACTS";
			break;
		case RULES:
			stype = "RULES";
			break;
		case QUERIES:
			stype = "QUERIES";
			break;
		case ID:
			stype = "ID";
			break;
		case STRING:
			stype = "STRING";
			break;
		case COMMENT:
			stype = "COMMENT";
			break;
		case ENDF:
			stype = "EOF";
			break;
		case UNDEFINED:
			stype = "UNDEFINED";
			break;
		default: //undefined, hopefully never gets here..
			stype = "not recognized?";
			break;
		}
		os << "(" << stype << ",\"" << name << "\"," << line << ")";
		return os.str();
	}

	friend ostream& operator<< (ostream& os, const Token& myToken)
	{
		os << myToken.toString();
		return os;
	}


	//Different implimentation of getting verbal tokens
	/*std::vector<string> EnumStrings{ "COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH", "MULTIPLY",
	"ADD", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "COMMENT",
	, "EOF" };

	*/

};




#endif // !TOKEN_H