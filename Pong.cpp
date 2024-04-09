#include "Bat.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
    // Create video mode object
    VideoMode vm(1920, 1080);

    // Create and open window for game
    RenderWindow window(vm, "Pong", Style::Fullscreen);

    int score = 0;
    int lives = 3;

    // Create a bat at the bottom center of screen
    Bat bat(1920 / 2, 1080 - 20);

    // Add ball

    // HUD
    Text hud;
    Font font;
    font.loadFromFile("arcade_ya/ARCADE_I.TTF");
    hud.setFont(font);
    hud.setCharacterSize(75);
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);

    // Clock
    Clock clock;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        // Handle player input
        // Player quits
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        // Press and release arrow keys
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            bat.moveLeft();
        }
        else
        {
            bat.stopLeft();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            bat.moveRight();
        }
        else
        {
            bat.stopRight();
        }

        // Update bat, ball, and HUD
        Time dt = clock.restart();
        bat.update(dt);
        std::stringstream ss;
        ss << "Score: " << score << "   Lives: " << lives;
        hud.setString(ss.str());

        // Draw bat, ball, and HUD
        window.clear();
        window.draw(hud);
        window.draw(bat.getShape());
        window.display();
    }

    return 0;
}