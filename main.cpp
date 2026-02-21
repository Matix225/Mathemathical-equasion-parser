#include <bits/stdc++.h>

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
    tokens.clear(); //get ready for new equasion

    for(int i = 0; i < (int)eq.length(); i++){
        token t;

        if(eq[i] == '+'){
            t.type = OPERATOR;
            t.data = "+";
            tokens.push_back(t);
        }
        else if(eq[i] == '-'){
            //minus can be an operator or number sign(negation)
            //if '-' is first sign in equasion it must be number sign
            //if before '-' was other operator then '-' is a number sign
            bool minus_type = false;

            if(i == 0)
                minus_type = true;
            else if(tokens[tokens.size()-1].type == OPERATOR)
                minus_type = true;

            if(minus_type){
                t.type = NEGATION;
                t.data = "-";
                tokens.push_back(t);
            }
            else{
                t.type = OPERATOR;
                t.data = "-";
                tokens.push_back(t);
            }
        }
        else if(eq[i] == '*'){
            t.type = OPERATOR;
            t.data = '*';
            tokens.push_back(t);
        }
        else if(eq[i] == '/'){
            t.type = OPERATOR;
            t.data = '/';
            tokens.push_back(t);
        }
        else if(eq[i] >= '0' && eq[i] <= '9'){
            //now we have to build a number from the largest consecutive sequences of digits
            string number = "";
            while(i < (int)eq.length()){
                if(eq[i] >= '0' && eq[i] <= '9')
                    number += eq[i];
                else{
                    //we found a sign that should not be in number
                    i--; //in for loop we increment i. we want to start from current sign to create his token
                    break;
                }
                i++; //go to next char
            }

            if(!tokens.empty() && tokens[tokens.size()-1].type == NEGATION){
                tokens[tokens.size()-1].type = OPERAND; //we merged negation with number to get negated number
                tokens[tokens.size()-1].data += number;
            }
            else{
                t.type = OPERAND;
                t.data = number;
                tokens.push_back(t);
            }
        }
        else if(eq[i] == ' ')
            continue;
        else{
            cout<<"Invalid equasion!\n";
            break;
        }
    }

    for(int i = 0; i < tokens.size(); i++)
        cout<<tokens[i].data<<"\n";
}
void parse_equasion(){
    bool expected = false; //at the begining we expect token to be a number
    for(int i = 0; i < tokens.size(); i++){
        if(!expected){
            if(tokens[i].type == OPERAND)
                expected = true;
            else{
                cout<<"Parsing error 1!";
                return;
            }
        }
        else{
            if(tokens[i].type == OPERATOR)
                expected = false;
            else{
                cout<<"Parsing error 1!";
                return;
            }
        }
    }
}

void solve(string eq){
    make_tokens(eq);
}

int main(){
    //main loop of the program
    while(true){
        string equasion = "";
        getline(cin, equasion);

        solve(equasion);
    }

    return 0;
}
