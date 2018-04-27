#include <fstream>
#include <iostream>
//#include <cstdlib>
#include <string>
#include <string.h>
//#include <vector> 
#include <stdio.h>

#include "Structures.h"
#include "Scanner.h"

using namespace std;


bool isNum(char c){
	if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9'){
		return true;
	} else {
		return false;
	}
}

Token clearToken(Token input){
	for (int i = 0; i < (input.actual_value).length(); i++){
		input.actual_value[i] = '\0';
	}
	for (int i = 0; i < (input.type).length(); i++){
		input.type[i] = '\0';
	}
	return input;
}

/*------------------------------------------  
	Reads File and Stores Tokens in a Vector 
------------------------------------------*/
void Scanner::scanInit(char *argv[]){
	ifstream inFile;
	bool number_checker = false, skip = false, record_token = false, grab_prev_c = false;
	char c; 
	int peeker = 0, j = 0, line_counter;
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