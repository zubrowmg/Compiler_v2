#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <string.h>

using namespace std;

#include "WrapperPass2.h"
#include "Structures.h"
#include "SymbolTable.h"

WrapperPass2::WrapperPass2(){
	prev_program = false, prev_ident = false, prev_is = false, prev_global = false, prev_integer = false, prev_procedure = false, prev_begin = false, prev_end = false, prev_semicolon = false;
	prev_char = false, prev_string = false, prev_bool = false, prev_float = false; prev2_program = false, prev2_end = false, print_flag_flow = false, prev2_procedure = false, prev2_global = false;
	prev2_char = false, prev2_string = false, prev2_bool = false, prev2_float = false, prev2_integer = false, prev3_global = false, new_global_integer = false, left_recorded = false;
	new_global_float = false, new_global_string = false, new_global_char = false, new_global_bool = false, new_integer = false, new_float = false, new_string = false, new_char = false, new_bool = false;
	new_tok_left = 0, new_tok_right = 0;
	current_procedure.push("global");
}

void WrapperPass2::recieveToken(Token tok){
	/*------------------------------------------  
	Symbol Table Functionality
	------------------------------------------*/	
	if (tok.type == "T_IDENTIFIER"){ new_tok_ident = tok; }

	// Variable Declaration
	// 
	if (current_part_of_program == "global_declare" || current_part_of_program == "procedure_declare"){
		addGlobalToSymbolTable(tok);
		
	}


	// Procedure stuff
	// 
	// Adding a new Procedure
	if (prev_procedure && tok.type == "T_IDENTIFIER"){
		sym.addNewProc(tok);
	} 
	// Scope out of a Procedure
	else if (current_part_of_program == "procedure_end" && tok.type == "T_SEMICOLON"){
		sym.scopeOut();
	}






	/*------------------------------------------  
	Print Functionality
	------------------------------------------*/
	if (print_flag_flow){ cout << current_part_of_program << " | " <<  current_procedure.top() << setw(15) << tok.type << endl;} 
	setFlags(tok);
}

void WrapperPass2::addGlobalToSymbolTable(Token tok){
	// Integer
	if (prev_global && tok.type == "T_INTEGER" || (tok.type == "T_INTEGER" && current_part_of_program == "global_declare")){
		new_global_integer = true;
	} else if (tok.type == "T_INTEGER" && current_part_of_program == "procedure_declare"){
		new_integer = true;
	} else if ((new_global_integer || new_integer) && tok.type == "T_IDENTIFIER"){
		new_tok_val_type = "V_Integer";
	} else if ((new_global_integer || new_integer) && tok.type == "T_NUMBERVAL") {
		if (left_recorded){
			if (prev_minus){
				new_tok_right = 0 - stoi(tok.actual_value);
			} else {
				new_tok_right = stoi(tok.actual_value);
			}
		} else {
			left_recorded = true;
			if (prev_minus){
				new_tok_left = 0 - stoi(tok.actual_value);
			} else {
				new_tok_left = stoi(tok.actual_value);
			}
		}
	} 
	// Float
	else if (prev_global && tok.type == "T_FLOAT" || (tok.type == "T_FLOAT" && current_part_of_program == "global_declare")){
		new_global_float = true;
	} else if (tok.type == "T_FLOAT" && current_part_of_program == "procedure_declare"){
		new_float = true;
	} else if ((new_global_float || new_float) && tok.type == "T_IDENTIFIER"){
		new_tok_val_type = "V_Float";
	} else if ((new_global_float || new_float) && tok.type == "T_NUMBERVAL") {
		if (left_recorded){
			if (prev_minus){
				new_tok_right = 0 - stoi(tok.actual_value);
			} else {
				new_tok_right = stoi(tok.actual_value);
			}
		} else {
			left_recorded = true;
			if (prev_minus){
				new_tok_left = 0 - stoi(tok.actual_value);
			} else {
				new_tok_left = stoi(tok.actual_value);
			}
		}
	}
	// Char
	else if (prev_global && tok.type == "T_CHAR" || (tok.type == "T_CHAR" && current_part_of_program == "global_declare")){
		new_global_char = true;
	} else if (tok.type == "T_CHAR" && current_part_of_program == "procedure_declare"){
		new_char = true;
	} else if ((new_global_char || new_char) && tok.type == "T_IDENTIFIER"){
		new_tok_val_type = "V_Char";
	} else if ((new_global_char || new_char) && tok.type == "T_NUMBERVAL") {
		if (left_recorded){
			if (prev_minus){
				new_tok_right = 0 - stoi(tok.actual_value);
			} else {
				new_tok_right = stoi(tok.actual_value);
			}
		} else {
			left_recorded = true;
			if (prev_minus){
				new_tok_left = 0 - stoi(tok.actual_value);
			} else {
				new_tok_left = stoi(tok.actual_value);
			}
		}
	}
	// Bool
	else if (prev_global && tok.type == "T_BOOL" || (tok.type == "T_BOOL" && current_part_of_program == "global_declare")){
		new_global_bool = true;
	} else if (tok.type == "T_BOOL" && current_part_of_program == "procedure_declare"){
		new_bool = true;
	} else if ((new_global_bool || new_bool) && tok.type == "T_IDENTIFIER"){
		new_tok_val_type = "V_Bool";
	} else if ((new_global_bool || new_bool) && tok.type == "T_NUMBERVAL") {
		if (left_recorded){
			if (prev_minus){
				new_tok_right = 0 - stoi(tok.actual_value);
			} else {
				new_tok_right = stoi(tok.actual_value);
			}
		} else {
			left_recorded = true;
			if (prev_minus){
				new_tok_left = 0 - stoi(tok.actual_value);
			} else {
				new_tok_left = stoi(tok.actual_value);
			}
		}
	}
	else if ((new_global_integer || new_global_float || new_global_string || new_global_char || new_global_bool) && tok.type == "T_SEMICOLON"){
		sym.addIdentVariable(new_tok_ident, new_tok_val_type, true, new_tok_left, new_tok_right);
		new_global_integer = false; new_global_float = false; new_global_string = false; new_global_char = false; new_global_bool = false;
		left_recorded = false;
		new_tok_right = 0; new_tok_left = 0;
	} else if ((new_integer || new_float || new_string || new_char || new_bool) && tok.type == "T_SEMICOLON"){
		sym.addIdentVariable(new_tok_ident, new_tok_val_type, false, new_tok_left, new_tok_right);
		new_integer = false; new_float = false; new_string = false; new_char = false; new_bool = false;
		left_recorded = false;
		new_tok_right = 0; new_tok_left = 0;
	}
}

