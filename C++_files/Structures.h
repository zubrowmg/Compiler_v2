#ifndef STRUCTURES_H
#define STRUCTURES_H



struct Token{
	std::string type;
	std::string actual_value; 						
 	int line_number;

    Token(){
       
    }
};

#endif