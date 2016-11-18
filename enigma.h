#ifndef ENIGMA_H
#define ENIGMA_H

class Rotor;
class Plugboard;
class Reflector;

class Enigma
{
private:
	int total_rotors;
	Rotor** rotor_array;
	Reflector* reflector;
	Plugboard* plugboard;
	int* position;
public:
	~Enigma();
	Enigma(int argc, char **argv);
	void run(char input);
};
#endif

//Pre-Condition: All specified plugboard, reflector, rotor and position files in pointer array
//"**argv" are well formed. "input" is a character between A and Z. "**argv" has at least three 
//and not four file parameters.
//Post-Condition: This class emulates an enigma machine. For details on how an enigma machine 
//works, visit enigma.louisedade.co.uk. This machine can be built with any number of rotors,
//one plugboard and one reflector, whose configuration can be read from files specified
//in the command line.  
