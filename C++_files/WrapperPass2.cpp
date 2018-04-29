#include <fstream>
#include <iostream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <string.h>

using namespace std;

#include "WrapperPass2.h"
#include "Structures.h"

WrapperPass2::WrapperPass2(){
	prev_program = false, prev_ident = false, prev_is = false, prev_global = false, prev_integer = false, prev_procedure = false, prev_begin = false, prev_end = false, prev_semicolon = false;
	prev_char = false, prev_string = false, prev_bool = false, prev_float = false; prev2_program = false, prev2_end = false, print_flag_flow = false, prev2_procedure = false;

	current_procedure.push("global");
}

void WrapperPass2::getToken(Token tok){

	/*------------------------------------------  
	Print Functionality
	------------------------------------------*/
	if (print_flag_flow){ cout << current_part_of_program << " | " <<  current_procedure.top() << setw(15) << tok.type << endl;} 
	setFlags(tok);
}

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

	if (prev_end){prev2_end = true;} else {prev2_end = false;}
	if (prev_program){prev2_program = true;} else {prev2_program = false;}
	if (prev_procedure){prev2_procedure = true;} else {prev2_procedure = false;}

	if (tok.type == "T_PROGRAM"){prev_program = true;} else {prev_program = false;}
	if (tok.type == "T_IDENTIFIER"){prev_ident = true; prev_ident_tok = tok;} else {prev_ident = false;}
	if (tok.type == "T_IS"){prev_is = true;} else {prev_is = false;}
	if (tok.type == "T_GLOBAL"){prev_is = true;} else {prev_is = false;}
	if (tok.type == "T_INTEGER"){prev_integer = true;} else {prev_integer = false;}
	if (tok.type == "T_CHAR"){prev_char = true;} else {prev_char = false;}
	if (tok.type == "T_STRING"){prev_string = true;} else {prev_string = false;}
	if (tok.type == "T_BOOL"){prev_bool = true;} else {prev_bool = false;}
	if (tok.type == "T_FLOAT"){prev_float = true;} else {prev_float = false;}
	if (tok.type == "T_PROCEDURE"){prev_procedure = true;} else {prev_procedure = false;}
	if (tok.type == "T_BEGIN"){prev_begin = true;} else {prev_begin = false;}
	if (tok.type == "T_END"){prev_end = true;} else {prev_end = false;}
}