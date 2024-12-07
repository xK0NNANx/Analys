#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include "Lexer.h"
#include "Parser.h"
#include "WorkWithFile.h"

int main()
{
    string code;
    File_work Files;
    Files.ImportCode(code);
    Lexer lex(code);
    parser pars(lex);
    pars.print();
    pars.ImportToFile();

}
