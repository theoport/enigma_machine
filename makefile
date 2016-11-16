enigma: main.o enigma.o reflector.o plugboard.o rotor.o check.o enigma.h reflector.h plugboard.h rotor.h check.h errors.h 
	g++ -g enigma.o reflector.o plugboard.o rotor.o check.o main.o -o enigma

main.o: main.cpp  
	g++ -g -c main.cpp  
 
enigma.o: enigma.cpp
	g++ -g -c enigma.cpp 

reflector.o: reflector.cpp
	g++ -g -c reflector.cpp 

plugboard.o: plugboard.cpp 
	g++ -g -c plugboard.cpp

rotor.o: rotor.cpp 
	g++ -g -c rotor.cpp
 
check.o: check.cpp 
	g++ -g -c check.cpp

clean:
	rm -f *.o enigma


