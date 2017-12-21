//
//  Ship.cpp
//  asteroids
//
//  Created by Chaonfan Su on 9/19/17.
//
//

#include "Ship.hpp"
///default constructor of ship class
Ship::Ship() {
     isAlive = true;
     shipLives = 5;
     isHit =false;
     withShield = false;
     isRequestLive = false;
     drawShape();
     drawShield();
     rotationSpeed = 15.0f;
     maxSpeed = 2.0f;
     
     mVelocity.x = 0.0f;
     mVelocity.y = 0.0f;
    
     xSpeed= 0;
     ySpeed = 0;
}

///draw the shape of the ship and set the default position to be the center of the window
void Ship::drawShape() {
    shape.setPointCount(4);
    shape.setPoint(0, sf::Vector2f(20.0f, 0.0f));
    shape.setPoint(1, sf::Vector2f(-20.0f, 18.f));
    shape.setPoint(2, sf::Vector2f(-8.0f, .0f));
    shape.setPoint(3, sf::Vector2f(-20.0f, -18.f));
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2);
    shape.setRotation(0.0f);
}

///ship is given a shield protection. When keyboard "O" is entered there will be a circle shiel aound the ship and any asteroid run into it will be destroyed right away. The shield will only last for 3 seconds each time press the key. Detailed implementation is in world class
void Ship::drawShield() {
    shield.setRadius(120);
    shield.setFillColor(sf::Color(0, 0, 0, 0));
    shield.setOutlineThickness(5.0f);
    shield.setOutlineColor(sf::Color::Cyan);
    shield.setPosition(20000.f, 20000.f);
}

///There is acceleration and decceleration properties for the movement of ship defined in the event and update function, a constant maximum speed is defined to limit the speed
void Ship::ProcessEvents() {
     if(isHit) return;
     xSpeed = 0;
     ySpeed = 0;
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
         ySpeed = 1.0f;
     }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
         ySpeed = -1.0f;
     }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
         xSpeed = 1.0f;
     }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
         xSpeed = -1.0f;
     }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
         setWithShield();
     }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
         isRequestLive = true;
     }
}

///set the ship alive if it request for live
void Ship::requestLive() {
    isRequestLive = true;
}

///decide if the ship is requsting live
bool Ship::IsRequestLive() {
    return isRequestLive;
}

///set the ship to dead
void Ship::setRequestLive() {
    isRequestLive = false;
}

///set the ship to be hit
void Ship::setHit() {
    isHit = true;
    mVelocity.x=0.f;
    mVelocity.y=0.f;
}

///Proper algorithm and calculation are implemented to make the ship rotate smoothly instead of simply going up, down, left and right
void Ship::update(float time) {
     if (isHit) return;
     if (xSpeed != 0) {
         shape.rotate(xSpeed * rotationSpeed * time);
     }
     int accerAdjust = 20;
     if (ySpeed != 0) {
         mVelocity.x += ySpeed * time * cos(shape.getRotation() * (3.14159f / 180.0f)) / accerAdjust;
         mVelocity.y += ySpeed * time * sin(shape.getRotation() * (3.14159f / 180.0f)) / accerAdjust;
         if (std::abs(mVelocity.x) > maxSpeed) {
             if (mVelocity.x > 0) {
                 mVelocity.x = maxSpeed;
             } else {
                 mVelocity.x = -maxSpeed;
             }
         }
         if (std::abs(mVelocity.y) > maxSpeed) {
             if (mVelocity.y > 0) {
                 mVelocity.y = maxSpeed;
             } else {
                 mVelocity.y = -maxSpeed;
             }
         }
     }
     shape.move(mVelocity);
     UpdatePosition();
}

///out of bound detection
void Ship::UpdatePosition() {
     sf::Vector2f position = shape.getPosition();
     
     if (position.x < -10.0f)
         position.x = WINDOW_WIDTH;
     else if (position.x > WINDOW_WIDTH)
         position.x = 0.0f;
     
     if (position.y < -10.0f)
         position.y = WINDOW_HEIGHT;
     else if (position.y > WINDOW_HEIGHT)
         position.y = 0.0f;
     shape.setPosition(position);
}

///decide if the ship is alive
bool Ship::IsAlive() {
    return isAlive;
}

///5 lives are given to the spaceship here, when ship is destroyed five times, there will be a "MISSION FAILED" message and the ending music
void Ship::kill() {
    isAlive = false;
    shipLives--;
}

///get the current lives of ship
int Ship::getShipLives() {
    return shipLives;
}

///when spaceship is destroyed less than five times, press the "+" key will set the ship back live and starts from the center of screen
void Ship::setShipBackLive() {
    isAlive = true;
}

///decide if the ship is destroyed
bool Ship::isDestroy() {
    return (shipLives <= 0);
}

///decide if the ship has the shield around
bool Ship::IsWithShield() {
    return withShield;
}

///set the ship with shield
void Ship::setWithShield() {
    withShield = true;
}

///set the ship without the shield
void Ship::setWithoutShield() {
    withShield = false;
}

