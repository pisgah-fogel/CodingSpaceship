#pragma once

#include <iostream>
#include <stdlib.h> // srand and time

#include "UnitTest.hpp"
#include "Engine.hpp"

#define POS_X_MIN 0
#define POS_X_MAX 2000
#define POS_Y_MIN 0
#define POS_Y_MAX 2000

#define SPAWN_X_MIN 100
#define SPAWN_X_MAX 1900
#define SPAWN_Y_MIN 1700
#define SPAWN_Y_MAX 1900

int test_game_macro() {
    if (POS_X_MAX <= POS_X_MIN) {
        std::cout<<"Error: POS_X_MAX <= POS_X_MIN"<<std::endl;
        return 1;
    }
    if (POS_Y_MAX <= POS_Y_MIN) {
        std::cout<<"Error: POS_Y_MAX <= POS_Y_MIN"<<std::endl;
        return 1;
    }
    if (SPAWN_X_MAX <= SPAWN_X_MIN) {
        std::cout<<"Error: SPAWN_X_MAX <= SPAWN_X_MIN"<<std::endl;
        return 1;
    }
    if (SPAWN_Y_MAX <= SPAWN_Y_MIN) {
        std::cout<<"Error: SPAWN_Y_MAX <= SPAWN_Y_MIN"<<std::endl;
        return 1;
    }

    if (SPAWN_X_MIN < POS_X_MIN) {
        std::cout<<"Error: SPAWN_X_MIN < POS_X_MIN"<<std::endl;
        return 1;
    }
    if (SPAWN_Y_MIN < POS_Y_MIN) {
        std::cout<<"Error: SPAWN_Y_MIN < POS_Y_MIN"<<std::endl;
        return 1;
    }
    if (SPAWN_X_MAX > POS_X_MAX) {
        std::cout<<"Error: SPAWN_X_MAX > POS_X_MAX"<<std::endl;
        return 1;
    }
    if (SPAWN_Y_MAX > POS_Y_MAX) {
        std::cout<<"Error: SPAWN_Y_MAX > POS_Y_MAX"<<std::endl;
        return 1;
    }
    return 0;
}
START_TEST(test_game_macro);

typedef struct {int x; int y;} Position;

class Spaceship
{
public:
    Position mPosition;
    Spaceship() {
        mPosition = Position {SPAWN_X_MIN + rand() % (SPAWN_X_MAX-SPAWN_X_MIN+1), SPAWN_Y_MIN + rand() % (SPAWN_Y_MAX-SPAWN_Y_MIN+1)};
    }
};

class Game
{
public:
    const char *const name = "Spaceship Simulator";
    std::vector<Spaceship> mShips;
    std::vector<Position> floor;
    Game() {
        srand((unsigned) time(NULL));
        init_ships();
        init_map();
        std::cout<<"[v] Game "<<name<<" started."<<std::endl;
    }
    void process() {
        if (mShips.size() <= 0) {
            std::cout<<"[x] Error: No spaceships instanciated in the game"<<std::endl;
            return;
        }
        child_write("2^6\n");
        child_read();
        child_write("2^3\n");
        child_read();
    }
    ~Game() {
        std::cout<<"[v] Resources for game "<<name<<" freed."<<std::endl;
    }
private:
    void init_ships() {
        mShips.push_back(Spaceship());
    }
    void init_map() {
        floor.push_back(Position {.x = POS_X_MIN, .y = 100});
        floor.push_back(Position {.x = POS_X_MAX, .y = 100});
    }
};

static void main_game() {
    Game game = Game();
    game.process();
}