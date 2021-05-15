#pragma once
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "constants.h"
#include "lane_model.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Game {

    private:
        // Singleton
        Game();

        // Basic properties
        int score;
        int level;
        int coins;
        vector<Lane*> lanes;

        // Auxiliary properties
        unsigned int grass_in_a_row;
        unsigned int street_in_a_row;

        // Auxiliary methods
        vector<Lane*> generateBaseLanes();

    public:
        // Constructor and singleton method
        Game(Game const&) = delete;
        void operator=(Game const&) = delete;
        static Game& get_instance();

        // Getters & Setters
        int getScore();
        int getLevel();
        int getCoins();
        vector<Lane*> getLanes();
        void setScore(int score);
        void addCoin();

        // Lane generation methods
        Lane* addLane(float position);
        void removeLane();

};

#endif
