#include <iostream>
#include <vector>
#include "lexanallis.h"
#include "sintaxanalis.h"

using namespace std;

vector<Lexem> Node::lex = vector<Lexem>();
int Node::index_lex = 0;
void Node::printNode(Node* node) {
        cout << node->type << ": " << node->data;
        cout << "{ ";
        for ( Node* el : node->childs) {
            printNode(el);
        }
        cout << " }";
    }

void Node::print (){
        printNode(this);
    }


    Node::Node(int type){
        this -> type = type;
    }

    Node::Node(vector<Lexem>& lex) {
        Node::lex = lex;
        Node::index_lex = 0;
        if (lex.size() == 0){
            cout<<"Файл пуст"<<"\n";
            exit(0);
        }


        if (Node::cur_lexem().ValuaLexem != "main()" ) {  // проверка на main()
            cout << "main not found";
            exit(0);
        }
        Node::next_lexem();
        if (Node::cur_lexem().ValuaLexem != "{") {      // проверка на { после main
            cout << "expected '{' in"<<result[index_lex].NumberOfStr<<"line";
            exit(0);
        }
        Node::next_lexem();

        this->type = ND_STMTLIST;
        this->parse(this);
    }

        Node::Node(int type, int datatype, string data){
        this -> type = type;
        this -> data = data;
        this -> datatype = datatype;
    }

        Node::Node(int type, string data){
        this -> type = type;
        this -> data = data;
    }



    void Node::add_node(Node* node) {
        this->childs.push_back(node);
    }

    Node* Node::parse_expression() {
        Lexem cur_lex = cur_lexem();
        string expression = cur_lex.ValuaLexem;
        while (cur_lex.TypeLexem == "EE_NAME" || cur_lex.TypeLexem == "EE_VAL" || cur_lex.TypeLexem == "EE_PLUS" || cur_lex.TypeLexem == "EE_MINUS" || cur_lex.TypeLexem == "EE_MULT" || cur_lex.TypeLexem == "EE_DEV" || cur_lex.TypeLexem == "EE_PROC"){
            cur_lex = next_lexem();
            expression += cur_lex.ValuaLexem;
        }
        Node* exp = new Node(ND_VARI, expression);
        return exp;
    }

    Node* Node::parse_var_init() {
        Lexem cur_lex = Node::next_lexem();
        if (cur_lex.TypeLexem != "EE_NAME") {
            cout << "Unexpected symbol: " + cur_lex.ValuaLexem + ". EE_NAME expected;";
            return NULL;
        }
        Node* node = new Node(ND_INIT, cur_lex.ValuaLexem);
        cur_lex = Node::next_lexem();
        if (cur_lex.TypeLexem == "EE_EQ") {
            cur_lex = Node::next_lexem();
            node->parse_expression();
            cur_lex = Node::cur_lexem();
            if(cur_lex.TypeLexem != "EE_SIMICOL") {
                cout << "Unexpected symbol: " + cur_lex.ValuaLexem + ", EE_SIMICOL expected; ";
                Node::next_lexem();
                return node;
            }
        } else if (cur_lex.TypeLexem == "EE_SIMICOL") {
            Node::next_lexem();
            return node;
        } else cout<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". EE_EQ or EE_SIMICOL expected;";
        return NULL;
    }
    Node* Node::parse_assign(string name){
        Node* node = new Node (ND_ASSIGN, name);
        node->add_node(parse_expression());
        return node;

    }

    Node* Node::parse_logic_expression(){
        Lexem cur_lex = cur_lexem();
        string expression = cur_lex.ValuaLexem;
        while (cur_lex.TypeLexem == "EE_NAME" || cur_lex.TypeLexem == "EE_VAL" || cur_lex.TypeLexem == "EE_PLUS" || cur_lex.TypeLexem == "EE_MINUS" || cur_lex.TypeLexem == "EE_MULT" || cur_lex.TypeLexem == "EE_DEV" || cur_lex.TypeLexem == "EE_PROC" || cur_lex.TypeLexem == "EE_MORE" ||cur_lex.TypeLexem == "EE_LESS" || cur_lex.TypeLexem == "EE_MOREQU" ||cur_lex.TypeLexem == "EE_LESSEAU" || cur_lex.TypeLexem == "EE_EQUAL" || cur_lex.TypeLexem == "EE_NOTEQU" ||cur_lex.TypeLexem == "EE_AND" ||cur_lex.TypeLexem == "EE_OR" || cur_lex.TypeLexem == "EE_NOT" ||cur_lex.TypeLexem == "EE_DOUBPL" || cur_lex.TypeLexem == "EE_DOUBMIN"){
            cur_lex = next_lexem();
            expression += cur_lex.ValuaLexem;
        }
        Node* exp = new Node(ND_VARI, expression);
        return exp;
    }

    Node* Node::parse_stmt_list() {
        Lexem cur_lex = Node::cur_lexem();
        Node* node = new Node(ND_STMTLIST);
        while ( cur_lex.ValuaLexem == "}" ) {
            node->add_node(parse_statement());
        }
        return node;
    }

    Node* Node::parse_statement() {
        while (true) {
            Lexem cur_lex = Node::cur_lexem();
            if (cur_lex.TypeLexem == "EE_SIMICOL") {
                next_lexem();
                continue;
            } else if (cur_lex.TypeLexem == "EE_TYPE") {
                return parse_var_init();
            }
            else if (cur_lex.TypeLexem == "EE_NAME"){
                string name = cur_lex.TypeLexem;
                cur_lex = Node::next_lexem();
                if ((cur_lex.ValuaLexem == "=") || (cur_lex.ValuaLexem == "+=") || (cur_lex.ValuaLexem == "-=") || (cur_lex.ValuaLexem == "*=") || (cur_lex.ValuaLexem == "/=") || (cur_lex.ValuaLexem == "%=")) {
                    Node* node = parse_assign (name);
                    cur_lex = Node::cur_lexem();
                    if (cur_lex.ValuaLexem != ";") {
                        cout << "Unexpected symbol: " + cur_lex.ValuaLexem + ". EE_SIMICOL expected;";
                        return NULL;
                    }
                    Node::next_lexem();
                    return node;
                } else {
                    cout << "Unused expression found;";
                    return NULL;
                }
            }
            else if (cur_lex.TypeLexem == "EE_IF"){
                cur_lex = Node::next_lexem();
                if (cur_lex.ValuaLexem != "(") {
                    cout << cur_lex.NumberOfStr<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". OPEN BRACKET expected;";
                    return NULL;
                }
                cur_lex = Node::next_lexem();
                Node* node = new Node(ND_IF);
                node->add_node(parse_logic_expression());
                cur_lex = Node::next_lexem();
                if (cur_lex.ValuaLexem != ")") {
                    cout << cur_lex.NumberOfStr<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". CLOSE BRACKET expected;";
                    return NULL;
                }
                cur_lex = Node::next_lexem();
                if (cur_lex.ValuaLexem != "{") {
                    cout << cur_lex.NumberOfStr<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". OPEN BRACKET expected '{';";
                    return NULL;

                }
                node->add_node(parse_stmt_list());
                cur_lex = Node::next_lexem();
                if (cur_lex.ValuaLexem != "}") {
                    cout << cur_lex.NumberOfStr<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". CLOSE BRACKET expected '}';";
                    return NULL;
                }
                if (cur_lex.ValuaLexem == "else") {
                    node -> type = ND_IFELSE;
                    cur_lex = Node::next_lexem();
                    if (cur_lex.ValuaLexem != "{") {
                        cout << cur_lex.NumberOfStr<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". OPEN BRACKET expected '{';";
                        return NULL;
                    }
                    node->add_node(parse_stmt_list());
                    cur_lex = Node::next_lexem();
                }
                return node;
            } else if(cur_lex.TypeLexem == "EE_WHILE") {
                cur_lex = Node::next_lexem();
                if (cur_lex.ValuaLexem != "(") {
                    cout << cur_lex.NumberOfStr<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". OPEN BRACKET expected;";
                    return NULL;
                }
                cur_lex = Node::next_lexem();
                Node* node = new Node(ND_WHILE);
                node->add_node(parse_logic_expression());
                cur_lex = Node::next_lexem();
                if (cur_lex.ValuaLexem != ")") {
                    cout << cur_lex.NumberOfStr<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". CLOSE BRACKET expected;";
                    return NULL;
                }
                cur_lex = Node::next_lexem();
                if (cur_lex.ValuaLexem != "{") {
                    cout << cur_lex.NumberOfStr<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". OPEN BRACKET expected '{';";
                    return NULL;

                }
                node->add_node(parse_stmt_list());
                cur_lex = Node::next_lexem();
                return node;
            } else if (cur_lex.TypeLexem == "EE_FOR") {
                cur_lex = Node::next_lexem();
                Node* node = new Node(ND_FOR);
                if (cur_lex.ValuaLexem != "(") {
                    cout << cur_lex.NumberOfStr<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". OPEN BRACKET expected;";
                    return NULL;
                }
                node->add_node(parse_var_init());
                cur_lex = Node::next_lexem();
                if (cur_lex.ValuaLexem != ";") {
                    cout << cur_lex.NumberOfStr<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". SEMICOLON expected;";
                    return NULL;
                }
                cur_lex = Node::next_lexem();
                node->add_node(parse_logic_expression());
                if (cur_lex.ValuaLexem != ";") {
                    cout << cur_lex.NumberOfStr<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". SEMICOLON expected;";
                    return NULL;
                }
                cur_lex = Node::next_lexem();
                node->add_node(parse_expression());
                if (cur_lex.ValuaLexem != ")") {
                    cout << cur_lex.NumberOfStr<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". CLOSE BRACKET expected;";
                    return NULL;
                }
                cur_lex = Node::next_lexem();
                if (cur_lex.ValuaLexem != "{") {
                    cout << cur_lex.NumberOfStr<< "Unexpected symbol: " + cur_lex.ValuaLexem + ". OPEN BRACKET expected '{';";
                    return NULL;

                }
                node->add_node(parse_stmt_list());
                return node;


            }


        }
    }

    void Node::parse (Node* node) {
        Lexem cur_lex = Node::cur_lexem();
        while ( cur_lex.ValuaLexem != "}" ) {
            node->add_node(parse_statement());
        }
    }
