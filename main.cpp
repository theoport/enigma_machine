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
#include <string>

using namespace std;

int main(int argc, char** argv){
	char string[50];
	if (argc<3||argc==4){
		cerr<<"Insufficient number of parameters."<<endl;
		return INSUFFICIENT_NUMBER_OF_PARAMETERS;
	}
	int status=0;
	//checks if configuration files from command line are well formed:
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
	//constructs enigma machine:
	Enigma enigma_machine(argc, argv);
	char input;
	cin>>ws>>input;
	while (!cin.eof()){
		//checks if input character is between A and Z:
		if (input<'A'||input>'Z'){
			cerr<<input<<" is not a valid character, input has to be in capital letters. Program is stopped."<<endl;
			return INVALID_INPUT_CHARACTER;
		}
		//runs input character through enigma machine and outputs resulting output character:
		else
			enigma_machine.run(input);		
	cin>>ws>>input;	
	}
	return 0;
}	
