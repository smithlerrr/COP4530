//Drew Smith          //
//COP4530             //
//Project 4           //
//November 11, 2015   //
////////////////////////

#ifndef BET_H
#define BET_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class BET
{
	private:
		struct BinaryNode
		{
      		string data;
			BinaryNode *left;
			BinaryNode *right;
 			BinaryNode(const std::string & d = std::string{}, BinaryNode *p = nullptr, BinaryNode *n = nullptr)
            		: data{d}, left{p}, right{n} {}
 			BinaryNode(std::string && d, BinaryNode *p = nullptr, BinaryNode *n = nullptr)
            		: data{move(d)}, left{p}, right{n} {}
		};

	public:
		BET();
		BET(const string postfix);
		BET(const BET&);
		~BET();
		bool buildFromPostfix(const string postfix);
		const BET& operator=(const BET&);
		void printInfixExpression();
		void printPostfixExpression();
		size_t size();
		size_t leaf_nodes();
		bool empty();
	
	private:
		void printInfixExpression(BinaryNode *n);
		void makeEmpty(BinaryNode* &t);
		BinaryNode *clone(BinaryNode *t) const;
		void printPostfixExpression(BinaryNode *n);
		size_t size(BinaryNode *t);
		size_t leaf_nodes(BinaryNode *t);
		BinaryNode *root;          
};
#include "bet.hpp"
#endif
