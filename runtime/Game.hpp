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

static void main_game() {
    child_write("2^6\n");
    child_read();
    child_write("2^3\n");
    child_read();
}

typedef struct {int x; int y;} Position;

class Spaceship
{
public:
    Position mPosition;
    Spaceship() {
        mPosition = Position {rand() % 2000, rand() % 50};
    }
};

class Game
{
public:
    const char *const name = "Spaceship Simulator";
    Game() {
        srand((unsigned) time(NULL));
        std::cout<<"[v] Game "<<name<<" started."<<std::endl;
    }
    void process() {
        
    }
    ~Game() {
        std::cout<<"[v] Resources for game "<<name<<" freed."<<std::endl;
    }
private:
};