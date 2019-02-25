#include "Shot.h"

ShotClass::ShotClass()
{
    texture.loadFromFile("Textures/shot1.png");
    sprite.setTexture(texture);
    texture.loadFromFile("Textures/shot.png");
    ap.update(texture,sf::Vector2u(4,1),600,true,1);
}

ShotClass::~ShotClass()
{

}

void ShotClass::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}