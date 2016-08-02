//Drew Smith          //
//COP4530             //
//Project 4           //
//November 11, 2015   //
////////////////////////

#include <iostream>
#include <sstream>
#include <cctype>
#include <stack>
#include <vector>
#include <string>
using namespace std;

//Default zero-parameter constructor
BET::BET():root{nullptr}{}

//One-parameter constructor, where parameter "postfix" is string containing a postfix expression
BET::BET(const string postfix):root{nullptr}
{
  buildFromPostfix(postfix);
}

//Copy constructor
BET::BET(const BET& c):root{nullptr}
{
  root = clone(c.root);
}

//Destructor
BET::~BET()
{
  makeEmpty(root);
}

/*The parameter "postfix" is string containing a postfix expression. The tree should
 be built based on the postfix expression. Tokens in the postfix expression are 
 separated by space. If the tree contains nodes before the function is called, 
 you need to first delete the existing nodes. Return true if the new tree is built 
 successfully. Return false if an error is encountered.*/
bool BET::buildFromPostfix(const string postfix)
{
  stack<BET::BinaryNode*> stack;
  istringstream inputstream(postfix);
  vector<string> vec;
  string input;
  int operators = 0, operands = 0;
 
  while(inputstream >> input)
  {
      vec.push_back(input);
      if(isalnum(input[0]))
        ++operands;
      
      else
        ++operators;
  }
  int finalop = operators + 1;
  if((operands != finalop) || ((vec.size() > 1) && ((!isalnum(vec[0][0]))||
    (isalnum(vec[vec.size() - 1][0])))))
  {
    cout<<"Error: Could not create tree.\n";
    return false;
  }

  for(size_t i = 0; i < vec.size(); ++i)
  {
    BinaryNode *temp = new BinaryNode();
    temp->data = vec[i];
    
    if(isalnum(temp->data[0]))
      stack.push(temp);
      
    else 
    {
      temp->right = stack.top();
      stack.pop();
      temp->left = stack.top();
      stack.pop();
      stack.push(temp);      
    }   
  }

  root = stack.top();
  return true;
}

//Assignment operator
const BET& BET::operator=(const BET &rhs)
{
  root = rhs.clone(rhs.root);
  return *this;
}

//Call the private version of the printInfixExpression function to print out the infix expression
void BET::printInfixExpression()
{
  printInfixExpression(root);
  cout << endl; 
}

//Call the private version of the printPostfixExpression function to print out the postfix expression
void BET::printPostfixExpression()
{
  printPostfixExpression(root);
  cout << endl;
}

//Call the  private version of the size function to return the number of nodes in the tree
size_t BET::size()
{
  return size(root);
}

//Call the private version of the leaf_nodes function to return the number of leaf nodes in the tree
size_t BET::leaf_nodes()
{
  return leaf_nodes(root);
}

//Return true if the tree is empty. Return false otherwise
bool BET::empty()
{
  return (root == nullptr);
}

/*Print to the standard output the corresponding infix expression. Note that you may need to add 
parentheses depending on the precedence of operators. You should not have unnecessary parentheses */
void BET::printInfixExpression(BinaryNode *n)
{
  if(isalnum(n->data[0])) //if 1 node
    cout << n->data << " ";
  else
  {
    if(isalnum(n->left->data[0])) //left side
      printInfixExpression(n->left);

    else if((!isalnum(n->left->data[0])) && ((((n->left->data == "-") || 
      (n->left->data == "+")) && ((n->data == "*") || (n->data== "/") || 
      (n->data == "-") || (n->data == "+"))) || (((n->left->data == "*")||
      (n->left->data == "/")) && ((n->data == "*") || (n->data == "/")))))
	    {
        cout << "(";
        printInfixExpression(n->left);
        cout << ")";
      }

    else
      printInfixExpression(n->left);

    cout << n->data << " ";

    if(isalnum(n->right->data[0]))  //right side
      cout << n->right->data << " ";
    
    else
    {
      if(isalnum(n->right->data[0]))
        printInfixExpression(n->right);

      else if((!isalnum(n->right->data[0])) && ((((n->right->data == "-")||
        (n->right->data == "+")) && ((n->data == "*") || (n->data == "/")|| 
        (n->data == "-") || (n->data == "+"))) || (((n->right->data == "*")||
        (n->right->data == "/")) && ((n->data =="*") || (n->data == "/")))))
      {
        cout << "(";
        printInfixExpression(n->right);
        cout << ")";
      }      
      else
        printInfixExpression(n->right);
    }
  }  
}

//Delete all nodes in the subtree pointed to by t. Called by functions such as the destructor.
void BET::makeEmpty(BinaryNode *&t)
{
  if(t == nullptr)
    return;
  else
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }  
}

//Clone all nodes in the subtree pointed to by t. Called by functions such as the assignment operator=.
BET::BinaryNode* BET::clone(BinaryNode *t) const
{
  if(t == nullptr)
    return nullptr;
  else
    return new BinaryNode{t->data, clone(t->left), clone(t->right)};
}

//Print to the standard output the corresponding postfix expression.
void BET::printPostfixExpression(BinaryNode *n)
{
  if(n->left == nullptr)
    cout << n->data << " ";
  else
  {
    printPostfixExpression(n->left);
    printPostfixExpression(n->right);
    cout << n->data << " ";
  }  
}

//Return the number of nodes in the subtree pointed to by t.
size_t BET::size(BinaryNode *t)
{
  if(t->left == nullptr)
    return 1;
  else
    return size(t->left) + size(t->right) + 1;
}

//Return the number of leaf nodes in the subtree pointed to by t.
size_t BET::leaf_nodes(BinaryNode *t)
{
  if(t->left == nullptr)
    return 1;
  else
    return leaf_nodes(t->left) + leaf_nodes(t->right);
}
