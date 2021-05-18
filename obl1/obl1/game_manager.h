#pragma once
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <algorithm>
#include <functional>
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
        int score; // Based on player position
        int level; // Level of difficulty based on player score
        int coins; // Amount of coins gathered
        bool immortal; // Flag for checking if player should die or not
        vector<Lane*> lanes; // Current existing lanes

        // Used for checking lane window constraints
        int upper_lane_limit; 
        int lower_lane_limit; 
        // Used for creating new lanes
        unsigned int grass_in_a_row; 
        unsigned int street_in_a_row;

        // Lane generating methods
        vector<Lane*> generateBaseLanes();
        Lane* addLane(float position);

    public:
        // Constructor and singleton method
        Game(Game const&) = delete;
        void operator=(Game const&) = delete;
        static Game& get_instance();

        // Getters & Setters
        int getScore();
        int getLevel();
        int getCoins();
        bool getImmortal();
        vector<Lane*> getLanes();
        void setScore(int score);
        void addCoin();
        void switchImmortal();

        // Main methods
        void update(float player_position);
        void clean_memory();

};

#endif
