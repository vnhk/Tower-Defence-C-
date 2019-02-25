#include "Road.h"


Road::Road(sf::Vector2i pos)
{
    rect.setSize(sf::Vector2f(35,35));
    rect.setPosition(pos.x-rect.getSize().x/2,pos.y-rect.getSize().y/2);
    rect.setFillColor(sf::Color::Yellow);
}

void Road::setShadow(sf::Vector2i pos)
{
    rect.setPosition(pos.x-rect.getSize().x/2,pos.y-rect.getSize().y/2);
}

void Road::draw(sf::RenderWindow &window)
{
    window.draw(rect);
}
