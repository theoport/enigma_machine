#include <iostream>
#include <fstream>
#include "check.h"
#include "errors.h"
#include "plugboard.h"
#include <cstdio>
#include <cassert>

using namespace std;


Plugboard::Plugboard(const char* filename){
	//reads parameters in filename into temporary array and counts number of parameters:
	ifstream input(filename);
	int temp[30];
	int count=0;
	while(!input.eof())
		input>>temp[count++];
	data_entries=count-1;
	//creates dynamic array of previously counted size:
	pairs=new int[data_entries];
	//fills in parameters from temporary array into dynamic array:
	for (int n=0;n<data_entries;n++)
		pairs[n]=temp[n];
}

Plugboard::~Plugboard()
{
	delete [] pairs;
}

char Plugboard::swap(char input){
	int x=input - 'A';
	for (int n=0;n<data_entries;n++){
		if (x==pairs[n]){
			if (n%2==0)
				return (pairs[n+1]+'A');
			else
				return (pairs[n-1]+'A');
		}
	}
	return input;
} 
				
			 
