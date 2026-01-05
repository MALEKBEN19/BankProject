#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "MyLib.h";
#include<iomanip>
using namespace std;
const string ClientList = "ClientList.txt";

struct stClient{
	string AccountNumber;
	string Pin_Code;
	string Name;
	string Phone;
	double Account_Balance;
	bool MarkClient = false;
};

enum enMenuOptions{ShowClient=1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, ExitMenu = 6};

enMenuOptions GetChoice();









int main()
{
	GetChoice();
	
	



	system("pause>0");
	return 0;
}

enMenuOptions GetChoice() {
	short OptionsButton = 0;
	do {
		cout << "Choose What You want to do? [1-6] ";
		cin >> OptionsButton;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Please enter a correct digit! ";
			cin >> OptionsButton;
		}

	} while (OptionsButton < 1 || OptionsButton>6);
	return enMenuOptions(OptionsButton);
}






















void ProgramEnd() {
	cout << "\n-----------------------------------\n\n";
	cout << "\tProgram Ends :-)";
	cout << "\n\n-----------------------------------\n\n";
}