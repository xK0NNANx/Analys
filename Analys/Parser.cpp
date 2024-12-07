#define _CRT_SECURE_NO_WARNINGS
#include <vector>;
#include <iostream>;
#include "Lexer.h";
#include "WorkWithFile.h"

using namespace std;

class parser {
private:
	vector<pair<string, int>> ErrorArray;
	int CountStaples = 0;


public:

	void CheckPerem(Token Token, vector<string>& usingPerem, Lexer Tokens, int i) {
		if (Token.getType() == "PEREM") {
			if (find(usingPerem.begin(), usingPerem.end(), Token.getLexem()) == usingPerem.end()) {
				if (usingPerem.back() != Token.getLexem() and Tokens.TokenList[i - 1].getType() == "TYPE") {
					usingPerem.push_back(Token.getLexem());
				}else if(usingPerem.back() != Token.getLexem() and Tokens.TokenList[i - 1].getType() != "TYPE") ErrorArray.push_back({ "Unknown command", Token.getNumberString() });
				else if(usingPerem.back() == Token.getLexem() and Tokens.TokenList[i - 1].getType() == "TYPE") ErrorArray.push_back({ "redefining types", Token.getNumberString() });
			}
			else if (Tokens.TokenList[i - 1].getType() == "TYPE") ErrorArray.push_back({ "redefining types", Token.getNumberString() });
		}
	}

	parser(Lexer Tokens) {
		vector<string> usingPerem = {"0"};
		for (int i = 0; i < Tokens.TokenList.size(); i++) {
			Token Token = Tokens.TokenList[i];

			CheckPerem(Token, usingPerem, Tokens , i);
			if (Token.getType() == "BREAK") {
				ErrorArray.push_back({ "break out of the loop", Token.getNumberString() });
			}

			if (Token.getType() == "WHILE" or Token.getType() == "FOR" or Token.getType() == "SWITCH") {
				while (Tokens.TokenList[i].getType() != "LBRA" and Tokens.TokenList[i].getType() != "SEMICOLON") {
					i++;
					if (Tokens.TokenList[i].getType() == "BREAK" and Tokens.TokenList[i-1].getType() != "RPAR") {
						ErrorArray.push_back({"Break is in a loop", Tokens.TokenList[i].getNumberString()});
					}
					CheckPerem(Tokens.TokenList[i], usingPerem, Tokens, i);
					if (i == Tokens.TokenList.size()) {
						ErrorArray.push_back({ "No end staples", Tokens.TokenList.back().getNumberString()});
					}
				}
				CountStaples++;
				while (CountStaples != 0)
				{
					i++;
					if (Tokens.TokenList[i].getType() == "LBRA") CountStaples++;
					if (Tokens.TokenList[i].getType() == "RBRA") CountStaples--;
					CheckPerem(Tokens.TokenList[i], usingPerem, Tokens , i);

					if (Tokens.TokenList[i].getType() == "BREAK") {
						if (Tokens.TokenList[i - 1].getType() != "LBRA" and Tokens.TokenList[i - 1].getType() != "RBRA"
							and Tokens.TokenList[i - 1].getType() != "RPAR" and Tokens.TokenList[i - 1].getType() != "LPAR"
							and Tokens.TokenList[i - 1].getType() != "COLON" and Tokens.TokenList[i - 1].getType() != "SEMICOLON") {
							ErrorArray.push_back({ "Unknown command before BREAK", Tokens.TokenList[i].getNumberString()});
						}
						if(Tokens.TokenList[i - 1].getType() == "RPAR" and Tokens.TokenList[i - 2].getType() == "TYPE")
							ErrorArray.push_back({ "Not possible to convert the type to break", Tokens.TokenList[i].getNumberString() });
						if (Tokens.TokenList[i+1].getType() != "SEMICOLON") {
							ErrorArray.push_back({ "Unknown command past BREAK", Tokens.TokenList[i].getNumberString()});
						}
					}
				}
				
			}
		}
		/*if (ErrorArray.empty()) {
			ErrorArray.push_back({ "All break write correct", 1 });
		}*/
	}

	void print() {
		for (int i = 0; i < ErrorArray.size(); i++) {
			cout << "error: " << ErrorArray[i].first << " on string " << ErrorArray[i].second << "\n";
		}
	}

	void ImportToFile() {
		File_work file;
		file.ImportToFile(ErrorArray);
	}
};