#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

const string ClientFile = "ClientFile.txt";


//Tools I used :
//-------------------------------------------------
struct stClient {
	string AccountNumber;
	string Pin_Code;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool MarkClient=false;
};
string ConvertRecordTo_Line(stClient clt, string sperator = "#//#") {
	string AssignRecordToLine = "";
	AssignRecordToLine += clt.AccountNumber + sperator;
	AssignRecordToLine += clt.Pin_Code + sperator;
	AssignRecordToLine += clt.Name + sperator;
	AssignRecordToLine += clt.Phone + sperator;
	AssignRecordToLine += to_string(clt.AccountBalance);
	return AssignRecordToLine;
}

vector<string>SplitString(string txt,string Delim) {
	vector<string>vWords;
	string word;
	short Pos = 0;
	while ((Pos = txt.find(Delim)) != std::string::npos) {
		word = txt.substr(0, Pos);
		if (word != "") {
			vWords.push_back(word);
		}
		txt.erase(0, Pos + Delim.length());
	}
	if (txt != "") {
		vWords.push_back(txt);
	}
	return vWords;
}

stClient Convert_LineToRecord(string Line,string sperator="#//#") {
	vector<string>vWord;
	stClient client;
	vWord = SplitString(Line,sperator);
	client.AccountNumber = vWord.at(0);
	client.Pin_Code = vWord.at(1);
	client.Name = vWord.at(2);
	client.Phone = vWord.at(3);
	client.AccountBalance = stod(vWord.at(4));
	return client;
}

enum enMenuOptions{Show=1, Add = 2, Delete = 3,Update=4, find = 5, Exit = 6,};

enMenuOptions GetChoice() {

	short Input = 0;
	do {
		cout << "Choose What do you want to do? [ 1 - 6 ] ";
		cin >> Input;
	} while (Input < 1 || Input>6);

	return enMenuOptions(Input);
}

vector<stClient> LoadDataFromFile(string file) {
	vector<stClient> vClients;
	stClient client;
	fstream Myfile;
	Myfile.open(file, ios::in);
	if (Myfile.is_open()) {
		string Line;
		while (getline(Myfile, Line)) {
			client = Convert_LineToRecord(Line);
			vClients.push_back(client);
		}
		Myfile.close();
	}
	return vClients;
}

//-------------------------------------------------


//show client menu : 
//----------------------------------------------

void PrintClients(stClient client) {
	cout << "| " << left << setw(15) << client.AccountNumber;
	cout << "| " << left << setw(13) << client.Pin_Code;
	cout << "| " << left << setw(30) << client.Name;
	cout << "| " << left << setw(16) << client.Phone;
	cout << "| " << left << setw(14) << to_string(client.AccountBalance);
}
void PrintClientMenu(vector<stClient> vclient) {
	system("cls");
	cout << "\n\t\t\t\t Client List (" << vclient.size() << ") Client(s).\n";
	cout << "\n____________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(13) << "Pin Code";
	cout << "| " << left << setw(30) << "Name";
	cout << "| " << left << setw(16) << "Phone";
	cout << "| " << left << setw(14) << "Account Balance";
	cout << "\n____________________________________________________________________________________________________\n\n";
	for (stClient& clt : vclient) {
		PrintClients(clt);
		cout << endl;
	}
	cout << "\n____________________________________________________________________________________________________\n\n";
}

//----------------------------------------------


