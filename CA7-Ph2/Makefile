all: futballFantasy.out

futballFantasy.out: main.o FutballFantasy.o Match.o Player.o Week.o Exceptions.o User.o League.o Team.o FantasyTeam.o
	g++ -std=c++11 -g -Wall main.o FutballFantasy.o Match.o Player.o Week.o Exceptions.o User.o League.o Team.o FantasyTeam.o -o futballFantasy.out

main.o: main.cpp FutballFantasy.hh League.hh Team.hh Week.hh Player.hh Match.hh Manual.hh User.hh Exceptions.hh FantasyTeam.hh
	g++ -c main.cpp

FutballFantasy.o: FutballFantasy.cpp FutballFantasy.hh League.hh Team.hh Week.hh Player.hh Match.hh Manual.hh User.hh Exceptions.hh FantasyTeam.hh
	g++ -c FutballFantasy.cpp

Match.o: Match.cpp Match.hh Team.hh Player.hh Manual.hh
	g++ -c Match.cpp

Week.o: Week.cpp Week.hh Match.hh Team.hh Player.hh Manual.hh
	g++ -c Week.cpp

Team.o: Team.cpp Team.hh Player.hh Manual.hh
	g++ -c Team.cpp

Player.o: Player.cpp Player.hh Manual.hh
	g++ -c Player.cpp

Exceptions.o: Exceptions.cpp Exceptions.hh
	g++ -c Exceptions.cpp

User.o: User.cpp User.hh Manual.hh Player.hh Exceptions.hh FantasyTeam.hh
	g++ -c User.cpp

League.o: League.cpp League.hh Team.hh Week.hh Player.hh Match.hh Manual.hh
	g++ -c League.cpp

FantasyTeam.o: FantasyTeam.cpp FantasyTeam.hh Player.hh Manual.hh Exceptions.hh
	g++ -c FantasyTeam.cpp

clean:
	rm *.o futballFantasy.out
