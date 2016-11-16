#include <iostream>
#include <fstream>
#include "check.h"
#include "errors.h"
#include <cstdio>
#include <cassert>

using namespace std;

int check_plugboard(const char* filename)
{
	ifstream input(filename);
	if (!input){
		input.close();
		cerr<<"Error opening input file "<<filename<<endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	}
	assert (input);
	int array[30];
	int size=0;
	while(!input.fail()){
		input>>array[size++];
	}
	
	if (multiple_input(array, size-1)){
		input.close();
		cerr<<"Impossible plugboard configuration in "<<filename<<endl;
		return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	}
	if (size%2==0){
		input.close();
		cerr<<"Incorrect number of parameters in "<<filename<<endl;
		return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
	}
	if (not_in_range(array, size-1)){
		input.close();
		cerr<<"Input parameters in "<<filename<<" not in range."<<endl;
		return INVALID_INDEX;
	}
	if (!input.eof()){
		input.close();
		cerr<<"Non numeric character in "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	input.close();
	return 0;
}

int check_rotor(const char* filename){
	ifstream input(filename);
	if (!input){
		input.close();
		cerr<<"Error opening input file "<<filename<<endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	}
	assert(input);
	int array[26];
	int count=0;
	while(!input.fail()&&count<26){
		input>>array[count++];
	}
	if (multiple_input(array,26)||count<=25){
		input.close();
		cerr<<"Invalid rotor mapping in "<<filename<<endl;
		return INVALID_ROTOR_MAPPING;
	}
	if (not_in_range(array,26)){
		input.close();
		cerr<<"Parameters in "<<filename<<" not in range"<<endl;
		return INVALID_INDEX;
	}
	if(input.fail()&&!input.eof()){
		input.close();
		cerr<<"Non-numeric input character in "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	input.close();
	return 0;
}

int check_reflector(const char* filename){
	ifstream input(filename);
	if (!input){
		input.close();
		cerr<<"Error opening input file "<<filename<<endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	}
	assert (input);
	int array[30];
	int size=0;
	while(!input.fail()){
		input>>array[size++];
	}
	if (multiple_input(array, size-1)){
		input.close();
		cerr<<"Invalid reflector mapping in "<<filename<<endl;
		return INVALID_REFLECTOR_MAPPING;
	}
	if (size!=27){
		input.close();
		cerr<<"Incorrect number of reflector parameters in "<<filename<<endl;
		return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
	}
	if (not_in_range(array,26)){
		input.close();
		cerr<<"Parameter in "<<filename<<" not in range"<<endl;
		return INVALID_INDEX;
	}
	if (!input.eof()){
		input.close();
		cerr<<"Non-numeric character in "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	input.close();
	return 0;
}

int check_position(const char* filename, int argc){
	ifstream input(filename);
	if (!input){
		input.close();
		cerr<<"Error opening input file "<<filename<<endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	}
	assert (input);
	int array[30];
	int size=0;
	while(!input.fail()){
		input>>array[size++];
	}
	if ((size-1)!=(argc-4)){
		input.close();
		cerr<<"Not sufficient starting positions for number of rotors in "<<filename<<endl;
		return NO_ROTOR_STARTING_POSITION;	
	}
	if (not_in_range(array, size-1)){
		input.close();
		cerr<<"Parameter in "<<filename<<" not in range"<<endl;
		return INVALID_INDEX;
	}
	if (!input.eof()){
		input.close();
		cerr<<"Non-numeric character in "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	input.close();
	return 0;
}	

bool multiple_input(const int a[], int size){
	for (int n=0;n<size;n++){
		for (int m=0;m<size;m++){
			if ((m!=n)&&a[m]==a[n])
				return true;
		}
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

