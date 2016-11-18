#ifndef CHECKS_H
#define CHECKS_H

int check_plugboard(const char* filename);
//Pre-condition: "filename" is a .pb file (i.e. a plugboard file).
//Post-Condition: Reads in file from file "filename" and errors are returned in the order
//that the file is read. Returns error if file contains either an odd number of parameters or
//more than 26 parameters.
//Returns error if file contains an impossible plugboard configuration 
//(if one letter is mapped to more than one other).
//Checks if all parameters correspond to a letter between A and Z. (Parameters are 0-based
//index into alphabet.
//Checks for any non-numeric characters in file.
int check_rotor(const char* filename);
//Pre-condition: "filename" is a .rot file (i.e. a rotor file).
//Post-Condition: Reads in file from file "filename" and errors are returned in the order
//that the file is read. 
//Returns error if file contains an impossible rotor configuration 
//(if one letter is mapped to more than one other or some letter is not mapped to any other).
//Checks if all parameteters correspond to a letter between A and Z. (Parameters are 0-based
//index into alphabet.)
//Checks for any non-numeric characters in file.
int check_reflector(const char* filename);
//Pre-condition: "filename" is a .rf file (i.e. a reflector file).
//Post-Condition: Reads in file from file "filename" and errors are returned in the order
//that the file is read. Returns error if file doesn't contatin exactly 26 parmeters. 
//Returns error if file contains an impossible reflector configuration 
//(if one letter is mapped to more than one other).
//Checks if all parameteters correspond to a letter between A and Z. (Parameters are 0-based
//index into alphabet.)
//Checks for any non-numeric characters in file.
int check_position(const char* filename, int argc);
//Pre-condition: "filename" is a .pos file (i.e. a position file).
//Post-Condition: Reads in file from file "filename" and errors are returned in the order
//that the file is read. Returns error if file doesn't contain as many parameters as the number
//of rotors specified. 
//Checks if all parameteters correspond to a letter between A and Z. (Parameters are 0-based
//index into alphabet.)
//Checks for any non-numeric characters in file.
bool multiple_input(const int a[], int size, int input, int& n);
//Pre-Condition: "size" corresponds to the number of data entries in array "a"
//and is smaller than 50. "input" contains number between 0 and 25.
//Post-Condition: checks if "input" is equal to any previous numbers in array "a".
#endif