//Add client : 
//----------------------------------------------
bool IsAccountNumberExist(vector<stClient> vClient, string AccountNumber) {
	for (stClient& clt : vClient) {
		if (clt.AccountNumber == AccountNumber) {
			return 1;
		}
	}
	return 0;
}
stClient GetClientInfo() {
	stClient client;
	vector<stClient>vclient = LoadDataFromFile(ClientFile);
	cout << "Enter Account Number : ";
	getline(cin >> ws, client.AccountNumber);
	while (IsAccountNumberExist(vclient,client.AccountNumber)) {
		cout << "\nClient With N: [" << client.AccountNumber << "] Already Exist, Enter Another Account Number? ";
		getline(cin >> ws, client.AccountNumber);
	}
	cout << "\nEnter Pin Code : ";
	getline(cin >> ws, client.Pin_Code);

	cout << "\nEnter Name : ";
	getline(cin >> ws, client.Name);

	cout << "\nEnter Phone : ";
	getline(cin >> ws, client.Phone);

	cout << "\nEnter Account Balance : ";
	cin >> client.AccountBalance;

	return client;

}
void AddDataLineToFile(string Line, string file) {
	fstream Myfile;
	Myfile.open(file, ios::out | ios::app);
	if (Myfile.is_open()) {
		Myfile << Line << endl;
		Myfile.close();
	}
}
void AddClient() {
	stClient client;
	client = GetClientInfo();
	AddDataLineToFile(ConvertRecordTo_Line(client), ClientFile);
}
void AddNewClientScreen() {
	cout << "\n----------------------------------------------------\n";
	cout << "\n\t\t Add New Client Screen \n";
	cout << "\n----------------------------------------------------\n\n";
}
void AddClients() {
	char AddMore = 'y';
	do {
		system("cls");
		AddNewClientScreen();
		cout << "Adding New Client\n\n";
		AddClient();
		cout << "\nClient Added successfully, do you want to add more client? (Y/N) ";
		cin >> AddMore;
	} while (tolower(AddMore) == 'y');
}

//----------------------------------------------


//Delete client : 
//----------------------------------------------
void DeleteClientScreen() {
	cout << "\n----------------------------------------------------\n";
	cout << "\n\t\t Delete Client Screen \n";
	cout << "\n----------------------------------------------------\n\n";
}
string ReadAccountNumber() {
	string Account;
	cout << "\nPlease Enter Account Number : ";
	getline(cin >> ws, Account);
	return Account;
}
bool IsAccountNumberExist(vector<stClient>& vClient, stClient &client,string AccountNumber) {
	for (stClient& clt : vClient) {
		if (clt.AccountNumber == AccountNumber) {
			client = clt;
			return 1;
		}
	}
	return 0;
}
bool MarkClientForDelete(vector<stClient>&vClient,string AccountNumber) {
	for (stClient& clt : vClient) {
		if (clt.AccountNumber == AccountNumber) {
			clt.MarkClient = true;
			return 1;
		}
	}
	return 0;
}
void ShowClientCard(stClient clnt) {
	cout << "\nThe Following Are The Client Details :\n";
	cout << "---------------------------------------------\n";
	cout << "Account Number : " << clnt.AccountNumber << endl;

	cout << "Pin Code : " << clnt.Pin_Code << endl;

	cout << "Name : " << clnt.Name << endl;

	cout << "Phone : " << clnt.Phone << endl;

	cout << "Account Balance : " << to_string(clnt.AccountBalance) << endl;

	cout << "---------------------------------------------\n";
}
void SaveClientDataToFile(string file, vector<stClient>& vClient) {
	fstream Myfiles;
	Myfiles.open(file, ios::out);
	if (Myfiles.is_open()) {
		string Line;
		for (stClient& clt : vClient) {
			if (clt.MarkClient == false) {
				Line = ConvertRecordTo_Line(clt);
				Myfiles << Line << endl;
			}
		}
		Myfiles.close();
	}
}
void DeleteAccountFromFile(vector<stClient> & vClient) {

	stClient client;
	char Delete = 'n';
	system("cls");
	DeleteClientScreen();
	string Account =ReadAccountNumber();
	if (IsAccountNumberExist(vClient, client, Account)) {
		ShowClientCard(client);
		cout << "\n\nAre You Sure You Want To Delete This Account? (Y/N) ";
		cin >> Delete;
		if (toupper(Delete) == 'Y') {
			MarkClientForDelete(vClient, Account);
			SaveClientDataToFile(ClientFile,vClient);
			cout << "\nclient Deleted successfully.";

		}
		vClient=LoadDataFromFile(ClientFile);
	}
	else { 
		cout << "Client with Account Number [" << Account  << "] is Not Found! ";
	}
}
//---------------------------------------------


//Updat client : 
//----------------------------------------------

