#ifndef ROTORS_H
#define ROTORS_H

class Rotor
{
private:
	int forward_list[26];
	int backward_list[26];
	int turns;
	int* notch_locations;
	int number_of_notches;
public:
	friend void invert_list(int a[26], int b[26]);
	Rotor(const char* filename, int starting_point);
	void make_turn();
	bool is_notch();
	char scramble_forwards(char input);
	char scramble_backwards(char input);
};

void invert_list(const int a[26], int b[26]);

#endif
