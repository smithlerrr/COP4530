#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Stack.h"

using namespace std;
using namespace cop4530;


bool CheckOperands(const vector<string>&);
bool Valid(const vector<string>&);
void In2Post(const vector<string>&, Stack<string>&);
bool VariableCheck(Stack<string>);
float Evaluate(Stack<string> &s);
float Calculate(string, float, float);

int main(void)
{
    Stack<string> post;
    string input;
    
    cout << "Enter infix expression (\"exit\" to quit): \n"; 
    while(getline(cin,input))
    {
        if (input == "exit") 
            break;
        
        vector<string> str;
        stringstream in(input);
        string temp;

        while(in >> temp)
            str.push_back(temp);

        if (CheckOperands(str) == false)
            cout << "Error: Mismatched Parenthesis\n";
        
        else if( Valid(str) == false )
            cout << "Error: Missing operand\n";
        
        else 
        {
            In2Post(str, post);
            cout << "Postfix expression: "<< post << endl;
            cout << "Postfix evaluation: " << post << " = ";
            if (VariableCheck(post) == false)
                cout << post << endl;
            else
                cout << Evaluate(post) << endl;

            post.clear();
        
        }

        cout << "Enter infix expression (\"exit\" to quit): \n";
    }
    return 1;
}

bool CheckOperands(const vector<string> &s)
{
    Stack<string> temp;
    
    for (size_t i=0; i< s.size(); ++i)
    {
        if (s[i] == "(" || s[i] == "[")
            temp.push(s[i]);
        else if (s[i] == ")")
        {
            if (temp.top() != "(")
                return false;
            else 
                temp.pop();
        }
        else if (s[i] == "]")
        {
            if (temp.top() != "[")
                return false;
            else
                temp.pop();
        }
    }

    if (temp.empty())
        return true;
    else
        return false;

}

bool Valid(const vector<string> &s)
{
    int operators = 0;
    int operands = 0;

    for (size_t i = 0; i < s.size(); ++i)
    {
        if (s[i] == "+" || s[i] == "-" ||
            s[i] == "*" || s[i] == "/")
            ++operators;
        else if (s[i] == "[" || s[i] == "]" ||
                 s[i] == "(" || s[i] == ")")
           continue; 
        else
            ++operands;
    }
    if ((operators == 0 && operands == 0) || (operators == (operands - 1))) 
        return true;
    else 
        return false;
}

void In2Post(const vector<string> &s1, Stack<string> &s2)
{
    Stack<string> operands;
    for (size_t i = 0; i < s1.size(); ++i)
    {
        if (s1[i] == "+" || s1[i] == "-")
        {
            while ((!operands.empty() &&  operands.top() != "(") && 
                    (operands.top() != "*" || operands.top() != "/"))
            {
                s2.push(operands.top());
                operands.pop();
            }
            operands.push(s1[i]);
        }   
        
        else if (s1[i] == "*" || s1[i] == "/")
        {
            while (!operands.empty() && operands.top() != "(" && 
                      (operands.top() != "-" && operands.top() != "+"))
            {
                s2.push(operands.top());
                operands.pop(); 
            }
            operands.push(s1[i]);
        }
        
        else if (s1[i] == "(")
        {
            operands.push(s1[i]);
        }
        
        else if (s1[i] == ")")
        {
            while (operands.top() != "(")
            {
                s2.push(operands.top());
                operands.pop();
            }
            operands.pop();
        }
        
        else
            s2.push(s1[i]);
    }
    while (operands.empty() == false)
    {
        s2.push(operands.top());
        operands.pop();
    }
}

bool VariableCheck(Stack<string> s)
{
    while (!s.empty())
    {
        stringstream in;
        float f;
        in << s.top();

        if (s.top() == "+" || s.top() == "-" || s.top() == "*" || s.top() == "/")
        {}
        else if (!(in >> f))
            return false;   
        s.pop();
    }
    return true;
}

float Evaluate(Stack<string> &s)
{
    stringstream in;
    Stack<string> str;
    string temp;

    s.print(in, ' ');

    while (in >> temp)
    {
        if (temp == "+" || temp == "-" || temp == "*" || temp == "/")
        {
            float rhs = stof( str.top() );
            str.pop();
            float lhs = stof( str.top() );
            str.pop();        
            stringstream result;
            result << Calculate(temp, lhs, rhs);
            string str2;
            result >> str2;
            str.push(str2); 
        }
        else
            str.push(temp);
    }
    return stof(str.top());
}

float Calculate(string op, float lhs, float rhs)
{
    if (op == "+")
        return lhs + rhs;
    else if (op == "-")
        return lhs - rhs;
    else if (op == "*")
        return lhs * rhs;
    else
        return lhs / rhs;
}
