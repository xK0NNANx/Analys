#pragma once
#include <string>
#include <iostream>
#include <regex>
#include <list>
#include <vector>;


using namespace std;


class Token {
private:
	string lexeme;
	string Type;
	int NumberString;
	vector<pair<string, string>> TokenTypeList = {
		{"NUMBER", "^[0-9]{1,}$"},
		{"FOR", "^for"},
		{"WHILE", "^while"},
		{"BREAK", "^break"},
		{"SWITCH", "^switch"},
		{"CASE", "^case"},
		{"DEFAULT", "^default"},
		{"IF", "^if"},
		{"SPACE", " "},
		{"LBRA", "^\\{"},
		{"LPAR", "^\\("},
		{"RPAR", "^\\)"},
		{"RBRA", "^\\}"},
		{"COLON",":"},
		{"ELSE", "^else"},
		{"OPERATOR", "\\/|\\*|\\+\\-|\\+-|\\-+|\\++|\\+=|\\-=|\\*=|\\/=|\\=|\\>|\\>=|\\<|\\<=|\\==|\\(\\)"},
		{"TYPE", "int|float|bool|string|char"},
		{"PEREM", "^[A-Za-z]+$"},
		{"SEMICOLON", "^;"}
	};
	
public:
	Token(string lex, int Numb) {
		lexeme = lex;
		Type = opr_TypeToken(lexeme);
		NumberString = Numb;
	}
	

	const string opr_TypeToken(string lexeme) {
		for (int i = 0; i < TokenTypeList.size(); i++) {
			regex regular(TokenTypeList[i].second);
			if (regex_match(lexeme, regular)) {
				return(TokenTypeList[i].first);
			}
		}
		return "UNKNOWN";
    }

	string getType() {
		return Type;
	}

	string getLexem() {
		return lexeme;
	}

	int getNumberString() {
		return NumberString;
	}

	void print() {
		cout << Type << " ";
	}
};