#include <iostream>
#include <fstream>
#include "check.h"
#include "errors.h"
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"
#include "enigma.h"
#include <string.h>
#include <cstdio>
#include <cassert>

using namespace std;

int main(int argc, char** argv){
	char string[50];
	if (argc<3){
		cerr<<"Insufficient number of parameters."<<endl;
		return INSUFFICIENT_NUMBER_OF_PARAMETERS;
	}
	int status=0;
	for (int i=1;i<argc;i++){
		if (i==1)
			status=check_plugboard(argv[i]);
		else if (i==2)
			status=check_reflector(argv[i]);
		else if(i==argc-1)
			status=check_position(argv[i], argc);
		else
			status=check_rotor(argv[i]);
		if (status>0)
			return status;
	}
	Enigma enigma_machine(argc, argv);
	cout<<"Please enter your string of characters in capital letters."<<endl;
	char input;
	cin>>ws>>input;
	while (!cin.eof()){
		if (input<'A'||input>'Z'){
			cerr<<input<<" is not a valid character, program is stopped."<<endl;
			return INVALID_INPUT_CHARACTER;
		}
	enigma_machine.run(input);		
	cin>>ws>>input;
	}
	return NO_ERROR;
}	
