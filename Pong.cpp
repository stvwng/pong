#include "Ball.h"
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
    Ball ball(1920 / 2, 0);

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
        ball.update(dt);
        std::stringstream ss;
        ss << "Score: " << score << "   Lives: " << lives;
        hud.setString(ss.str());

        // handle ball hitting bottom
        if (ball.getPosition().top > window.getSize().y)
        {
            // reverse ball direction
            ball.reboundBottom();
            // remove life
            lives--;
            // check for 0 lives
            if (lives < 1)
            {
                score = 0;
                lives = 3;
            }
        }

        // handle ball hitting top
        if (ball.getPosition().top < 0)
        {
            ball.reboundBatOrTop();
            score++;
        }

        // handle ball hitting sides
        if (ball.getPosition().left < 0 || 
            ball.getPosition().left + ball.getPosition().width > window.getSize().x)
            {
                ball.reboundSides();
            }

        // handle ball hitting bat
        if (ball.getPosition().intersects(bat.getPosition()))
        {
            // intersects function is part of SFML library and is used here to detect a collision
            ball.reboundBatOrTop();
        }

        // Draw bat, ball, and HUD
        window.clear();
        window.draw(hud);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.display();
    }

    return 0;
}