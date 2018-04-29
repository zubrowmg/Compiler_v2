#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <iostream>
#include <queue> 

#include "Structures.h"
#include "Error.h"

using namespace std;

class Scanner{
	private:
        int current_vector_pos;
    	Error error_handler;
        queue<Token> tok_list;
    public:
        Scanner();
        void scanInit(char *argv[]);
    	Token getToken();
        void print();
};

#endif