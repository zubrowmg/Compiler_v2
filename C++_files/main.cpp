#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <vector> 
#include <stdio.h>

#include "Scanner.h"
#include "WrapperPass2.h"
#include "Structures.h"

using namespace std;

Scanner scan; Token tok;


bool parameterCheck(int argc, char *argv[]){								
	if (argc != 2){										//this condition makes sure that there is a second parameter
        cout << "Enter a txt file after the program name" << endl;
        cout << "example: program txt" << endl;
   		return false;
	 } else if (argc > 2){  							//this condition makes sure that there aren't more than 2 parameters
        cout << "You entered too many parameters" << endl;
        cout << "example: program txt" << endl;
    	return false;
	} 	
}

int main(int argc, char *argv[]){	
	bool correct_input = false;
	correct_input = parameterCheck(argc, argv);

	

	if (correct_input){
		scan.scanInit(argv);
		//while (tok.type != "T_ENDFILE"){
			//tok = scan.getToken();
		//}
	}

		
	return 0;
}