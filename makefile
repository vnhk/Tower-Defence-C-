CFLAGS=-Wall

CC=g++

LIBS=-L ./SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

INCLUDE=-I ./SFML/include

all: TowerDefence
  
TowerDefence: main.o Editor.o Game.o GameObj.o GameFun.o LevelsObject.o Npc.o Road.o Shot.o Tower.o HUD.o Gold.o Menu.o Animation.o Info.o
	@$(CC) $(CFLAGS) main.o Shot.o Editor.o Game.o GameObj.o GameFun.o LevelsObject.o Npc.o Road.o Tower.o HUD.o Gold.o Menu.o Animation.o Info.o -o TowerDefence $(LIBS)

main.o: main.cpp	
	@echo 'Building...'
	@$(CC) -c $(INCLUDE) main.cpp

GameObj.o: GameObj.cpp
	@$(CC) -c $(INCLUDE) GameObj.cpp

GameFun.o: GameFun.cpp
	@$(CC) -c $(INCLUDE) GameFun.cpp
    	
%.o: %.cpp %.h
	@$(CC) -c $(INCLUDE) $< -o $@

clean:
	@echo 'Removing -o files'
	@rm -f *.o TowerDefence
