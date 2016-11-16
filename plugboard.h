#ifndef PLUGBOARDS_H
#define PLUGBOARDS_H


class Plugboard
{
private:
	int* value;
	int data_entries;
public:
	Plugboard(const char* filename);
	char swap(char input);
};

#endif
