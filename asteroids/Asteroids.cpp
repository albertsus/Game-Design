

#include "Asteroids.hpp"
#include "Game.hpp"

///default constructor of asteroid class
Asteroids::Asteroids() {
    startPosition.x = -(rand() % 300);
    startPosition.y = -(rand() % 300);
    shape.setPosition(startPosition);
    level = 1;
    drawLevel(level);
    angle = rand() % 360;
    direction = sf::Vector2f(cos(angle * (3.14159f/180.f)), sin(angle * (3.14159f/180.f)));
    isAlive = true;
    rotationSpeed = 0.1f;
}

///basic constructor of astroid class
Asteroids::Asteroids(sf::Vector2f position, int slevel) {
    level=slevel;
    angle = rand() % 360;
    direction = sf::Vector2f(cos(angle * (3.14159f/180.f)), sin(angle * (3.14159f/180.f)));
    isAlive = true;
    shape.setPosition(position);
    rotationSpeed = 0.15f;
    drawLevel(level);
}

///three different asteroid levels are defined here with different shapes, colors and speeds
void Asteroids::drawLevel(int level) {
    if (level == 1) {
        shape.setPointCount(10);
        radius = 150.0f;
        speed = 10.0f;
        shape.setFillColor(sf::Color::Red);
    } else if (level == 2) {
        shape.setPointCount(8);
        radius = 100.0f;
        speed = 30.0f;
        shape.setFillColor(sf::Color::Blue);
    } else if (level == 3) {
        shape.setPointCount(6);
        radius = 50.0f;
        speed = 40.0f;
        shape.setFillColor(sf::Color::Green);
    }else {
        return;
    }
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
}

///update the asteroid class event
void Asteroids::update(float time) {
    if (isAlive) {
        sf::Vector2f distance = speed * time * direction;
        shape.move(distance);
        shape.rotate(rotationSpeed);
        UpdatePosition();
    }
}

///decide if the asteroid is alive
bool Asteroids::IsAlive() {
    return level < 4;
}

///get the current level of asteroid
int Asteroids::getLevel() {
    return level;
}

///the asteroid will split to diffrent level asteroids instead of disappering right away
void Asteroids::split() {
    if(level >= 4) return;
    level++;
    isAlive = (level < 4);
    drawLevel(level);
}

///detect out of bound and move the asteroid back to screen
void Asteroids::UpdatePosition() {
    sf::Vector2f position = shape.getPosition();
    if (position.x < -250) {
        position.x = WINDOW_WIDTH;
    } else if (position.x > WINDOW_WIDTH) {
        position.x = 0.0f;
    }
    if (position.y < -250) {
        position.y = WINDOW_HEIGHT;
    } else if (position.y > WINDOW_HEIGHT) {
        position.y = 0.0f;
    }
    shape.setPosition(position);
}

///The performance of asteroid decides if there is collision between asteroid and weapon or asteroid and ship
bool Asteroids::IsCollision(sf::Vector2f others) {
    float distance = ((shape.getPosition().x - others.x) * (shape.getPosition().x - others.x)) +
    ((shape.getPosition().y - others.y) * (shape.getPosition().y - others.y));
    return (distance <= (radius * radius));
}
