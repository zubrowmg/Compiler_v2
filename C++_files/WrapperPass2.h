#ifndef WRAPPERPASS2_H
#define WRAPPERPASS2_H

#include <stack>
#include <string>
#include <string.h>

using namespace std;

#include "Structures.h"
<<<<<<< HEAD

class WrapperPass2{
	private:
    	bool prev_program, prev_ident, prev_is, prev_global, prev_integer, prev_procedure, prev_begin, prev_end, prev_semicolon;
        bool prev_char, prev_string, prev_bool, prev_float, prev2_program, prev2_end, print_flag_flow, prev2_procedure;
        string current_part_of_program;
=======
#include "SymbolTable.h"

class WrapperPass2{
	private:
        Token new_tok_ident;
        SymbolTable sym;
        int new_tok_left, new_tok_right;
    	bool prev_program, prev_ident, prev_is, prev_global, prev_integer, prev_procedure, prev_begin, prev_end, prev_semicolon;
        bool prev_char, prev_string, prev_bool, prev_float, prev2_program, prev2_end, print_flag_flow, prev2_procedure, prev2_global;
        bool prev2_char, prev2_string, prev2_bool, prev2_float, prev2_integer, prev3_global, new_global_integer, prev_minus, left_recorded;
        bool new_global_float, new_global_string, new_global_char, new_global_bool, new_integer, new_float, new_string, new_char, new_bool;
        string current_part_of_program, new_tok_val_type;
>>>>>>> symbol_table
        stack <string> current_procedure;
        Token prev_ident_tok;
    public:
    	WrapperPass2();
        void print();
<<<<<<< HEAD
    	void getToken(Token tok);
        void setFlags(Token tok);
=======
    	void recieveToken(Token tok);
        void setFlags(Token tok);

        void printSymbolTable();
        void addGlobalToSymbolTable(Token tok);
>>>>>>> symbol_table
};

#endif