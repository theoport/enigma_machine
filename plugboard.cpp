#include <iostream>
#include <fstream>
#include "check.h"
#include "errors.h"
#include "plugboard.h"
#include <cstdio>
#include <cassert>

using namespace std;


Plugboard::Plugboard(const char* filename){
	ifstream input(filename);
	int temp[30];
	int count=0;
	while(!input.eof())
		input>>temp[count++];
	data_entries=count-1;
	value=new int[data_entries];
	for (int n=0;n<data_entries;n++)
		value[n]=temp[n];
}

char Plugboard::swap(char input){
	int x=input - 'A';
	for (int n=0;n<data_entries;n++){
		if (x==value[n]){
			if (n%2==0)
				return (value[n+1]+'A');
			else
				return (value[n-1]+'A');
		}
	}
	return input;
} 
				
			 
