#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <map>


using namespace std;

struct Token{
	string type;
	string actual_value; 						
 	int line_number;

    Token(){
       
    }
};


struct SymbolNode{
	string ident_name;
	bool is_proc;

	// Variable Items
	bool is_array;
	int array_left, array_right, array_size;
	string ident_variable_type;

	// Procedure Items
	map<string, SymbolNode*> proc_table;
	map<string, SymbolNode> table;
	SymbolNode *scope_in;
	SymbolNode *scope_out;

    SymbolNode(){
       is_proc = false; is_array = false; array_left = 0; array_right = 0; array_size = 1;
    }
};

#endif