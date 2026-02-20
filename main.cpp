#include <iostream>

#define OPERATOR    1
#define OPERAND     2
#define NEGATION    3

using namespace std;

struct token{
    int type; //number, operator or negation
    string data;
};
vector <token> tokens;

void make_tokens(string eq){
    
}

int main(){
    //main loop of the program
    while(true){
        string equasion = "";
        getline(cin, equasion);

        cout<<equasion <<" = "<<solve();
    }

    return 0;
}