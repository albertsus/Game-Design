//
//  World.hpp
//  asteroids
//
//  Created by Chaofan Su on 9/20/17.
//  Copyright © 2017 su. All rights reserved.
//


#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Ship.hpp"
#include "Asteroids.hpp"
#include "Weapons.hpp"
#include "Game.hpp"

///world class handles all entity updates, certain events, and integrates the behavior of ship, asteroids, and weapons\n
///score of the game is counted here; the score is incremented each time the asteroid is being hit\n
///difficult level of the game is also set here. When all the asteroids in the current level are destroyed, the game will jump to next level and more asteroids are coming out. Six levels(can be set to other number) are defined in the current version, and the number of asteroids will add three more when it comes to next level
class World {
    
    const int DIFFICULT_LEVEL = 6;
    
public:
    World();
    void ProcessEvents(const sf::Event& event);
    void update(float time);
    void draw(sf::RenderTarget& target);
    int getScore();
    bool IsShipAlive();
    bool IsLevelUp();
    bool IsPlayerWin();
    bool IsPlayerLose();
    void setPlayerWin();
    void setPlayerLose();
    int displayShipLives();
private:
    Ship ship;
    std::vector<Asteroids> asteroids;
    std::vector<Weapons> weapons;
    int score;
    int shipTimeCnt;
    int weaponTimeCnt;
    int levelTimeCnt;
    int shieldTimeCnt;
    bool pistolMode;
    bool machineGunMode;
    bool isLevelUp;
    int difficultLevel;
    bool playerWin;
    bool playerLose;
};


#endif /* World_hpp */
