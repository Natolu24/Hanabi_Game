#include "application.hpp"

Application::Application(sf::RenderWindow& window) : mWindow(window), mMenu(window, mFont), mGame(window, mFont) {
    // Load global font for the application
    if (!mFont.loadFromFile("assets/FreeMono.ttf"))
    {
        std::cout << "Error while loading font" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Application::run()
{
    // Create window
    mWindow.create(sf::VideoMode(1200, 675), "Hanabi");
    // Application loop
    while (mWindow.isOpen())
    {
        // Handle events
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            // Quit app when closing window
            if (event.type == sf::Event::Closed)
            {
                mWindow.close();
                return;
            }
            // Otherwise let the event be handled by the current scene
            switch(mState)
            {
                case Scenes::MENU:
                    mMenu.handleEvent(event);
                    break;
                case Scenes::GAME:
                    mGame.handleEvent(event);
                    break;
            }
        }
        // Draw the current scene
        switch(mState)
        {
            case Scenes::MENU:
                mMenu.draw();
                break;
            case Scenes::GAME:
                mGame.draw();
                break;
        }
    }
}