//
//  Ship.hpp
//  asteroids
//
//  Created by Chaofan Su on 9/19/17.
//
//

#ifndef Ship_hpp
#define Ship_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Game.hpp"

///ship class defines all ship properties\n
///There is acceleration and decceleration properties for the movement of ship, a constant maximum speed is defined to limit the speed\n
///Proper algorithm and calculation are implemented to make the ship rotate smoothly instead of simply going up, down, left and right\n
///Ship is also gaven a shiel function. When keyboard "O" is entered there will be a circle shiel aound the ship and any asteroid run into it will be destroyed right away. The shield will only last for 3 seconds each time press the key\n
///5 lives are given to the spaceship here, when ship is destroyed five times, there will be a "MISSION FAILED" message and the ending music\n
///when spaceship is destroyed less than five times, press the "+" key will set the ship back live and starts from the center of screen
class Ship {
public:
    Ship();
    sf::ConvexShape shape;
    sf::CircleShape shield;
    void ProcessEvents();
    void update(float time);
    void drawShape();
    void drawShield();
    void UpdatePosition();
    bool IsAlive();
    void kill();
    int getShipLives();
    void setShipBackLive();
    bool isDestroy();
    bool isHit;
    void setHit();
    bool IsWithShield();
    void setWithShield();
    void setWithoutShield();
    void requestLive();
    bool IsRequestLive();
    void setRequestLive();
private:
    sf::Vector2f mVelocity;
    float maxSpeed;
    float xSpeed, ySpeed;
    float rotationSpeed;
    bool isAlive;
    int shipLives;
    bool withShield;
    bool isRequestLive;
 };
 
#endif /* Ship_hpp */
