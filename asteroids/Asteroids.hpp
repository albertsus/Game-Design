
#ifndef Asteroids_hpp
#define Asteroids_hpp

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <cmath>

///The asteroid class specifies the behavior of asteroid\n
///Behavior includes generating, handling and updating asteroid entities\n
///The performance of asteroid decides if there is collision between asteroid and weapon or asteroid and ship, the asteroid will split to diffrent level asteroids instead of disappering right away. There are 3 levels in total for the split of asteroid, each with different shapes, colors and speeds
class Asteroids {
public:
    sf::CircleShape shape;
    Asteroids();
    Asteroids(sf::Vector2f position, int slevel);
    void update(float time);
    void drawLevel(int level);
    void UpdatePosition();
    bool IsAlive();
    int getLevel();
    bool IsCollision(sf::Vector2f others);
    void split();
private:
    sf::Vector2f startPosition;
    int level;
    int angle;
    sf::Vector2f velocity;
    sf::Vector2f direction;
    float speed;
    float rotationSpeed;
    bool isAlive;
    float radius;
};
#endif /* Asteroids_hpp */
