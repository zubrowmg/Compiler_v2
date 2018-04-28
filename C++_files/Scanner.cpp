#include <fstream>
#include <iostream>
//#include <cstdlib>
#include <string>
#include <string.h>
//#include <vector> 
#include <stdio.h>

#include "Structures.h"
#include "Scanner.h"
#include "Error.h"

using namespace std;

int isLetter(char c){
	if (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h' || c == 'i' || c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'o' || c == 'p' || c == 'q' || c == 'r' || c == 's' || c == 't' || c == 'u' || c == 'v' || c == 'w' || c == 'x' || c == 'y' || c == 'z'
		|| c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F' || c == 'G' || c == 'H' || c == 'I' || c == 'J' || c == 'K' || c == 'L' || c == 'M' || c == 'N' || c == 'O' || c == 'P' || c == 'Q' || c == 'R' || c == 'S' || c == 'T' || c == 'U' || c == 'V' || c == 'W' || c == 'X' || c == 'Y' || c == 'Z'){
		return 1;
	} else {
		return 0;
	}
}

bool isNum(char c){
	if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9'){
		return true;
	} else {
		return false;
	}
}

Token clearToken(Token input){
	input.actual_value = "";
	input.type = "";
	return input;
}

bool reservedWordChecker(Token token, string str){
	bool match = false; 

	if (str.length() == (token.actual_value).length()){
		match = true;		
	}
 
	if (match){
		for (int i = 0; i < str.length(); i++){ 
			if (str[i] == (token.actual_value)[i]){
				match = true;
			} else {
				match = false;
				return match;
			}
		}
	}
	return match;
}

