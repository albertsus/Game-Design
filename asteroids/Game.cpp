#include "Game.hpp"
#include "World.hpp"

Game::Game()
{
}

///window implements the event polling and draw different kins of message\n
///Before the start of the game there will be an instructon showing the keyboard use, press "Enter" will skip the instruction and start the game\n
///Other messages include Mission failed and success message\n
///Audio implement infincludes the sound of shooting, the sound when ship crushes, the mission success and fail music respectively
void Game::run() {
    
    sf::Texture startScreen;
    startScreen.loadFromFile("Intro.png");
    sf::Sprite intro(startScreen);
    
    sf::Texture training1;
    training1.loadFromFile("Training1.png");
    sf::Sprite train1(training1);
    
    sf::Font font;
    sf::Text scoreMessage;
    font.loadFromFile("Pixel-Miners.otf");
    scoreMessage.setFont(font);
    scoreMessage.setCharacterSize(50);
    scoreMessage.setFillColor(sf::Color::White);
    scoreMessage.setPosition(20.0f, 25.0f);
    
    sf::Text liveMessage;
    liveMessage.setFont(font);
    liveMessage.setCharacterSize(50);
    liveMessage.setFillColor(sf::Color::White);
    liveMessage.setPosition(WINDOW_WIDTH - 300.0f, 30.f);
    
    sf::Text gameOverMessage;
    gameOverMessage.setFont(font);
    gameOverMessage.setCharacterSize(100);
    gameOverMessage.setFillColor(sf::Color::White);
    gameOverMessage.setPosition(WINDOW_WIDTH / 2 - 520.0f, WINDOW_HEIGHT / 2 - 120.0f);
    
    sf::Text winMessage;
    winMessage.setFont(font);
    winMessage.setCharacterSize(100);
    winMessage.setFillColor(sf::Color::White);
    winMessage.setPosition(WINDOW_WIDTH / 2 - 570.0f, WINDOW_HEIGHT / 2 - 100.0f);
    
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("fire.wav")) {
        std::cout << "no loading the file" << std::endl;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    
    sf::SoundBuffer buffer1;
    if (!buffer1.loadFromFile("bangLarge.wav")) {
        std::cout << "no loading the file" << std::endl;
    }
    sf::Sound sound1;
    sound1.setBuffer(buffer1);
    
    sf::SoundBuffer buffer2;
    if (!buffer2.loadFromFile("levelUp.wav")) {
        std::cout << "no loading the file" << std::endl;
    }
    sf::Sound sound2;
    sound2.setBuffer(buffer2);
    
    
    sf::SoundBuffer buffer3;
    if (!buffer3.loadFromFile("win.wav")) {
        std::cout << "no loading the file" << std::endl;
    }
    sf::Sound sound3;
    sound3.setBuffer(buffer3);
    
    sf::SoundBuffer buffer4;
    if (!buffer4.loadFromFile("lose.wav")) {
        std::cout << "no loading the file" << std::endl;
    }
    sf::Sound sound4;
    sound4.setBuffer(buffer4);
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pytheas Asteroid Field");
    World world;
    sf::Clock clock;
    sf::Event event;
    
    sf::Time t2 = clock.getElapsedTime();
    
    while (t2.asSeconds() < 2.f){
        window.pollEvent(event);
        window.draw(intro);
        window.display();
        t2 = clock.getElapsedTime();
    }
    
    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
        window.clear();
        window.pollEvent(event);
        window.draw(train1);
        window.display();
    }
    
    
    while (window.isOpen())
    {
        scoreMessage.setString("Score:  " + (std::to_string(world.getScore())));
        liveMessage.setString("Lives:  " + std::to_string(world.displayShipLives()));
        gameOverMessage.setString("MISSION FAILED");
        winMessage.setString("MISSION SUCCESS");
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                sound.play();
            }
            if (world.IsPlayerWin()) {
                sound3.play();
                world.setPlayerWin();
            } else if (world.IsPlayerLose()) {
                sound4.play();
                world.setPlayerLose();
            } else {
                if (!world.IsShipAlive()) {
                    sound1.play();
                }
            }
            world.ProcessEvents(event);
        }
        window.clear();
        world.update(1.0/60.f);
        world.draw(window);
        window.draw(scoreMessage);
        window.draw(liveMessage);
        if (world.IsPlayerLose()) {
            window.draw(gameOverMessage);
        } else if (world.IsPlayerWin()) {
            window.draw(winMessage);
        }
        window.display();
        
    }
}



