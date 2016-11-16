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
	char filename[50];
	total_rotors=argc-4;
	position=new int[total_rotors];
	ifstream input(argv[argc-1]);
	for (int n=0;n<total_rotors;n++)
		input>>position[n];
	rotor_array=new Rotor*[total_rotors];
	for (int n=0;n<total_rotors;n++)
		rotor_array[n]=new Rotor(argv[3+n], position[n]);
	//strcpy(filename, argv[1]);
	plugboard=new Plugboard(argv[1]);
	//strcpy(filename, argv[2]);
	reflector=new Reflector(argv[2]);
}
void Enigma::run(char input){
	char runner, output;
	int n=total_rotors-1;
	do {
		rotor_array[n]->make_turn();
	}while(rotor_array[n--]->is_notch()&&n>=0);
	runner=plugboard->swap(input);
	for (int n=1;n<=total_rotors;n++){
		runner=rotor_array[total_rotors-n]->scramble_forwards(runner);
	}
	runner=reflector->swap(runner);
	for (int n=0;n<total_rotors;n++){
		runner=rotor_array[n]->scramble_backwards(runner);
	}
	output=plugboard->swap(runner);
	cout<<output;
}
	
	

	
