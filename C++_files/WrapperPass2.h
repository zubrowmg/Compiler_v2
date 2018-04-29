#ifndef WRAPPERPASS2_H
#define WRAPPERPASS2_H

#include <stack>
#include <string>
#include <string.h>

using namespace std;

#include "Structures.h"
#include "SymbolTable.h"

class WrapperPass2{
	private:
        SymbolTable sym;
    	bool prev_program, prev_ident, prev_is, prev_global, prev_integer, prev_procedure, prev_begin, prev_end, prev_semicolon;
        bool prev_char, prev_string, prev_bool, prev_float, prev2_program, prev2_end, print_flag_flow, prev2_procedure, prev2_global;
        string current_part_of_program;
        stack <string> current_procedure;
        Token prev_ident_tok;
    public:
    	WrapperPass2();
        void print();
        void printSymbolTable();
    	void getToken(Token tok);
        void setFlags(Token tok);
};

#endif