#include<iostream>
#include<fstream>
#include"Graph.h"
#include"Token.h"
#include"Scanner.h"
#include"Proposition.h"
#include"Graph.h"


using std::cout;

int main(int argc, char* argv[]) //Scanner opens argv[1] as input file
{
	//Test if input works
	/*std::ifstream inputFile;
	inputFile.open(argv[1]);
	if (!inputFile)
	{
		cout << "input opening error" << endl;
		return 1;
	}
	if (inputFile)
	{
		//I am happy silently. :)
	}*/

	std::ofstream outputFile;
	outputFile.open(argv[2]);
	if (!outputFile)
	{
		cout << "output opening error" << endl;
		return 1;
	}
	if (outputFile)
	{
		//I am happy silently. :)
	}

	try
	{
		//menu
		cout << "We have success testing." << endl;
		cout << "MENU: " << endl;

		Scanner scanner;
		scanner.scan(argv); //One input file, one output file, for now
		cout << "Finished scanning." << endl;
		//DatalogProgram datalog(scanner.giveVector()); //Give vector
		cout << scanner.toString();

	}
	catch (...)
	{
		cout << "EXCEPTION!! Some error caused it to abort." << endl;
	}




	//inputFile.close();
	outputFile.close();

	system("pause");

	return 0;
}