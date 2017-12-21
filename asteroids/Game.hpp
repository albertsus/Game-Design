#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>


const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 1600;

///game class handles the render window, load all kinds of text, image and audio files\n
///window implements the event polling and draw different kins of message\n
///Before the start of the game there will be an instructon showing the keyboard use, press "Enter" will skip the instruction and start the game\n
///Other messages include Mission failed and success message\n
///Audio implement infincludes the sound of shooting, the sound when ship crushes, the mission success and fail music respectively

class Game {
    
public:
    Game();
    void run();
    void quit();
private:
    sf::RenderWindow window;
};

#endif
