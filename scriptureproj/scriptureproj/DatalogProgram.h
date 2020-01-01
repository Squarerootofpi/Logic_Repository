#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H


#include<set>
#include"Token.h"


using std::vector;


class DatalogProgram
{
private:
	unsigned int tokenIndex;
	vector<Token> tokens;
	//std::stack<std::string> thestack;
	std::set<string> domainFacts;


public:
	DatalogProgram(vector<Token> tokensfromScanner) {
		tokens = tokensfromScanner;
		tokenIndex = 0;
	} //Puts tokens immediately into Datalog, token vector starts at 0
	~DatalogProgram() {}

	/*bool parser() { //Returns true if successfully parsed
					//This class is the grammar if-else's of the class.
		return false;
	}*/
	bool parseDatalog()
	{
		match(SCHEMES);
		match(COLON);
		scheme();
		schemeList();
		match(FACTS);
		match(COLON);
		factList();
		match(RULES);
		match(COLON);
		ruleList();
		match(QUERIES);
		match(COLON);
		query();
		queryList();
		match(ENDF);

		//If any more tokens after the ENDF token... we have issues.
		if (tokenIndex > (tokens.size()))
		{
			thro(); //throws the token after the last match of EOF
		}
		/*
		Grammar for DATALOG
	SCHEMES COLON scheme schemeList
		FACTS COLON factList
		RULES COLON ruleList
		QUERIES COLON query queryList
		*/
		return true;
	}

	/** Throw a token in error  */
	void thro() {
		throw (tokens.at(tokenIndex));
		return; //Will never hit the return, but there for grammar
	}
	/** This is how I match tokens which are TERMINALS in the grammar */
	string match(TokenType matchWith)
	{
		if (tokens.at(tokenIndex).getType() == matchWith)
		{
			++tokenIndex;
			return tokens.at(tokenIndex - 1).getName(); //Gets the name of the token we just matched with.
		}
		thro();
		return "";
	}
	void schemeList() {
		if (tokens.at(tokenIndex).getType() == FACTS) //stop recursing on FOLLOW set
		{
			return; //Don't imcrement Token, just match in main
		}
		scheme();
		schemeList();
		return;
	}
	void scheme() {
		string sSPred = match(ID); //gives us an sPred Predicate with the  name of the scheme
		match(LEFT_PAREN);
		string firstID = match(ID);
		vector<string> myIDs;
		myIDs.push_back(firstID);
		myIDs = idList(myIDs);
		//Put the scheme on the vector, so idList can add as many more strings as are needed.
		Predicate sPred(myIDs, sSPred);
		vSchemes.push_back(sPred);
		match(RIGHT_PAREN);
		return;
	}

	void ruleList() { //This is pretty much reduntant, but we keep it for clarity. 
						//The recursion occurs in rule.
		if (tokens.at(tokenIndex).getType() == QUERIES) //stop recursing
		{
			return;
		}
		rule();
		ruleList();
		return;
	}
	void rule() {
		//Make 1st Predicate
		Predicate hPred = hPredicate();
		match(COLON_DASH);
		//Make other rule associated predicates
		vector<Predicate> preds;
		Predicate p1 = predicate(); //Manditory 1st Predicate
		preds.push_back(p1);
		preds = predicateList(preds); //Get all other associates
		match(PERIOD);
		Rule theRule(preds, hPred);
		vRules.push_back(theRule);
		return;
	}
	void factList() {
		if (tokens.at(tokenIndex).getType() == RULES) //stop recursing
		{
			return;
		}
		fact();
		factList();
		return;
	}
	void fact() {
		string name = match(ID);
		match(LEFT_PAREN);
		string firstStr = match(STRING);
		vector<string> vect;
		vect.push_back(firstStr);
		domainFacts.insert(firstStr); //Add to domain of facts
		vect = stringList(vect);
		Predicate fPred(vect, name);
		vFacts.push_back(fPred);
		match(RIGHT_PAREN);
		match(PERIOD);

		return;
	}
	void queryList() {
		if (tokens.at(tokenIndex).getType() == ENDF) //stop recursing
		{
			return;
		}
		query();
		queryList();
		return;
	}
	void query() {
		Predicate queryPred = predicate();
		match(Q_MARK);
		vQueries.push_back(queryPred);
		return;
	}
	Predicate hPredicate() {
		string name = match(ID);
		match(LEFT_PAREN);
		vector<string> predIDs;
		predIDs.push_back(match(ID));
		predIDs = idList(predIDs);
		match(RIGHT_PAREN);
		Predicate pred(predIDs, name);
		return pred;
	}
	Predicate predicate() {
		string name = match(ID);
		match(LEFT_PAREN);
		string p1 = parameter();
		vector<string> vparams;
		vparams.push_back(p1);
		vparams = parameterList(vparams);
		match(RIGHT_PAREN);
		Predicate thePred(vparams, name);
		return thePred; //These do the exact same thing. Return a predicate.
	}
	vector<Predicate> predicateList(vector<Predicate> thePredicates) {
		if (tokens.at(tokenIndex).getType() == PERIOD) //stop recursing
		{
			return thePredicates;
		}
		match(COMMA);
		thePredicates.push_back(predicate());

		return predicateList(thePredicates);
	}
	vector<string> parameterList(vector<string> params) {
		if (tokens.at(tokenIndex).getType() == RIGHT_PAREN) //stop recursing
		{
			return params;
		}
		match(COMMA);
		params.push_back(parameter());

		return parameterList(params);
	}
	string parameter() {
		if (tokens.at(tokenIndex).getType() == LEFT_PAREN) //follow set, do expression
		{
			return expression("");
		}
		else if (tokens.at(tokenIndex).getType() == STRING)
		{
			return match(STRING);
		}
		else if (tokens.at(tokenIndex).getType() == ID)
		{
			return match(ID);
		}
		else
		{
			thro(); //We have an error gentlemen.
			return tokens.at(tokenIndex).getName();
		}
	}
	vector<string> stringList(vector<string> theVector) {
		if (tokens.at(tokenIndex).getType() == RIGHT_PAREN) //stop recursing
		{
			return theVector;
		}
		match(COMMA);
		string toAdd = match(STRING);
		theVector.push_back(toAdd);
		domainFacts.insert(toAdd);
		return stringList(theVector);
	}
	vector<string> idList(vector<string> theVector) {
		if (tokens.at(tokenIndex).getType() == RIGHT_PAREN) //stop recursing
		{
			return theVector;
		}
		/*
		sPred.addStr(match(ID));
		vSchemes.push_back(sPred);
		*/
		match(COMMA);
		theVector.push_back(match(ID));
		//vSchemes.at(vSchemes.size() -1).addStr(match(ID)); //Adds an ID string to the last vector in schemes (the current one we are inside of)
		//cout << vSchemes.at(vSchemes.size() - 1).paramSize() << endl;


		return idList(theVector);
	}

