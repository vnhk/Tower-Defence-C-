#include "LevelsObject.h"

bool LevelsObject::isMouseOn(sf::Vector2i mouse)
{
    if(active==false)
        return false;
    if(levelSprite.getGlobalBounds().contains(mouse.x,mouse.y))
        return true;
    else
        return false;
}

LevelsObject::LevelsObject(int id)
{
    this->id = id;
    std::ostringstream t;
    t<<id;
    levelTexture.loadFromFile("Textures/Menu/level"+t.str()+".png");
    levelSprite.setTexture(levelTexture);
    active = false;
    levelSprite.setPosition(sf::Vector2f(650-.5*levelTexture.getSize().x,600-levelTexture.getSize().y-25));
}
LevelsObject::~LevelsObject()
{

}

void LevelsObject::activate(bool y)
{
    active = y;
}

void LevelsObject::draw(sf::RenderWindow &window)
{
    if(active)
        window.draw(levelSprite);
}

sf::Vector2u LevelsObject::getTextureSize()
{
    return levelTexture.getSize();
}