#include <iostream>
#include "lexanallis.h"
#include "sintaxanalis.h"

int main(int argc, const char * argv[]) {
    reading("/Users/elizaveta/Documents/Универ/Новая папка/языки/lexanalis/lexanalis/newfile.txt");
    Node* node = new Node(result);
    node->print();
    for (int a=0; a<result.size(); a++) {
        //cout<<result[a].ValuaLexem<<' '<<result[a].TypeLexem<<' '<<result[a].NumberOfStr<<' '<<'\n';
    }
}
