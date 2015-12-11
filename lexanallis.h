#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>

#ifndef __kompil__lexanallis__
#define __kompil__lexanallis__

using namespace std;

extern const string lexemes[40][2];

struct Lexem{
    string TypeLexem;
    string ValuaLexem;
    int NumberOfStr;
};

extern bool commentarii;

extern vector<Lexem> result;

bool ChekOfBorder(char Symbol);

bool isSymbol(char letter);

bool isNumber(char Symbol);

void Error(string a, Lexem b, int Num);

void ComparisonAndWriter(string inText, int NumStr);

bool doubleSymble (string Symbol);

void parsing(string stitch,int NumberString);;

string reading(string A);

#endif
