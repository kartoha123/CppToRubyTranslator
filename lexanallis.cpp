#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "lexanallis.h"

using namespace std;

const string lexemes[40][2] =
{
    //типы данных
    {"int","EE_TYPE"},
    {"bool","EE_TYPE"},
    {"string","EE_TYPE"},
    {"float","EE_TYPE"},

    //Операторы
    {"+", "EE_PLUS"},
    {"-", "EE_MINUS"},
    {"=", "EE_EQ"},
    {"*", "EE_MULT"},
    {"/", "EE_DEV"},
    {"\"", "EE_QUOTE"},
    {"%", "EE_PROC"},
    {"+=", "EE_PLUCEQU"},
    {"-=", "EE_MINUCEQU"},
    {"*=", "EE_MULTEQU"},
    {"/=", "EE_DEVEQU"},
    {"%=", "EE_PROCEQU"},
    {">", "EE_MORE"},
    {"<", "EE_LESS"},
    {">=", "EE_MOREQU"},
    {"<=", "EE_LESSEQU"},
    {"==", "EE_EQUAL"},
    {"!=", "EE_NOTEQU"},
    {"&&", "EE_AND"},
    {"||", "EE_OR"},
    {"!", "EE_NOT"},
    {"++", "EE_DOUBPL"},
    {"--", "EE_DOUBMIN"},
    {"(", "EE_OPENBKT"},
    {")", "EE_CLOSEBKT"},
    {"{", "EE_OPENBRACE"},
    {"}", "EE_CLOSEBRACE"},
    {";", "EE_SIMICOL"},

    //зарезервированные слова
    {"if", "EE_IF"},
    {"else", "EE_ELSE"},
    {"for", "EE_FOR"},
    {"while", "EE_WHILE"},
    {"true", "EE_TRUE"},
    {"false", "EE_FALSE"},
    {"error", "EE_ERROR"},
    {"main()", "EE_MAIN"}

};

bool commentarii = false;
vector<Lexem> result;

bool ChekOfBorder(char Symbol){
    if (Symbol == '=' or Symbol == ' ' or Symbol == '"' or Symbol == '+' or Symbol == '-' or Symbol == '*' or Symbol == '/' or Symbol == '%' or Symbol == ';' or Symbol == '(' or Symbol == ')' or Symbol == '{' or Symbol == '}' or Symbol == '<' or Symbol == '>' or Symbol == '!' or Symbol == '|' or Symbol == '&' or Symbol == '\0')
        return true;
    else return false;
}

bool isSymbol(char letter){
    if (((letter >= 'a') && (letter <= 'z')) || ((letter >= 'A') && (letter <= 'Z')))
        return true;
    else return false;
}

bool isNumber(char Symbol)
{
    if (Symbol >= '0' && Symbol <= '9')
        return true;
    return false;
}

void Error(string a, Lexem b, int Num){
    for (int i = 0; i < a.length(); i++) {
        if (!((isSymbol(a[i])) or (isNumber(a[i])) or (ChekOfBorder(a[i]))or (a[i] == '_') or (a[i] == '.'))) {
            b.TypeLexem = "EE_ERROR_2";
            b.ValuaLexem = a;
            b.NumberOfStr = Num;
            result.insert(result.end(), b);
            cout << a[i];
            return;

        }
    }
    b.TypeLexem = "EE_ERROR_1";
    b.ValuaLexem = a;
    b.NumberOfStr = Num;
    result.insert(result.end(), b);
    return;

}


