#include <iostream>
#include <fstream>
#include "check.h"
#include "enigma.h"
#include "errors.h"
#include "rotor.h"
#include <cstdio>
#include <cassert>

using namespace std;


Rotor::Rotor(const char* filename, int starting_point)
{
	ifstream input(filename);
	for (int n=0;n<26;n++)
		input>>forward_list[n];
	int temp_array[26];
	int n=0;
	while(!input.eof()){
		input>>temp_array[n];
		n++;
	}
	number_of_notches=n-1;
	notch_locations=new int[number_of_notches];
	for (int m=0;m<number_of_notches;m++){
		notch_locations[m]=temp_array[m];
	}
	invert_list(forward_list,backward_list);
	turns=starting_point;
}
void Rotor::make_turn(){
	turns++;
	if (turns==26)
		turns=0;
}
bool Rotor::is_notch(){
	for (int n=0;n<number_of_notches;n++){
		if (turns==notch_locations[n])
			return true;
	}
	return false;
}

char Rotor::scramble_forwards(char input)
{
	int z,x;
	x=input-'A'+turns;
	if (x>25)
		x-=26;
	if (x<0)
		x+=26;
	z=(forward_list[x]-turns);
	if (z>25)
		z-=26;
	if (z<0)
		z+=26;
	return 'A'+z;
}
	
char Rotor::scramble_backwards(char input)
{
	int z,x;
	x=input-'A'+turns;
	if (x>25)
		x-=26;
	if (x<0)
		x+=26;
	z=(backward_list[x]-turns);
	if (z>25)
		z-=26;
	if (z<0)
		z+=26;
	return 'A'+z;
}
void invert_list(const int a[26], int b[26]){
	for (int n=0;n<26;n++){
		int m=0;
		while (n!=a[m])
			m++;
		b[n]=m;
	}
}		
