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
	int size=0,status=0;
	int array[50];
	bool invalid_input=false;
	cleaned_sized(size, array, filename, invalid_input,status);
	if ((status!=0))
		return status;
	if (multiple_input(array, size)){
		cerr<<"Impossible plugboard configuration in "<<filename<<endl;
		return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
	}
	if (size%2!=0){
		cerr<<"Incorrect number of parameters in "<<filename<<endl;
		return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
	}
	if (not_in_range(array, size)){
		cerr<<"Input parameters in "<<filename<<" not in range."<<endl;
		return INVALID_INDEX;
	}
	if (invalid_input){
		cerr<<"Non numeric character in "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	return NO_ERROR;
}

int check_rotor(const char* filename){
	int size=0,status=0;
	int array[50];
	bool invalid_input=false;
	cleaned_sized(size, array, filename, invalid_input,status);
	if((status!=0))
		return status;
	if (multiple_input(array,26)||size<=25){
		cerr<<"Invalid rotor mapping in "<<filename<<endl;
		return INVALID_ROTOR_MAPPING;
	}
	if (not_in_range(array,26)){
		cerr<<"Parameters in "<<filename<<" not in range"<<endl;
		return INVALID_INDEX;
	}
	if(invalid_input){
		cerr<<"Non-numeric input character in "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	return NO_ERROR;
}

int check_reflector(const char* filename){
	int size=0, status=0;
	int array[50];
	bool invalid_input=false;
	cleaned_sized(size, array, filename, invalid_input,status);
	if((status!=0))
		return status;
	if (multiple_input(array, size)){
		cerr<<"Invalid reflector mapping in "<<filename<<endl;
		return INVALID_REFLECTOR_MAPPING;
	}
	if (size!=26){
		cerr<<"Incorrect number of reflector parameters in "<<filename<<endl;
		return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
	}
	if (not_in_range(array,26)){
		cerr<<"Parameter in "<<filename<<" not in range"<<endl;
		return INVALID_INDEX;
	}
	if (invalid_input){
		cerr<<"Non-numeric character in "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	return NO_ERROR;
}

int check_position(const char* filename, int argc){
	int size=0, status=0;
	int array[50];
	bool invalid_input=false;
	cleaned_sized(size, array, filename, invalid_input, status);
	if((status!=0))
		return status;
	if ((size)!=(argc-4)){
		cerr<<"Not sufficient starting positions for number of rotors in "<<filename<<endl;
		return NO_ROTOR_STARTING_POSITION;	
	}
	if (not_in_range(array, size)){
		cerr<<"Parameter in "<<filename<<" not in range"<<endl;
		return INVALID_INDEX;
	}
	if (invalid_input){
		cerr<<"Non-numeric character in "<<filename<<endl;
		return NON_NUMERIC_CHARACTER;
	}
	return NO_ERROR;
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
void cleaned_sized(int& size, int array[50], const char* filename, bool& invalid_input, int& status){
	ifstream input(filename);
	char character;
	int count=0, temp;
	if (!input){
		input.close();
		cerr<<"Error opening input file "<<filename<<endl;
		status=ERROR_OPENING_CONFIGURATION_FILE;
		return;
	}
	assert (input);
	char clean[50];
	strncpy(clean,filename,24);
	strncat(clean,"-clean",25);
	ofstream output;
	output.open(clean);
	if (!output){
		output.close();
		input.close();
		cerr<<"Error creating file "<<clean<<endl;
		status=ERROR_CREATING_FILE;
		return;
	}
	input.get(character);
	while(!input.eof()){
		if (!isdigit(character)&&character!=' '&&character!='\n'){
			output.put(' ');
			invalid_input=true;
		}
		else
			output<<character;
		input.get(character);
	}
	input.close();
	output.close();
	input.open(clean);
	if (!input){
		input.close();
		cerr<<"Error opening clean input file "<<clean<<endl;
		status=ERROR_OPENING_CONFIGURATION_FILE;
		return;
	}
	assert(input);
	input>>temp;
	while(!input.eof()){
		array[size++]=temp;
		input>>temp;
	}
	input.close();
}
