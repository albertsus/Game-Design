//
//  Weapons.hpp
//  asteroids
//
//  Created by Chaofan Su on 9/19/17.
//
//

#ifndef Weapons_hpp
#define Weapons_hpp
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <cmath>
#include "Ship.hpp"

///Weapons class for bullet construction, handling, and drawing\n
///There are two types of weapons implemented in the game. One is normal single direction shooting bullet, another has three rows of bullets at the same time; the bullets contain certain degree (12) to destroy the asteroids in this range
class Weapons {
public:
    Weapons(sf::Vector2f position,float angle);
    void update(float time);
    bool IsAlive();
    void kill();
    sf::RectangleShape shape;
    void setPistolMode(float angle);
    void setLaserMode(float angle);
private:
    sf::Vector2f direction;
    bool isAlive;
    float bulletSpeed;
};
#endif /* Weapons_hpp */
