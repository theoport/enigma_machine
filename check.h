#ifndef CHECKS_H
#define CHECKS_H

int check_plugboard(const char* filename);
int check_rotor(const char* filename);
int check_reflector(const char* filename);
int check_position(const char* filename, int argc);
bool multiple_input(const int a[], int size, int input);

#endif
