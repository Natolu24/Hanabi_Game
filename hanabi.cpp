#include <SFML/Graphics.hpp>
#include "application.hpp"

int main()
{
    sf::RenderWindow window;
    Application app(window);
    app.run();
    return 0;
}