void WrapperPass2::printSymbolTable(){sym.print();}
void WrapperPass2::print(){print_flag_flow = true;}
void WrapperPass2::setFlags(Token tok){

	//current_part_of_program
	if (current_part_of_program == "global_declare" && tok.type == "T_BEGIN"){current_part_of_program = "global_body";}										// Into Global Body
	if (current_part_of_program == "procedure_end" && prev2_end && prev_procedure && tok.type == "T_SEMICOLON"){											// Into Global or Procedure Declare
		current_procedure.pop();
		if (current_procedure.top() != "global"){
			current_part_of_program = "procedure_declare";
		} else {
			current_part_of_program = "global_declare";
		}
	}

	if (current_part_of_program == "procedure_body" && prev_end && tok.type == "T_PROCEDURE"){current_part_of_program = "procedure_end";}					// Into Proc End

	if (current_part_of_program == "procedure_declare" && tok.type == "T_BEGIN"){current_part_of_program = "procedure_body";}								// Into Proc Body
	if (current_part_of_program == "procedure_parameters" && tok.type == "T_RPARANTH"){current_part_of_program = "procedure_declare";}						// Into Proc Declare
	
	

	if (prev_procedure && tok.type == "T_IDENTIFIER" 
	&& (current_part_of_program == "global_declare" || current_part_of_program == "procedure_declare")){
		current_procedure.push(tok.actual_value);
	}

	if (prev2_procedure && prev_ident && tok.type == "T_LPARANTH" 
	&& (current_part_of_program == "global_declare" || current_part_of_program == "procedure_declare")){
		current_part_of_program = "procedure_parameters";
	}
																																							// Into Proc Parameters
	if (prev2_program && prev_ident && tok.type == "T_IS"){current_part_of_program = "global_declare"; }					// Into Global Declare

	if (prev2_global){prev3_global = true;} else {prev3_global = false;}

	if (prev_global){prev2_global = true;} else {prev2_global = false;}
	if (prev_end){prev2_end = true;} else {prev2_end = false;}
	if (prev_program){prev2_program = true;} else {prev2_program = false;}
	if (prev_procedure){prev2_procedure = true;} else {prev2_procedure = false;}
	if (prev_integer){prev2_integer = true;} else {prev2_integer = false;}
	if (prev_char){prev2_char = true;} else {prev2_char = false;}
	if (prev_float){prev2_float = true;} else {prev2_float = false;}
	if (prev_bool){prev2_bool = true;} else {prev2_bool = false;}
	if (prev_string){prev2_string = true;} else {prev2_string = false;}

	if (tok.type == "T_MINUS"){prev_minus = true;} else {prev_minus = false;}
	if (tok.type == "T_PROGRAM"){prev_program = true;} else {prev_program = false;}
	if (tok.type == "T_IDENTIFIER"){prev_ident = true; prev_ident_tok = tok;} else {prev_ident = false;}
	if (tok.type == "T_IS"){prev_is = true;} else {prev_is = false;}
	if (tok.type == "T_GLOBAL"){prev_global = true;} else {prev_global = false;}
	if (tok.type == "T_INTEGER"){prev_integer = true;} else {prev_integer = false;}
	if (tok.type == "T_CHAR"){prev_char = true;} else {prev_char = false;}
	if (tok.type == "T_STRING"){prev_string = true;} else {prev_string = false;}
	if (tok.type == "T_BOOL"){prev_bool = true;} else {prev_bool = false;}
	if (tok.type == "T_FLOAT"){prev_float = true;} else {prev_float = false;}
	if (tok.type == "T_PROCEDURE"){prev_procedure = true;} else {prev_procedure = false;}
	if (tok.type == "T_BEGIN"){prev_begin = true;} else {prev_begin = false;}
	if (tok.type == "T_END"){prev_end = true;} else {prev_end = false;}
}