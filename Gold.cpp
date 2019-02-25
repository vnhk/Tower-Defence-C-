#include "Gold.h"
#include <iostream>

Gold::Gold()
{
    goldTexture.loadFromFile("Textures/Gold.png");
    goldSprite.setPosition(600,0);
    goldSprite.setTexture(goldTexture);
    goldSprite.setTextureRect(sf::IntRect(0,0,68,80));
    font.loadFromFile("Files/Fonts/Gold/28 Days Later.ttf");
    amountOfGold.setFont(font);
    amountOfGold.setCharacterSize(50);
    amountOfGold.setPosition(680,0);
    amountOfGold.setFillColor(sf::Color::Black);
    goldAnim.update(goldTexture,sf::Vector2u(6,1),700,false,0);    
}

bool Gold::isEnoughGold(int amount)
{
    if(this->amount - amount >= 0)
        return true;
    else
        return false;
}

void Gold::draw(sf::RenderWindow &window)
{
    window.draw(amountOfGold);
    window.draw(goldSprite);
}

void Gold::addGold(int amount)
{
    this->amount+=amount;
    if (this->amount > MAX_GOLD)
        this->amount = MAX_GOLD;
    updateGold();
}

int Gold::getGold()
{
    return amount;
}

void Gold::subGold(int amount)
{
    this->amount -= amount;
    if (this->amount < 0)
        this->amount = 0;
    updateGold();
}

void Gold::setGold(int amount)
{
    if (this->amount > MAX_GOLD)
        this->amount = MAX_GOLD;
    
    this->amount = amount;
    updateGold();
}


Gold::~Gold()
{
}

void Gold::updateGold()
{
    std::ostringstream g;
    g << amount;
    amountOfGold.setString(g.str());
}