void ComparisonAndWriter(string inText, int NumStr){
    Lexem cell;
    bool flag = 1;
    bool point = false;
    int j = 0;
    if ((inText.length() != 0) && (inText[0] != ' ') &&(inText[0] != '\0')) {
        for (int a = 0; a < inText.length(); a++){
            if (!isNumber(inText[a])) {
                if (inText[a] == '.' and point == false){
                    point = true;

                }
                else flag = 0;

            }
        }
        if (flag == 1) {
            cell.TypeLexem = "EE_VAL";
            cell.ValuaLexem = inText;
            cell.NumberOfStr = NumStr;
            result.insert(result.end(), cell);
            return;
        }

        for (int i = 0; i < 40; i++) {
            if (lexemes[i][j] == inText) {
                cell.TypeLexem = lexemes[i][1];
                cell.ValuaLexem = lexemes[i][0];
                cell.NumberOfStr = NumStr;
                result.insert(result.end(), cell);
                return;
            }
        }
        if (isSymbol(inText[0])){
            int i = 1;
            bool flagok = true;
            while (i < inText.length()){
                if (isNumber(inText[i]) || inText[i] == '_' || isSymbol(inText[i])) {
                    i++;
                }
                else{
                    Error(inText, cell, NumStr);
                    i++;
                    flagok = false;
                }

            }
            if (flagok == true) {


                cell.TypeLexem = "EE_NAME";
                cell.ValuaLexem = inText;
                cell.NumberOfStr = NumStr;
                result.insert(result.end(), cell);
                return;

            }
        }
        else {
            Error(inText, cell, NumStr);
        }

    }
}




bool doubleSymble (string Symbol){
    if (Symbol == "==" or Symbol == "<=" or Symbol == ">=" or Symbol == "++" or Symbol == "--" or Symbol == "+=" or Symbol == "/=" or Symbol == "%=" or Symbol == "-=" or Symbol == "*=" or Symbol == "!=" or Symbol == "||" or Symbol == "&&")
        return true;
    else return false;
}


void parsing(string stitch,int NumberString){
    string Lex = "";
    string LexemInText = "";
    int i = 0;
    Lexem cell;
    while (i <= stitch.length()){
        bool dupe = false;
        if ( commentarii == true){
            while ((stitch[i] != '*')) {
                i++;
                if (stitch[i] == '\0') {
                    return;
                }
            }
            if (stitch[i+1] == '/') {
                i = i+2;
                commentarii = false;
            }

        }
        if (stitch[i] == '/'){
            if (stitch[i+1] == '/') {
                return;
            }
            if (stitch[i+1] == '*') {
                commentarii = true;
                i = i+2;
                while ((stitch[i] != '*')) {
                    i++;
                    if (stitch[i] == '\0') {
                        return;
                    }
                }
                if (stitch[i+1] == '/') {
                    i = i+2;
                    commentarii = false;
                }
            }
        }
        if (ChekOfBorder(stitch[i])) {
            if (ChekOfBorder(stitch[i+1])) {
                Lex = stitch[i];

                if (doubleSymble(Lex+=stitch[i+1])){

                    ComparisonAndWriter(LexemInText,NumberString);
                    LexemInText = "";
                    ComparisonAndWriter(Lex, NumberString);
                    Lex = "";
                    i=i+2;
                    dupe = true;
                }
                if(Lex == "()" && LexemInText == "main"){
                    LexemInText = LexemInText + Lex;
                    ComparisonAndWriter(LexemInText,NumberString);
                    i = i+2;
                    Lex = "";
                    LexemInText = "";
                }
            }
            Lex = "";
            if (dupe == false){
                if (stitch[i] == '"') {
                    i++;
                    while (stitch[i] != '"') {
                        if (stitch[i] == '\0'){
                            string cov = "\"";
                            cov = cov + LexemInText;
                            Error(cov, cell, NumberString);
                            return;
                        }
                        LexemInText += stitch[i];
                        i++;
                    }
                    ComparisonAndWriter("\"", NumberString);

                    cell.TypeLexem = "EE_VAL";
                    cell.ValuaLexem = LexemInText;
                    cell.NumberOfStr = NumberString;
                    result.insert(result.end(), cell);
                    LexemInText = "";
                    ComparisonAndWriter(string(1,stitch[i]), NumberString);

                    i++;
                }
                else{
                    ComparisonAndWriter(LexemInText,NumberString);
                    LexemInText = "";
                    ComparisonAndWriter(string(1,stitch[i]),NumberString);

                    i++;

                }


            }}
        else {
            LexemInText = LexemInText + stitch[i];

            i++;

        }
    }
};



string reading(string A){
    int i = 1;
    string line;
    string sss;
    ifstream fileread(A);
    if (!fileread.is_open())
        cout << "Файл не может быть открыт!\n";
    else {
        while (!fileread.eof()) {
            getline (fileread, line);
            parsing(line,i);
            i++;
        }
    }
    fileread.close();
    return line;
}
