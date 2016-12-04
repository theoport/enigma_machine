#include <iostream>
#include <fstream>
#include "errors.h"
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"
#include "enigma.h"
#include <string.h>
#include <cstdio>
#include <cassert>

using namespace std;

Enigma::Enigma(int argc, char** argv){
	if (argc>3){
		total_rotors=argc-4;
		//creates dynamic array of rotor starting positions given in position configuration file:
		position=new int[total_rotors];
		ifstream input(argv[argc-1]);
		for (int n=0;n<total_rotors;n++)
			input>>position[n];
		//creates dynamic array of rotors:
		rotor_array=new Rotor*[total_rotors];
		for (int n=0;n<total_rotors;n++)
			rotor_array[n]=new Rotor(argv[3+n], position[n]);
	}
	else{
		total_rotors=0;
		position=NULL;
		rotor_array=NULL;
	}
	//constructs new plugboard and sets pointer to it:
	plugboard= new Plugboard(argv[1]);
	//constructs new reflector and sets pointer to it:
	reflector= new Reflector(argv[2]);
	
}

Enigma::~Enigma(){
	delete plugboard;
	delete reflector;
	for (int n=0;n<total_rotors;n++)
		delete rotor_array[n];
	delete [] rotor_array;
	delete [] position;
}

void Enigma::run(char input){
	char runner, output;
	int n=total_rotors-1;
	//turns the first rotor, if rotors exist. turns further rotors depending on notch locations:
	if (n>=0){
		do {
			rotor_array[n]->make_turn();
		}while(rotor_array[n--]->is_notch()&&n>=0);
	}
	//swaps input character with plugboard-partner if it exists, otherwise returns input character: 
	runner=plugboard->swap(input);
	//scrambles character through rotors, starting with the right-most rotor:
	for (int n=1;n<=total_rotors;n++){
		runner=rotor_array[total_rotors-n]->scramble_forwards(runner);
	}
	//swaps input character with reflector-partner:
	runner=reflector->swap(runner);
	//scramble backwards through rotors starting with left-most rotor:
	for (int n=0;n<total_rotors;n++){
		runner=rotor_array[n]->scramble_backwards(runner);
	}
	//swap with plugboard-partner:
	output=plugboard->swap(runner);
	cout<<output;
	return;
}
	
	

	
