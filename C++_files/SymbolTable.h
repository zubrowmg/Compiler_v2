#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <stack>

#include "Error.h"

using namespace std;


class SymbolTable{
	private:
		Error error_handler;
       	SymbolNode *global;
  	 	SymbolNode *pos;
  		int print_spacing;
    public:
    	SymbolTable();
    	void addNewProc(Token tok);
    	void addIdentVariable(Token tok, string variable_type, bool global_variable, int left, int right);
    	void scopeOut();

    	void print();
    	void printScopeIn();

};


#endif