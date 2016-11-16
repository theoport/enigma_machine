#ifndef ENIGMA_H
#define ENIGMA_H

class Rotor;
class Plugboard;
class Reflector;

class Enigma
{
private:
	int total_rotors;
public:
	Rotor** rotor_array;
	Reflector* reflector;
	Plugboard* plugboard;
	int* position;
	Enigma(int argc, char **argv);
	void run(char input);
	int get_total_rotors(){return total_rotors;}
};
#endif
