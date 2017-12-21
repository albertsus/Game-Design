//
//  Weapons.cpp
//  asteroids
//
//  Created by Chaofan Su on 9/19/17.
//
//

#include "Weapons.hpp"

///There are two types of weapons implemented in the game. One is single direction bullet, another has three rows of bullets; the rows have certain angle(12 degrees) to each other and can destroy the asteroids with more broad range
Weapons::Weapons(sf::Vector2f position,float angle) {
    shape.setPosition(position);
    isAlive = true;
    setPistolMode(angle);
}

///set only one row bullet mode
void Weapons::setPistolMode(float angle) {
    shape.setSize(sf::Vector2f(15.0f, 5.0f));
    shape.setFillColor(sf::Color::Yellow);
    shape.setRotation(angle);
    direction.x = cos(angle * (3.14159f/180.f));
    direction.y = sin(angle * (3.14159f/180.f));
    bulletSpeed = 1000.0f;
}

///kill the bullet(make it to be false)
void Weapons::kill() {
    isAlive = false;
}

///decide if the bullet is alive
bool Weapons::IsAlive() {
    return isAlive;
}

///update the weapon class events
void Weapons::update(float time) {
    if (isAlive) {
        sf::Vector2f distance = bulletSpeed * time * direction;
        shape.move(distance);
    }
}

