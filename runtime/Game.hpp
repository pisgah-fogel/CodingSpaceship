#pragma once

#include <iostream>

class Game
{
public:
    const char const name[] = "Spaceship Simulator";
    Game() {
        std::cout<<"[v] Game "<<name<<" started."<<std::endl;
    }
    process() {
        
    }
    ~Game() {
        std::cout<<"[v] Resources for game "<<name<<" freed."<<std::endl;
    }
private:
};