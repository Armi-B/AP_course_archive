all: futballFantasy.out

futballFantasy.out: main.o FutballFantasy.o Match.o Player.o Week.o Exceptions.o User.o League.o Team.o FantasyTeam.o
	g++ -std=c++11 -g -Wall main.o FutballFantasy.o Match.o Player.o Week.o Exceptions.o User.o League.o Team.o FantasyTeam.o -o futballFantasy.out

main.o: main.cpp
	g++ -c main.cpp

FutballFantasy.o: FutballFantasy.cpp
	g++ -c FutballFantasy.cpp

Match.o: Match.cpp
	g++ -c Match.cpp

Week.o: Week.cpp
	g++ -c Week.cpp

Team.o: Team.cpp
	g++ -c Team.cpp

Player.o: Player.cpp
	g++ -c Player.cpp

Exceptions.o: Exceptions.cpp
	g++ -c Exceptions.cpp

User.o: User.cpp
	g++ -c User.cpp

League.o: League.cpp
	g++ -c League.cpp

FantasyTeam.o: FantasyTeam.cpp
	g++ -c FantasyTeam.cpp

clean:
	rm *.o futballFantasy.out
