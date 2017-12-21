//
//  World.cpp
//  asteroids
//
//  Created by Chaofan Su on 9/20/17.
//  Copyright © 2017 su. All rights reserved.
//

#include "World.hpp"
#include "Game.hpp"

///score of the game is counted here; the score is incremented each time the asteroid is being hit
World::World() {
    for (int i = 0; i < 3; i++) {
        Asteroids asteroid;
        asteroids.push_back(asteroid);
    }
    score = 0;
    shipTimeCnt = -1;
    weaponTimeCnt = -1;
    levelTimeCnt = -1;
    shieldTimeCnt = -1;
    pistolMode = true;
    machineGunMode = false;
    difficultLevel = 1;
    playerWin = false;
    playerLose = false;
    isLevelUp = false;
}

///process the events of world class
void World::ProcessEvents(const sf::Event &event) {
    ship.ProcessEvents();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        pistolMode = false;
        machineGunMode = true;
    }
    if (machineGunMode) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            Weapons weapon(ship.shape.getPosition(),ship.shape.getRotation());
            Weapons weapon1(ship.shape.getPosition(),ship.shape.getRotation() + 12);
            Weapons weapon2(ship.shape.getPosition(),ship.shape.getRotation() - 12);
            weapons.push_back(weapon);
            weapons.push_back(weapon1);
            weapons.push_back(weapon2);
        }
        weaponTimeCnt++;
        if (weaponTimeCnt > 55) {
            pistolMode = true;
            machineGunMode = false;
            weaponTimeCnt = -1;
        }
    } else if (pistolMode) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            Weapons weapon(ship.shape.getPosition(),ship.shape.getRotation());
            weapons.push_back(weapon);
        }
    }
}

///difficult level of the game is set. When all the asteroids in the current level are destroyed, the game will jump to next level and more asteroids are coming out. Six levels(can be set to other number) are defined in the current version, and the number of asteroids will add three more when it comes to next level
void World::update(float time) {
    if (ship.getShipLives() > 0 && !playerWin) {
        if (!ship.IsAlive()) {
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
                ship.setHit();
                ship.shape.setPosition(20000.f, 20000.f);
            } else {
                if(shipTimeCnt < 0) {
                    ship.setHit();
                    ship.shape.setPosition(20000.f, 20000.f);
                    shipTimeCnt = 0;
                }
                shipTimeCnt++;
                if(shipTimeCnt > 5) {
                    ship.isHit = false;
                    ship.shape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                    ship.setShipBackLive();
                    shipTimeCnt = -1;
                }
            }
        }
        ship.update(time);
    } else if (ship.getShipLives() <= 0){
        ship.shape.setPosition(10000.f, 10000.f);
    }
    
    if (ship.IsWithShield()) {
        sf::Vector2f movePar(-120.f, -120.f);
        ship.shield.setPosition(ship.shape.getPosition() + movePar);
        shieldTimeCnt++;
        if (shieldTimeCnt > 2000) {
            ship.setWithoutShield();
            shieldTimeCnt = -1;
            ship.shield.setPosition(20000.f, 20000.f);
        }
    }
    
    std::vector<Weapons>::iterator weapon = weapons.begin();
    while (weapon != weapons.end()) {
        if (weapon->IsAlive()) {
            weapon->update(time);
            ++weapon;
        } else
            weapon = weapons.erase(weapon);
    }
    
    std::vector<Asteroids>::iterator asteroid = asteroids.begin();
    while (asteroid != asteroids.end()) {
        if (asteroid->IsAlive()) {
            asteroid->update(time);
            ++asteroid;
        } else
            asteroid = asteroids.erase(asteroid);
    }
    
    std::vector<Asteroids> tmpAsteroids;
    asteroid = asteroids.begin();
    
    while (asteroid != asteroids.end()) {
        weapon = weapons.begin();
        while (weapon != weapons.end()) {
            if (!weapon->IsAlive()) {
                ++weapon;
                continue;
            }
            if (asteroid->IsAlive()){
                if ((asteroid->IsCollision(weapon->shape.getPosition()))){
                    weapon->kill();
                    asteroid->split();
                    sf::Vector2f position = asteroid->shape.getPosition();
                    Asteroids a(position, asteroid->getLevel());
                    tmpAsteroids.push_back(a);
                    score++;
                    break;
                }
            }
            ++weapon;
        }
        if (asteroid->shape.getGlobalBounds().intersects(ship.shield.getGlobalBounds())){
            asteroid->split();
            score++;
        }
        if (asteroid->IsCollision(ship.shape.getPosition())){
            asteroid->split();
            ship.kill();
        }
        if (asteroids.size() != 0) {
            ++asteroid;
        }
    }
    asteroids.insert(asteroids.end(), tmpAsteroids.begin(), tmpAsteroids.end());
    if (asteroids.size() == 0) {
        if (levelTimeCnt == -1) {
            difficultLevel++;
            isLevelUp = true;
        }
        if (difficultLevel >= DIFFICULT_LEVEL) {
            playerWin = true;
            return;
        } else {
            levelTimeCnt++;
            if (levelTimeCnt >= 1000) {
                int numberOfAsteroids = 3 * difficultLevel;
                for (int i = 0; i < numberOfAsteroids; i++) {
                    Asteroids asteroid;
                    asteroids.push_back(asteroid);
                }
                levelTimeCnt = -1;
                isLevelUp = false;
            }
        }
    }
}

///get the current score
int World::getScore() {
    return score;
}

///decide if the ship is alive
bool World::IsShipAlive() {
    return ship.IsAlive();
}

///decide if the
bool World::IsLevelUp() {
    return isLevelUp;
}

///decide if the player loses the game
bool World::IsPlayerLose() {
    return (ship.getShipLives() <= 0);
}

///set the player not lose the game
void World::setPlayerLose() {
    playerLose = false;
}

///display the current lives of ship
int World::displayShipLives() {
    return ship.getShipLives();
}

///decide if the player has won the game
bool World::IsPlayerWin() {
    return playerWin;
}

///set the player not win the game
void World::setPlayerWin() {
    playerWin =  false;
}

///draw the window target including ship, shield, asteroids and bullets
void World::draw(sf::RenderTarget& target) {
    target.draw(ship.shape);
    target.draw(ship.shield);
    for(std::vector<Asteroids>::iterator asteroid = asteroids.begin(); asteroid != asteroids.end(); ++asteroid)
        target.draw(asteroid->shape);
    for(std::vector<Weapons>::iterator weapon = weapons.begin(); weapon != weapons.end(); ++weapon) {
        target.draw(weapon->shape);
    }
}
