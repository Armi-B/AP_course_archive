all: main

main: main.o Mission.o Driver.o DriveSystem.o Time.o
	g++ -std=c++11 -g main.o Mission.o Driver.o DriveSystem.o Time.o -o main

main.o: main.cpp
	g++ -c main.cpp

Driver.o: Driver.cpp
	g++ -c Driver.cpp

Time.o: Time.cpp
	g++ -c Time.cpp

DriveSystem.o: DriveSystem.cpp
	g++ -c DriveSystem.cpp

Mission.o: Mission.cpp
	g++ -c Mission.cpp

clean:
	rm *.o main