	string expression(string totalExpr) {
		totalExpr += match(LEFT_PAREN);
		totalExpr += parameter();
		totalExpr += operator_();
		totalExpr += parameter();
		totalExpr += match(RIGHT_PAREN);
		return totalExpr;
	}
	string operator_() {
		if (tokens.at(tokenIndex).getType() == MULTIPLY)
		{
			return match(MULTIPLY);
		}
		else if (tokens.at(tokenIndex).getType() == ADD)
		{
			return match(ADD);
		}
		else {
			thro(); //We have an error gentleman....
			return "";
		}
	}


	string toString()
	{
		ostringstream os;
		os << "Success!" << endl;
		os << "Schemes(" << vSchemes.size() << "):" << endl;
		for (unsigned int i = 0; i < vSchemes.size(); ++i)
		{
			os << "  " << vSchemes.at(i).toString() << endl;
		}
		//os << "It should happen here.." << endl;
		os << "Facts(";
		os << vFacts.size();
		os << "):" << endl;
		//os << "Try again" << endl;
		for (unsigned int i = 0; i < vFacts.size(); ++i)
		{
			os << "  " << vFacts.at(i).toString() << "." << endl;
		}
		os << "Rules(";
		os << vRules.size();
		os << "):" << endl;
		for (unsigned int i = 0; i < vRules.size(); ++i)
		{
			os << "  " << vRules.at(i).toString() << "." << endl;
		}
		os << "Queries(";
		os << vQueries.size();
		os << "):" << endl;
		for (unsigned int i = 0; i < vQueries.size(); ++i)
		{
			os << "  " << vQueries.at(i).toString() << "?" << endl;
		}
		std::set<std::string>::iterator it = domainFacts.begin();
		os << "Domain(";
		os << domainFacts.size();
		os << "):" << endl;
		// Iterate till the end of set
		if (domainFacts.size() > 0)
		{
			os << "  " << (*it);
			it++;
		}

		while (it != domainFacts.end())
		{
			os << endl;
			// Print the element
			os << "  " << (*it);
			//Increment the iterator
			it++;
		}
		return os.str();
	}

	/*
	vector<Predicate> vSchemes;
	vector<Rule> vRules;
	vector<Predicate> vFacts;
	vector<Predicate> vQueries;
	std::set<string> domainFacts;
	*/

	vector<Predicate> getSchemes() {
		return vSchemes;
	}
	vector<Rule> getRules() {
		return vRules;
	}
	vector<Predicate> getFacts() {
		return vFacts;
	}
	vector<Predicate> getQueries() {
		return vQueries;
	}
	std::set<string> getDomainFacts() {
		return domainFacts;
	}
};

#endif // !DATALOGPROGRAM_H

