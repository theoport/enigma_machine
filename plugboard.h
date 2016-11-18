#ifndef PLUGBOARDS_H
#define PLUGBOARDS_H


class Plugboard
{
private:
	int* pairs;
	int data_entries;
public:
	Plugboard(const char* filename);
	~Plugboard();
	char swap(char input);
};

#endif