/*------------------------------------------  
	Reads File and Stores Tokens in a Vector 
------------------------------------------*/
void Scanner::scanInit(char *argv[]){
	ifstream inFile;
	bool nest_comment = false, number_checker = false, skip = false, record_token = false, grab_prev_c = false, ident_checker = false, leave_while = false;
	char c; 
	int peeker = 0, j = 0, line_counter = 0, char_length = 0, num_of_comments = 0;
	Token tok;

	inFile.open(argv[1]);

	if (!inFile) {
 	  	cout << "Unable to open file txt" << endl;
    	exit(1);   											
	}

	while (inFile.get(c)){
		/*---------------------------------------------------------  
		There are times where we need to reread a prevoius char
		---------------------------------------------------------*/
		if (grab_prev_c){
			inFile.seekg(-2, inFile.cur);  		// -2 because we want to read the previous char, -1 will move the position to the current char again 
			if (inFile.good()) {
			  	inFile.get(c);
			}
			grab_prev_c = false;
		}

		/*------------------  
		Number Token Section 
		------------------*/
		if (isNum(c) || c == '.'){
			if (isNum(c)){
				(tok.actual_value).insert((tok.actual_value).begin()+j, c);
				j++;
				number_checker = true;
			} else {
				(tok.actual_value).insert((tok.actual_value).begin()+j, c);
				inFile.get(c);
				j++;			
				if (isNum(c)){										
					(tok.actual_value).insert((tok.actual_value).begin()+j, c);
					j++;
					number_checker = true;
				} else {
					number_checker = false;
					tok.type = "T_PERIOD"; tok.line_number = line_counter; tok_list.push_back(tok);
					tok = clearToken(tok);
				}
			}

			/*---------------------------------------------  
				While loop will get the entire number token 
			---------------------------------------------*/
			while (number_checker){
				inFile.get(c);
				if (isNum(c)){
					(tok.actual_value).insert((tok.actual_value).begin()+j, c);									
				} else if (c == '.'){
					if (skip){
						number_checker = false;	
					}
					else{
						(tok.actual_value).insert((tok.actual_value).begin()+j, c);
						skip = true;						
					}
				} else if(c == '_'){ 
					j--;
				} else {
					number_checker = false;				
				}
				j++;
				record_token = true;					
			}
			
			/*-------------------------------------------------------------------------------  
				We only want to record the token if it was a number token, not a period token 
			-------------------------------------------------------------------------------*/
			if (record_token){
				tok.type = "T_NUMBERVAL"; tok.line_number = line_counter; tok_list.push_back(tok);
				tok = clearToken(tok);
			}


			grab_prev_c = true;	skip = false; record_token = false;
			j = 0;
		}
		/*--------------------------  
		Identifier Token Section 
		--------------------------*/
		else if (isLetter(c)){						//Checks to see if it is a letter, triggers flag and stores char
			(tok.actual_value).insert((tok.actual_value).begin()+j, c);
			j++;

			ident_checker = true;
			while (ident_checker){
				inFile.get(c); 
				if (isNum(c) || isLetter(c) || c == '_'){
					(tok.actual_value).insert((tok.actual_value).begin()+j, c);
				} else {
					ident_checker = false;
					if (c == '\n' || c == '\t' || c == ' ' || c == '['|| c == ']' || c == '(' || c == ')' || c == ';' || c == '.' || c == ','){
						
					} else {
						error_handler.error(line_counter, 5);
					}
				}
				j++;
			}
			/*------------------------  
				Reserved Token Section 
			------------------------*/
			if (reservedWordChecker(tok, "program")){tok.type = "T_PROGRAM"; tok.line_number = line_counter; tok_list.push_back(tok); }
			else if (reservedWordChecker(tok, "is")){tok.type = "T_IS"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "begin")){tok.type = "T_BEGIN"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "end")){tok.type = "T_END"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "global")){tok.type = "T_GLOBAL"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "procedure")){tok.type = "T_PROCEDURE"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "in")){tok.type = "T_IN"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "out")){tok.type = "T_OUT"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "inout")){tok.type = "T_INOUT"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "integer")){tok.type = "T_INTEGER"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "float")){tok.type = "T_FLOAT"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "bool")){tok.type = "T_BOOL"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "char")){tok.type = "T_CHAR"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "if")){tok.type = "T_IF"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "then")){tok.type = "T_THEN"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "else")){tok.type = "T_ELSE"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "for")){tok.type = "T_FOR"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "return")){tok.type = "T_RETURN"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "true")){tok.type = "T_TRUE"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "false")){tok.type = "T_FALSE"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "not")){tok.type = "T_NOT"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (reservedWordChecker(tok, "string")){tok.type = "T_STRING"; tok.line_number = line_counter; tok_list.push_back(tok);}
			
			else {
				tok.type = "T_IDENTIFIER"; tok.line_number = line_counter; tok_list.push_back(tok);
				tok = clearToken(tok);
			}
			tok = clearToken(tok);

			ident_checker = false; grab_prev_c = true;
			j = 0;
		}
		
	
		/*---------------------  
			Char Token Section 
		-----------------------*/
		else if (c == '\''){						
			char_length = 0; leave_while = false;		
			inFile.get(c);
			while (!leave_while){
				(tok.actual_value).insert((tok.actual_value).begin()+j, c);
				j++; char_length++;

				inFile.get(c);

				peeker = inFile.peek();

				if (c == '\''){					//Char ends with ' so we can leave the while loop
					leave_while = true;
				}
				else if (c == ';' || c == '_' || c == ':' || c == '.' || c == '\"' || isLetter(c) || isNum(c)){} 		//Do nothing for these accepted chars
				
				else if (peeker == EOF){		//Error for forgeting the ending '
					error_handler.error(line_counter, 3);
					break;
				} else {
					error_handler.error(line_counter, 4);		//Error for illegal chars
				}

				if (char_length > 1 && !(skip)){	//Error for char that is longer than 1
					error_handler.error(line_counter, 2);
					skip = true;
				} 
			}

			tok.type = "T_CHARVAL"; tok.line_number = line_counter; tok_list.push_back(tok);
			tok = clearToken(tok);
			skip = false; leave_while = false;
			j = 0;
		} 
		/*---------------------  
		String Token Section 
		-----------------------*/
		else if (c == '\"'){						
			leave_while = false;			
			inFile.get(c);
			while (!leave_while){
				(tok.actual_value).insert((tok.actual_value).begin()+j, c);
				j++; 

				inFile.get(c);

				peeker = inFile.peek();

				if (c == '\"'){
					leave_while = true;
				}
				else if (c == ';' || c == '_' || c == ':' || c == '.' || c == '\'' || isLetter(c) || isNum(c) || c == ' '){}
				else if (peeker == EOF){
					error_handler.error(line_counter, 3);
					break;
				} else {
					error_handler.error(line_counter, 4);
				}

				
				
			}

			tok.type = "T_STRINGVAL"; tok.line_number = line_counter; tok_list.push_back(tok);
			tok = clearToken(tok);
			leave_while = false;
			j = 0;
		}
		/*--------------------------------------------------  
		All other chars (like spaces, newlines, symbols)
		--------------------------------------------------*/

		else {										
			
			j = 0;
			
			tok = clearToken(tok);

			if (c == '\n') {line_counter++;} else if (c == '\t' || isspace(c) ){} 
			else if (c == '='){ 
				inFile.get(c); 
				if (c == '='){
					tok.type = "T_EQUALTO"; tok.actual_value = "=="; tok.line_number = line_counter; tok_list.push_back(tok);
					
				} else {
					//temp.type = "T_ASSIGN"; current_token.line = line_counter; token_list.createnode(temp);
					grab_prev_c = true;
				}	
			}
			else if (c == ':'){ 
				
				inFile.get(c); 
				if (c == '='){
					tok.type = "T_ASSIGN"; tok.actual_value = ":="; tok.line_number = line_counter; tok_list.push_back(tok);
					
				} else {
					tok.type = "T_COLON"; tok.actual_value = ":"; tok.line_number = line_counter; tok_list.push_back(tok);
					grab_prev_c = true;
				}	
			}
			else if (c == '&'){ tok.type = "T_AND"; tok.actual_value = "&"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (c == '|'){ tok.type = "T_OR"; tok.actual_value = "|"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (c == '+'){ tok.type = "T_ADD"; tok.actual_value = "+"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (c == '-'){ tok.type = "T_MINUS"; tok.actual_value = "-"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (c == '<'){ 
				inFile.get(c); 
				if (c == '='){
					tok.type = "T_LESSTHANEQUAL"; tok.actual_value = "<=";  tok.line_number = line_counter; tok_list.push_back(tok);;
				} else {
					tok.type = "T_LESSTHAN"; tok.actual_value = "<"; tok.line_number = line_counter; tok_list.push_back(tok);
					grab_prev_c = true;
				}				
			}
			else if (c == '>'){ 			
				inFile.get(c); 
				if (c == '='){
					tok.type = "T_GREATERTHANEQUAL"; tok.actual_value = ">="; tok.line_number = line_counter; tok_list.push_back(tok);
				} else {
					tok.type = "T_GREATERTHAN"; tok.actual_value = ">"; tok.line_number = line_counter; tok_list.push_back(tok);
					grab_prev_c = true;
				}			
			}
			else if (c == '!'){
				inFile.get(c);  
				if (c == '='){
					tok.type = "T_NOTEQUALTO"; tok.actual_value = "!="; tok.line_number = line_counter; tok_list.push_back(tok);
				} else {
					tok.type = "T_EXLAMANTION"; tok.actual_value = "!"; tok.line_number = line_counter; tok_list.push_back(tok);
					grab_prev_c = true;
				}
			}
			else if (c == '*'){ 
				
				inFile.get(c); 
				if (c == '/'){
					if (num_of_comments > 0){
						error_handler.error(line_counter, 29);
					} else {
						num_of_comments--;
					}
				} else {
					tok.type = "T_MULT"; tok.actual_value = "*"; tok.line_number = line_counter; tok_list.push_back(tok);
					grab_prev_c = true;
				}
			} else if (c == '/'){ 
				inFile.get(c); 
				if (c == '/'){
					inFile.get(c);
					while (c != '\n' || c == (-1)){
						inFile.get(c);
					}
					if (c == '\n'){
						line_counter++;
					}
				} else if(c == '*'){
					inFile.get(c);
					nest_comment = true;
					while (nest_comment){
						if (c == '*'){
							inFile.get(c);
							if (c == '/'){
								//if (num_of_comments > 0){
									num_of_comments--;
								//} else if (num_of_comments == 0){
									nest_comment = false;
								//}
							}
						} else if (inFile.eof()){
							nest_comment = false;
						} else if (c == '/'){
							inFile.get(c);
							if (c == '*'){
								num_of_comments++; 
							}
						} else if (c == '\n'){
							line_counter++;
						}
						inFile.get(c);
					}
					grab_prev_c = true;
					num_of_comments = 0;
					nest_comment = false;
				} else {
					tok.type = "T_DIVIDE"; tok.actual_value = "/"; tok.line_number = line_counter; tok_list.push_back(tok);
					grab_prev_c = true;
				}
			}
			else if (c == ','){ tok.type = "T_COMMA"; tok.actual_value = ","; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (c == ';'){ tok.type = "T_SEMICOLON"; tok.actual_value = ";"; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (c == '('){ tok.type = "T_LPARANTH"; tok.actual_value = "("; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (c == ')'){ tok.type = "T_RPARANTH"; tok.actual_value = ")"; tok.line_number = line_counter; tok_list.push_back(tok);} 
			else if (c == '['){ tok.type = "T_LBRACKET"; tok.actual_value = "["; tok.line_number = line_counter; tok_list.push_back(tok);}
			else if (c == ']'){ tok.type = "T_RBRACKET"; tok.actual_value = "]"; tok.line_number = line_counter; tok_list.push_back(tok);}
			

			else {tok.type = "T_UNKOWN"; tok.line_number = line_counter; tok_list.push_back(tok); error_handler.error(line_counter, 1);}
				
			tok = clearToken(tok);
		} 

		peeker = inFile.peek();

		if (peeker == EOF){
			tok.type = "T_ENDFILE"; tok.line_number = line_counter; tok_list.push_back(tok);
			tok = clearToken(tok);
		}


	
	}
	inFile.close();
}


Token Scanner::getToken(){
	Token tok;
	

	return tok;
}

void Scanner::print(){
	for (int i = 0; i < tok_list.size(); i++){
		cout << '[' << tok_list[i].line_number << ']' << " " << tok_list[i].actual_value << " " << tok_list[i].type << endl;
	}
}