void UpdateClientScreen() {
	cout << "\n----------------------------------------------------\n";
	cout << "\n\t\t Update Client Screen \n";
	cout << "\n----------------------------------------------------\n\n";
}
void UpdateTheClientOnVector(stClient &clt) {
	cout << "Enter Pin Code : ";
	getline(cin >> ws, clt.Pin_Code);

	cout << "Enter Name : ";
	getline(cin >> ws, clt.Name);

	cout << "Enter Phone : ";
	getline(cin >> ws, clt.Phone);

	cout << "Enter Account Balance : ";
	cin >> clt.AccountBalance;
}
bool UpdateInfo(vector<stClient>& vClient,string AccountNumber) {
	for (stClient& clt : vClient) {
		if (clt.AccountNumber == AccountNumber) {
			UpdateTheClientOnVector(clt);
			return 1;
		}
	}
	return 0;
	
}
void UpdateClient(vector<stClient>& vClient) {

	stClient client;
	char Delete = 'n';
	UpdateClientScreen();
	string Account = ReadAccountNumber();
	if (IsAccountNumberExist(vClient, client, Account)) {
		ShowClientCard(client);
		cout << "\n\nAre You Sure You Want To Update This Account? (Y/N) ";
		cin >> Delete;
		if (toupper(Delete) == 'Y') {
			UpdateInfo(vClient,Account);
			SaveClientDataToFile(ClientFile, vClient);
			cout << "\nclient Updated successfully.";

		}
		vClient = LoadDataFromFile(ClientFile);
	}
	else {
		cout << "Client with Account Number '" << Account << "' is Not Found! \n";
	}
}
//---------------------------------------------



//Find client : 
//----------------------------------------------
void FindClientScreen() {
	cout << "\n----------------------------------------------------\n";
	cout << "\n\t\t Find Client Screen \n";
	cout << "\n----------------------------------------------------\n\n";
}
void FindClientByAccountNumber(vector<stClient> vClient) {
	stClient clients;
	system("cls");
	FindClientScreen();
	string AccountNum = ReadAccountNumber();
	if (IsAccountNumberExist(vClient, clients, AccountNum)) {
		ShowClientCard(clients);
	}
	else {
		cout << "Client with Account Number '" << AccountNum << "' is Not Found! \n";
	}

}

//----------------------------------------------


//Exit Screen : 
//----------------------------------------------

void EndsScreen() {
	cout << "\n----------------------------------------------------\n";
	cout << "\n\t\t Program Ends :-) \n";
	cout << "\n----------------------------------------------------\n\n";
}

//---------------------------------------------


//Run The Bank System : 
//----------------------------------------------

void Header() {
	cout << "=======================================================================================\n\n";
	cout << "\t\t\t\t  Main Menu Screen ";
	cout << "\n\n=======================================================================================\n\n";
}
void BankMainMenu() {
	system("cls");
	Header();
	cout << right << setw(25) << "[1]" << " Show Client Menu.\n";
	cout << right << setw(25) << "[2]" << " Add New Client.\n";
	cout << right << setw(25) << "[3]" << " Delete Client.\n";
	cout << right << setw(25) << "[4]" << " Update Client.\n";
	cout << right << setw(25) << "[5]" << " Find Client.\n";
	cout << right << setw(25) << "[6]" << " Exit.\n";
	cout << "\n=======================================================================================\n";
}
enMenuOptions MakeOperations(enMenuOptions UserChoice, vector<stClient> &vClient) {
	switch (UserChoice) {
	case enMenuOptions::Show:
	{
		PrintClientMenu(vClient);
		return enMenuOptions::Show;
	}
	case enMenuOptions::Add:
	{
		AddClients();
		return enMenuOptions::Add;
	}
	case enMenuOptions::Delete:
	{
		
		DeleteAccountFromFile(vClient);
		return enMenuOptions::Delete;
	}
	case enMenuOptions::Update:
	{
		UpdateClient(vClient);
		return enMenuOptions::Update;
	}
	case enMenuOptions::find:
	{
		
		FindClientByAccountNumber(vClient);
		return enMenuOptions::find;
	}case enMenuOptions::Exit:
	{
		EndsScreen();
		return enMenuOptions::Exit;
	}
	default:
		return Show;
	}
	return Show;
}
void LunchBankSystem() {
	vector<stClient>vClients = LoadDataFromFile(ClientFile);
	enMenuOptions Choice;
	do {
		BankMainMenu();
		Choice=GetChoice();
		Choice=MakeOperations(Choice,vClients);
		vClients = LoadDataFromFile(ClientFile);
		if (Choice!= enMenuOptions::Exit) {
			cout << "\n\n\nPress any Key to go Back Main Menu...";
			system("pause>0");
		}
		
	} while (Choice != enMenuOptions::Exit);
}

//---------------------------------------------

int main()
{
	LunchBankSystem();

	system("pause>0");
	return 0;
}


