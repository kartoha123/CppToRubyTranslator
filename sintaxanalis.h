#include <iostream>
#include <vector>

#ifndef __kompil__sintaxanalis__
#define __kompil__sintaxanalis__

#include "lexanallis.h"

using namespace std;

enum {
    ND_PLUS,
    ND_MINUS,
    ND_MULT,
    ND_DIV,
    ND_MOD,
    ND_ASSIGN,
    ND_INIT,
    ND_VARI,
    ND_CONST,
    ND_PLUCEQU,
    ND_MINUCEQU,
    ND_MULTEQU,
    ND_DEVEQU,
    ND_PROCEQU,
    ND_MORE,
    ND_LESS,
    ND_EQU,
    ND_MOREQU,
    ND_LESSEQU,
    ND_NOTEQU,
    ND_AND,
    ND_OR,
    ND_NOT,
    ND_DOUBPL,
    ND_DOUBMIN,

    ND_IF,
    ND_IFELSE,
    ND_FOR,
    ND_WHILE,
    ND_STMTLIST


};

enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL
};

class Node{ //структура листика
public:
    std::vector<Node*> childs;
    int type;
    string data;
    int datatype;
    static vector<Lexem> lex;
    static int index_lex;


    void printNode(Node* node);

    void print ();


    Node(int type);

    Node(vector<Lexem>& lex);

    Node(int type, int datatype, string data);

    Node(int type, string data);

    static Lexem next_lexem() {
        if (Node::index_lex + 1 >= Node::lex.size()) {
            cout << "Unexpected end of file. { Expected;";
        }
        return Node::lex[++Node::index_lex];
    }

    static Lexem cur_lexem() {
        return Node::lex[Node::index_lex];
    }

    void add_node(Node* node);

    Node* parse_expression();

    Node* parse_var_init();

    Node* parse_assign(string name);

    Node* parse_logic_expression();

    Node* parse_stmt_list();

    Node* parse_statement();

    void parse (Node* node);


private:


};








#endif /* defined(__kompil__sintaxanalis__) */
