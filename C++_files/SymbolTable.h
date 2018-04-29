#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <stack>

using namespace std;


class SymbolTable{
	private:
       SymbolNode *global;
       SymbolNode *pos;
       int print_spacing;
    public:
    	SymbolTable();
    	void addNewProc(Token tok);
    	void addIdentVariable(Token tok, string variable_type, bool global_variable);
    	void scopeOut();

    	void print();
    	void printScopeIn();

};


#endif