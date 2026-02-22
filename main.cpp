#include <bits/stdc++.h>

#define OPERATOR        1
#define OPERAND         2
#define NEGATION        3
#define LEFT_PARENTH    4
#define RIGHT_PARENTH   5

#define PRIORITY_LEVEL0     0
#define PRIORITY_LEVEL1     1
#define PRIORITY_LEVEL2     2

using namespace std;

struct token{
    int type; //number, operator or negation
    int priority; //only for operators
    string data;
};
vector <token> tokens;

bool make_tokens(string eq){
    tokens.clear(); //get ready for new equasion

    for(int i = 0; i < (int)eq.length(); i++){
        token t;

        if(eq[i] == '+'){
            t.type = OPERATOR;
            t.priority = PRIORITY_LEVEL1;
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
                t.priority = PRIORITY_LEVEL1;
                t.data = "-";
                tokens.push_back(t);
            }
        }
        else if(eq[i] == '*'){
            t.type = OPERATOR;
            t.priority = PRIORITY_LEVEL2;
            t.data = "*";
            tokens.push_back(t);
        }
        else if(eq[i] == '/'){
            t.type = OPERATOR;
            t.priority = PRIORITY_LEVEL2;
            t.data = "/";
            tokens.push_back(t);
        }
        else if(eq[i] == '('){
            t.type = LEFT_PARENTH;
            t.priority = PRIORITY_LEVEL0;
            t.data = "(";
            tokens.push_back(t);
        }
        else if(eq[i] == ')'){
            t.type = RIGHT_PARENTH;
            t.priority = PRIORITY_LEVEL0;
            t.data = ")";
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
                tokens[tokens.size()-1].priority = PRIORITY_LEVEL0;
                tokens[tokens.size()-1].data += number;
            }
            else{
                t.type = OPERAND;
                t.priority = PRIORITY_LEVEL0;
                t.data = number;
                tokens.push_back(t);
            }
        }
        else if(eq[i] == ' ')
            continue;
        else{
            cout<<"Invalid equasion!\n";
            return false;
        }
    }

    if(tokens.empty()){
        cout<<"Empty equasion!\n";
        return false;
    }
    if(tokens[tokens.size()-1].type == OPERATOR || tokens[tokens.size()-1].type == LEFT_PARENTH){ //if last token in equasion is operator np. 5+, 5*3/
        cout<<"Invalid equasion!\n";
        return false;
    }

    /*for(int i = 0; i < tokens.size(); i++)
        cout<<tokens[i].data<<"\n";*/
    return true;
}
bool parse_equasion(){
    bool expected = false; //at the begining we expect token to be a number or '(' (false), after that we can get operator or ')' (true)
    int parenth_diff = 0; //store the differences of the number of left and right parenthesis 
    
    for(int i = 0; i < tokens.size(); i++){
        if(tokens[i].type == LEFT_PARENTH){
            if(expected){ //handle ex. 1234(32 - 1)
                cout<<"Expect number or '('!\n";
                return false;
            }
            parenth_diff++;
        }
        else if(tokens[i].type == RIGHT_PARENTH){
            if(!expected){//handle ex. 123 - (1234)
                cout<<"Unexpected ')'!\n";
                return false;
            }

            parenth_diff--;
            if(parenth_diff < 0){ //handle ex. ((1234 - 23 + 1 *2)))
                cout<<"Unmatched closing parenthesis!\n";
                return false;
            }
        }
        else if(tokens[i].type == OPERATOR){
            if(!expected){
                cout<<"Unexpected operator\n";
                return false;
            }

            expected = false; //now we expect number or '('
        }
        else if(tokens[i].type == OPERAND){
            if(expected){
                cout<<"Expect operator beetwen operands!\n";
                return false;
            }

            expected = true; //now we expect operator or ')'
        }
    }

    if(parenth_diff != 0){//handle ex. ((1234 - 23 + 1 *2))) or ((1234 - (23 + 1)*2)
        cout<<"Unclosed/unmatched parenthesis!\n";
        return false;
    }

    return true;
}
vector<token> change_to_ONP(){
    vector <token> res;
    vector <token> stack;

    for(int i = 0; i < tokens.size(); i++){
        if(tokens[i].type == OPERATOR){
            if(stack.empty())
                stack.push_back(tokens[i]); //stack is empty we can just put an element there
            else if(stack[stack.size()-1].priority < tokens[i].priority)
                stack.push_back(tokens[i]); //last operator has lower priority so we have to execute current token first
            else{
                //there are some operators with greater priority. We have to pop them and then put current operator
                while(!stack.empty()){
                    if(stack[stack.size()-1].priority >= tokens[i].priority){
                        res.push_back(stack[stack.size()-1]);
                        stack.pop_back();
                    }
                    else 
                        break;
                }
                stack.push_back(tokens[i]);
            }
        }
        else if(tokens[i].type == LEFT_PARENTH)
            stack.push_back(tokens[i]);
        else if(tokens[i].type == RIGHT_PARENTH){
            while(stack[stack.size()-1].data != "("){
                res.push_back(stack[stack.size()-1]);
                stack.pop_back();
            }
            stack.pop_back(); //we also have to pop "("
        }
        else
            res.push_back(tokens[i]);
    }

    //if some operators left on the stack - add them to result
    for(int i = stack.size()-1; i >= 0; i--){
        res.push_back(stack[i]);
        stack.pop_back();
    }
    return res;
}
void calculate_ONP(vector <token> ONP){
    vector<double> stack;
    for(int i = 0; i < ONP.size(); i++){
        if(ONP[i].type == OPERATOR){
            double a, b;

            b = stack[stack.size()-1];
            stack.pop_back();
            a = stack[stack.size()-1];
            stack.pop_back();

            if(ONP[i].data == "+")
                stack.push_back(a + b);
            else if(ONP[i].data == "-")
                stack.push_back(a - b);
            else if(ONP[i].data == "*")
                stack.push_back(a * b);
            else if(ONP[i].data == "/"){
                if(b == 0){
                    cout<<"You can't divide by 0!\n";
                    return;
                }
                stack.push_back(a / b);
            }
        }
        else
            stack.push_back(stof(ONP[i].data));
    }

    cout<<stack[stack.size()-1]<<"\n";
}
void solve(string eq){
    if(!make_tokens(eq))
        return;
    if(!parse_equasion())
        return;
    
    vector <token> ONP;
    ONP = change_to_ONP();
    /*cout<<"\n";
    for(int i = 0; i < ONP.size(); i++){
        cout<<ONP[i].data<<"\n";
    }*/
    calculate_ONP(ONP);
}
int main(){
    //main loop of the program
    while(true){
        string equasion = "";
        cout<<"Enter equasion: ";
        getline(cin, equasion);

        solve(equasion);
    }
    return 0;
}
