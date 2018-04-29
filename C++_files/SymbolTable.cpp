#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <stdio.h>
#include <iterator>

#include "Structures.h"
#include "SymbolTable.h"


using namespace std;

SymbolTable::SymbolTable(){
	// Set up the global table
	SymbolNode *temp = new SymbolNode;
	global = temp;
	global->ident_name = "global";
	global->is_proc = true;

	pos = global;
	print_spacing = 20;
}

void SymbolTable::addNewProc(Token tok){
	SymbolNode *new_proc = new SymbolNode;

	new_proc->is_proc = true;
	new_proc->scope_out = pos;
	new_proc->ident_name = tok.actual_value;

	(pos->proc_table)[tok.actual_value] = new_proc;

 //cout << "+++++++++  " << pos->ident_name << "  " << new_proc->ident_name << endl;

	pos = new_proc;

}

void SymbolTable::addIdentVariable(Token tok, string variable_type, bool global_variable){
	SymbolNode new_ident_variable; 

	new_ident_variable.ident_name = tok.actual_value;
	new_ident_variable.ident_variable_type = variable_type;

	if (global_variable){
		(global->table)[tok.actual_value] = new_ident_variable;								// Add in global table
	} else {
		(pos->table)[tok.actual_value] = new_ident_variable; 								// Add in scoped table
	}
}

void SymbolTable::print(){
	map<string, SymbolNode> :: iterator itr;
	
	pos = global;

	cout << "========================================" << endl;
	cout << "              Symbol Table              " << endl;
	cout << "========================================" << endl;
	cout << "Table Name: " << pos->ident_name << endl;

	for (itr = (pos->table).begin(); itr != (pos->table).end(); ++itr){	
		if (itr->second.is_proc == false){
			cout << setw(10) << itr->second.ident_name << setw(10) << " | ";
				if (!itr->second.is_array){
					cout << "Not Array";
				} else {
					cout << " Is Array";
				}
			cout << "\t" << "[" << itr->second.array_left << ":" << itr->second.array_right << "]" << setw(15) << "Size: " << itr->second.array_size << setw(20) << itr->second.ident_variable_type << endl;
		}
	}

	printScopeIn();

}

void SymbolTable::scopeOut(){
	pos = pos->scope_out;
}

void SymbolTable::printScopeIn(){
	map<string, SymbolNode*> :: iterator itr;
	map<string, SymbolNode> :: iterator itr2;

	SymbolNode *temp_pos;

	for (itr = (pos->proc_table).begin(); itr != (pos->proc_table).end(); ++itr){	
		cout << setw(print_spacing) << "---------------------------" << endl;
		cout << setw(print_spacing) << "Table Name: " << (itr->second)->ident_name << setw(print_spacing) << "Inside of: " << setw(print_spacing - 10) << pos->ident_name << endl;

		pos = itr->second;

		for (itr2 = (pos->table).begin(); itr2 != (pos->table).end(); ++itr2){	
			if (itr2->second.is_proc == false){
				cout << setw(print_spacing + 10) << itr2->second.ident_name << setw(print_spacing - 15) << " | ";
					if (!itr2->second.is_array){
						cout << "Not Array";
					} else {
						cout << " Is Array";
					}
				cout << "\t" << "[" << itr2->second.array_left << ":" << itr2->second.array_right << "]" << setw(print_spacing - 5) << "Size: " << itr2->second.array_size << setw(print_spacing - 5) << itr2->second.ident_variable_type << endl;
			}
		}

		printScopeIn();

		pos = (itr->second)->scope_out;
		//temp_pos = itr->second;
	}
}