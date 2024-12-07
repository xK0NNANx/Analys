#include "Tokens.h"
#include "vector"
#include <iostream>
#include <fstream>
#include <set>


class Lexer {
private:
	string code;
    vector<char> NewTokEl = {
        '{','(',')','}','+','-',' ','\n','\0',';','[',']','=', '>', '<', '=', '\t', ':', ' '
    };
public:
    vector<Token> TokenList;
    Lexer(string c) {
        code = c;
        code.push_back('\0');
        Lex();
    }

	void Lex() {
        string TimeString;
        string comment;
        int NumberString = 1;
        bool compile = 1;
        for (char i : code) {
            if (i == '\n') NumberString++;
            if ((i == '/' and TimeString[0] == '/') or (i == '*' and TimeString[0] == '/')) {
                compile = 0;
                comment.push_back(TimeString[0]);
                comment.push_back(i);
                TimeString = "";
            }
            if (comment == "//" and i == '\n') {
                compile = 1;
                comment = "";
                continue;
            }
            if (comment == "/*" and i == '*') {
                comment.push_back(i);
                continue;
            }
            if (comment == "/**") {
                if (i == '/') {
                    compile = 1;
                    comment = "";
                    continue;
                }
                else {
                    comment.pop_back();
                }
            }

            if (compile) {
                if (find(NewTokEl.begin(), NewTokEl.end(), i) != NewTokEl.end()) {
                    if (!TimeString.empty()) {
                        if (find(NewTokEl.begin(), NewTokEl.end(), TimeString[0]) == NewTokEl.end()) {
                            Token tok(TimeString, NumberString);
                            TimeString = "";
                            TokenList.push_back(tok);
                        }
                    }
                }
                else
                {
                    if (find(NewTokEl.begin(), NewTokEl.end(), TimeString[0]) != NewTokEl.end() and find(NewTokEl.begin(), NewTokEl.end(), i) == NewTokEl.end() and !TimeString.empty()) {
                        Token tok(TimeString, NumberString);
                        TokenList.push_back(tok);
                        TimeString = "";
                        TimeString.push_back(i);
                    }
                    else {
                        TimeString.push_back(i);
                    }
                }
                if (find(NewTokEl.begin(), NewTokEl.end(), i) != NewTokEl.end()) {
                    if (i != ' ' and i != '\n' and i != '\0' and i != '\t') {
                        TimeString.push_back(i);
                    }
                    else if (TimeString.size() != 0) {
                        Token tok(TimeString, NumberString);
                        TokenList.push_back(tok);
                        TimeString = "";
                    }

                }
            }
        }

        //for (int i = 0; i < TokenList.size(); i++) {
        //    TokenList[i].print();
        //}
   }

};