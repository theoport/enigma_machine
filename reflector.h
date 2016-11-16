#ifndef REFLECTORS_H
#define REFLECTORS_H 

class Reflector
{
private:
	int list[26];
public:
	Reflector(const char* filename);
	char swap(char input);
};

#endif
