
all: turtix.out

turtix.out: main.o Baby_turtle.o Enemy.o Location.o Portal.o Turtix_game.o Turtle.o Bonus.o Animation.o
	g++ main.o Baby_turtle.o Enemy.o Location.o Portal.o Turtix_game.o Turtle.o Bonus.o Animation.o -lsfml-graphics -lsfml-window -lsfml-system -o turtix.out

main.o: main.cpp
	g++ -c main.cpp

Baby_turtle.o: Baby_turtle.cpp
	g++ -c Baby_turtle.cpp

Enemy.o:    Enemy.cpp
	g++ -c Enemy.cpp

Location.o: Location.cpp
	g++ -c Location.cpp

Portal.o: Portal.cpp
	g++ -c Portal.cpp

Turtix_game.o: Turtix_game.cpp
	g++ -c Turtix_game.cpp

Turtle.o: Turtle.cpp
	g++ -c Turtle.cpp

Bonus.o: Bonus.cpp
	g++ -c Bonus.cpp

Animation.o: Animation.cpp
	g++ -c Animation.cpp

clean:
	rm *.o turtix.out
