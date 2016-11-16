#include <iostream>
#include <fstream>
#include "reflector.h"
#include "errors.h"
#include <cstdio>
#include <cassert>

using namespace std;

Reflector::Reflector(const char* filename){
	ifstream input(filename);
	for (int n=0;n<26;n++)
		input>>list[n];
}

char Reflector::swap(char input){
	int x=input - 'A';
	for (int n=0;n<26;n++){
		if (x==list[n]){
			if (n%2==0)
				return (list[n+1]+'A');
			else
				return (list[n-1]+'A');
		}
	}
} 
				
			 
