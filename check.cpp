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
	int size=0, temp;
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
		if (multiple_input(array, size, temp)){
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
	if (size%2!=0||size>26){
		input.close();
		cerr<<"Incorrect number of parameters in plugboard file "<<filename<<endl;
		return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
	}
	return NO_ERROR;
}

int check_rotor(const char* filename){
	int size=0, temp;
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
		if (multiple_input(array, size, temp)){
			input.close();
			cerr<<"Impossible configuration in rotor file "<<filename<<endl;
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
		cerr<<"Non-numeric character in rotor file "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	if (size<=25){
		input.close();
		cerr<<"Invalid rotor mapping in rotor file "<<filename<<endl;
		return INVALID_ROTOR_MAPPING;
	}
	return NO_ERROR;
}

int check_reflector(const char* filename){
	int size=0, temp;
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
		if (multiple_input(array, size, temp)){
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
		cerr<<"Non-numeric character in reflector file "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	if (size!=26){
		input.close();
		cerr<<"Incorrect number of parameters in reflector file "<<filename<<endl;
		return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
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
		cerr<<"Non-numeric character in position file "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	if ((size)!=(argc-4)){
		cerr<<"Not sufficient starting positions for number of rotors in position file "<<filename<<endl;
		return NO_ROTOR_STARTING_POSITION;	
	}
	return NO_ERROR;
}	

bool multiple_input(const int a[], int size, int input){
	for (int n=0;n<size-1;n++){
		if(input==a[n])
				return true;
	}
	return false;
}

bool not_in_range(const int a[], int size){
	for (int n=0;n<size;n++){
			if (a[n]>25||a[n]<0)
				return true;
	}
	return false;
}

