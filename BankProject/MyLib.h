#pragma once
#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
using namespace std;


namespace MyLib{

	int RandomNumber(int from, int to) {
		int RandomN = rand() % (to - from + 1) + from;
		return RandomN;
	}

	int SumTwoNumbers(int f,int x) {
		return f + x;
	}

	int ValditionNumber() {
		int Number = 0;
		cout << "Please enter your number! ";
		cin >> Number;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid Number, Please eneter a valid Number!" << endl;
			cin >> Number;
		}
		return Number;
	}

	void swapUsingRef(int& A, int& B) {
		int swaper = 0;
		swaper = A;
		A = B;
		B = swaper;
	}
	void swapUsingPointer(int * A, int* B) {
		int swaper ;
		swaper = *A;
		*A = *B;
		*B = swaper;
	}

	short AskUserToEnterANumber() {
		short Check = 0;
		cout << "Please Enter a Number to Check? ";
		cin >> Check;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Wrong Input, Please enter a valid digit? ";
			cin >> Check;
		}
		return Check;
	}

	int SumMatrix(int Matrix[3][3], short row, short colm) {
		int sum = 0;
		for (int x = 0; x < row; x++) {
			for (int g = 0; g < colm; g++) {
				sum += Matrix[x][g];
			}
		}
		return sum;
	}

	short CountNumberInMatrix(int Matrix[3][3], int Check, short Rows, short Colm) {
		short count = 0;

		for (int a = 0; a < Rows; a++) {
			for (int x = 0; x < Colm; x++) {

				if (Matrix[a][x] == Check) {
					count++;
				}

			}

		}
		return count;

	}
	bool ChecKIfNumberInMatrix(int Mtx[3][3], int check, short row, short colm) {

		for (int a = 0; a < row; a++) {
			for (int x = 0; x < colm; x++) {
				if (Mtx[a][x] == check) {
					return true;
				}
			}
		}
		return false;
	}

	char InvertCharacter(char Charact) {
		return isupper(Charact) ? tolower(Charact) : toupper(Charact);
	}


	char ReadChar(string message) {
		char Letter = ' ';
		cout << message<<" ";
		cin >> Letter;
		return Letter;
	}
	string ReadName() {
		string Name = "";
		cout << "Please enter Your name!\n";
		cin >> Name;
		return Name;
	}
	string ReadText(string message) {
		string txt = "";
		cout << message << " ";
		getline(cin, txt);
		return txt;
	}

	string InvertAllStringLetterCase(string Text) {
		for (int b = 0; b < Text.length(); b++) {
			Text[b] = InvertCharacter(Text[b]);
		}
		return Text;
	}

	string ConvertAllTxtToUpper(string MyTxt) {
		bool FirstLetter = true;
		for (int k = 0; k < MyTxt.length(); k++) {
			MyTxt[k] = toupper(MyTxt[k]);
		}
		return MyTxt;
	}

	string ConvertAllTxtToLower(string MyTxt) {
		bool FirstLetter = true;
		for (int k = 0; k < MyTxt.length(); k++) {
			MyTxt[k] = tolower(MyTxt[k]);
		}
		return MyTxt;
	}

	enum enConversionString { Upper = 1, Lower = 2 };
	string ConvertAllTxtToLowerOrUpper(string MyTxt, enConversionString ConvertTo) {
		for (int k = 0; k < MyTxt.length(); k++) {
			(ConvertTo == enConversionString::Upper) ? MyTxt[k] = toupper(MyTxt[k]) : MyTxt[k] = tolower(MyTxt[k]);
		}
		return MyTxt;
	}

	enum enCountChar { Capital = 1, Small = 2, AllPargraph = 3 };

	short CountCharacters(string MyStr, enCountChar enumChar = enCountChar::AllPargraph) {
		if (enumChar == enCountChar::AllPargraph) {
			return MyStr.length();
		}
		short Count = 0;
		for (short f = 0; f < MyStr.length(); f++) {
			if (isupper(MyStr[f]) && enumChar == enCountChar::Capital) {
				Count++;
			}
			if (islower(MyStr[f]) && enumChar == enCountChar::Small) {
				Count++;
			}
		}
		return Count;
	}
	bool CheckIfCharIsVowel(char ToCheck) {
		ToCheck = tolower(ToCheck);
		return (ToCheck == 'a' || ToCheck == 'i' || ToCheck == 'e' || ToCheck == 'o' || ToCheck == 'u');
	}

	string JointText(string Arr[100], short ArrLength, string Delim) {
		string ToJoin = "";
		for (short x = 0; x < ArrLength; x++) {
			ToJoin += Arr[x] + Delim;
		}
		return ToJoin.substr(0, ToJoin.length() - Delim.length());

	}
	string JointText(vector <string>& vWords, string Delim) {
		string ToJoin = "";
		for (string& txt : vWords) {
			ToJoin += txt + Delim;
		}
		return ToJoin.substr(0, ToJoin.length() - Delim.length());

	}

	vector <string> SplitText(string& Txt, string Delim) {
		vector<string>vWords;
		string word = "";
		short Pos = 0;
		while ((Pos = Txt.find(Delim)) != std::string::npos) {
			word = Txt.substr(0, Pos);
			if (word != "") {
				vWords.push_back(word);
			}
			Txt.erase(0, Pos + Delim.length());
		}
		if (Txt != "") {
			vWords.push_back(Txt);
		}
		return vWords;
	}

	struct stClientData {
		string Account_Number = "";
		string PIN_Code = "";
		string Name = "";
		string Phone = "";
		double Account_Blance = 0;
	};

	string ConvertRecordToLine(stClientData client, string sperator = "#//#") {
		string ConvertLine = "";
		ConvertLine += client.Account_Number + sperator;
		ConvertLine += client.PIN_Code + sperator;
		ConvertLine += client.Name + sperator;
		ConvertLine += client.Phone + sperator;
		ConvertLine += to_string(client.Account_Blance);
		return ConvertLine;
	}
	
	stClientData ConvertLineToRecord(string Line, string sperator = "#//#") {
		vector<string>vConvert;
		vConvert = SplitText(Line, sperator);
		stClientData client;
		client.Account_Number = vConvert.at(0);
		client.PIN_Code = vConvert.at(1);
		client.Name = vConvert.at(2);
		client.Phone = vConvert.at(3);
		client.Account_Blance = stod(vConvert.at(4));
		return client;
	}
}