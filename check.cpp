#include <iostream>
#include <fstream>
#include "check.h"
#include "errors.h"
#include <cstdio>
#include <cassert>
#include <string>
#include <cstring>

using namespace std;

int check_plugboard(const char* filename)
{
	int size=0, temp,n;
	int array[50];
	ifstream input(filename);
	if (!input){
		input.close();
		cerr<<"Input file "<<filename<<" could not be opened."<<endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	}
	input>>temp;
	while(!input.fail()){
		array[size++]=temp;
		if (size>26){	
			input.close();
			cerr<<"Incorrect number of parameters in plugboard file "<<filename<<endl;
			return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
		}
		if (multiple_input(array, size, temp,n)){
			input.close();
			cerr<<"Impossible configuration in plugboard file "<<filename<<endl;
			return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
		}
		else if (temp<0||temp>25){
			input.close();
			cerr<<"Parameter in plugboard file "<<filename<<" out of range."<<endl;
			return INVALID_INDEX;
		}
		else
			input>>temp;
	}
	if (!input.eof()){
		input.close();
		cerr<<"Non-numeric character in plugboard file "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	if (size%2!=0){
		input.close();
		cerr<<"Incorrect number of parameters in plugboard file "<<filename<<endl;
		return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
	}
	input.close();
	if (input.bad()){
		cerr<<"Error closing configuration file "<<filename<<endl;
		return ERROR_CLOSING_CONFIGURATION_FILE;
	}
	return NO_ERROR;
}

int check_rotor(const char* filename){
	int size=0, temp, n;
	int array[50];
	ifstream input(filename);
	if (!input){
		input.close();
		cerr<<"Input file "<<filename<<" could not be opened."<<endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	}
	input>>temp;
	while(!input.fail()&&size<=25){
		array[size++]=temp;
		if (multiple_input(array, size, temp, n)){
			input.close();
			cerr<<"Invalid mapping of input "<<size<<" to output "<<temp;
			cerr<<" (output "<<temp<<" is already mapped to from input "<<n<<")"<<endl;
			return INVALID_ROTOR_MAPPING;
		}
		else if (temp<0||temp>25){
			input.close();
			cerr<<"Parameter in rotor file "<<filename<<" out of range."<<endl;
			return INVALID_INDEX;
		}
		else
			input>>temp;
	}
	if (input.fail()&&!input.eof()){
		input.close();
		cerr<<"Non-numeric character for mapping in rotor file "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	if (size<=25){
		input.close();
		cerr<<"Not all inputs mapped in rotor file: "<<filename<<endl;
		return INVALID_ROTOR_MAPPING;
	}
	input.close();
	if (input.bad()){
		cerr<<"Error closing configuration file "<<filename<<endl;
		return ERROR_CLOSING_CONFIGURATION_FILE;
	}
	return NO_ERROR;
}

int check_reflector(const char* filename){
	int size=0, temp,n;
	int array[50];
	ifstream input(filename);
	if (!input){
		input.close();
		cerr<<"Input file "<<filename<<" could not be opened."<<endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	}
	input>>temp;
	while(!input.fail()){
		array[size++]=temp;
		if (size>26){
			input.close();
			if (size%2!=0)
				cerr<<"Incorrect (odd) number of parameters in reflector file "<<filename<<endl;
			else
				cerr<<"Too many reflector mappings in reflector file "<<filename<<endl;
			return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
		}
		if (multiple_input(array, size, temp, n)){
			input.close();
			cerr<<"Impossible configuration in reflector file "<<filename<<endl;
			return INVALID_REFLECTOR_MAPPING;
		}
		else if (temp<0||temp>25){
			input.close();
			cerr<<"Parameter in reflector file "<<filename<<" out of range."<<endl;
			return INVALID_INDEX;
		}
		else
			input>>temp;
	}
	if (!input.eof()){
		input.close();
		cerr<<"Non-numeric character for mapping in rotor file "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	if (size!=26){
		input.close();
		if (size%2!=0)
			cerr<<"Incorrect number of parameters in reflector file "<<filename<<endl;
		else 
			cerr<<"Insufficient number of mappins in reflector file: "<<filename<<endl;
		return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
	}
	input.close();
	if (input.bad()){
		cerr<<"Error closing configuration file "<<filename<<endl;
		return ERROR_CLOSING_CONFIGURATION_FILE;
	}
	return NO_ERROR;
}

int check_position(const char* filename, int argc){
	int size=0, temp;
	int array[50];
	ifstream input(filename);
	if (!input){
		input.close();
		cerr<<"input file "<<filename<<" could not be opened."<<endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	}
	input>>temp;
	while(!input.fail()){
		array[size++]=temp;
		if (temp<0||temp>25){
			input.close();
			cerr<<"Parameter in position file "<<filename<<" out of range."<<endl;
			return INVALID_INDEX;
		}
		else
			input>>temp;
	}
	if (!input.eof()){
		input.close();
		cerr<<"Non-numeric character in rotor positions file "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	if ((size)!=(argc-4)){
		cerr<<"Not sufficient starting positions for number of rotors in rotor position file ";
		cerr<<filename<<endl;
		return NO_ROTOR_STARTING_POSITION;	
	}
	input.close();
	if (input.bad()){
		cerr<<"Error closing configuration file "<<filename<<endl;
		return ERROR_CLOSING_CONFIGURATION_FILE;
	}
	return NO_ERROR;
}	

bool multiple_input(const int a[], int size, int input, int& n){
	for (n=0;n<size-1;n++){
		if(input==a[n])
				return true;
	}
	return false;
}


