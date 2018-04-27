#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <iostream>
#include <vector> 

#include "Structures.h"

using namespace std;

class Scanner{
	private:
    	
        vector<Token> tok_list;
    public:
        void scanInit(char *argv[]);
    	Token getToken();
        void print();
};

#endif