#include "Npc.h"




void Npcbuf::deleteObj()
{
    for(unsigned i = 0; i < Infantry.size();i++)
    {
        delete Infantry[i];
    }
    for(unsigned i = 0; i < Cavalry.size();i++)
    {
        delete Cavalry[i];
    }
    for(unsigned i = 0; i < Infantry_Arm.size();i++)
    {
        delete Infantry_Arm[i];
    }
    for(unsigned i = 0; i < Cavalry_Arm.size();i++)
    {
        delete Cavalry_Arm[i];
    }
    if(Infantry.size()>0)
        Infantry.clear();
    if(Cavalry.size()>0)
        Cavalry.clear();
    if(Infantry_Arm.size()>0)
        Infantry.clear();
    if(Cavalry_Arm.size()>0)
        Cavalry.clear();
}
void Npcbuf::draw(sf::RenderWindow &window)
{
    for(unsigned i = 0; i < Infantry.size();i++)
    {
        Infantry[i]->draw(window);
    }
    for(unsigned i = 0; i < Cavalry.size();i++)
    {
        Cavalry[i]->draw(window);
    }
    
    for(unsigned i = 0; i < Infantry_Arm.size();i++)
    {
        Infantry_Arm[i]->draw(window);
    }
    for(unsigned i = 0; i < Cavalry_Arm.size();i++)
    {
        Cavalry_Arm[i]->draw(window);
    }
}

bool Npc::isSomeoneAlive()
{
    if(amountOfDeadNpc == amountOfNpc)
        return false;
    return true;    
}

void Npc::kill(Gold &gold)
{
    ++amountOfDeadNpc;
    alive = false;
    gold.addGold(amountOfGold);
}

void Npc::kill()
{
    ++amountOfDeadNpc;
    alive = false;
}

int Npc::amountOfNpc = 0;
int Npc::amountOfDeadNpc = 0;

Npc::Npc()
{
    amountOfNpc++;
    direction = 'r';
    NpcSpeed = 1;
    npcSprite.setPosition(-amountOfNpc*60-500,300);
    point = 0;
    alive = true;
    amountOfGold = 155;
    armor = false;
    greenShape.setSize(sf::Vector2f(5,50));
    redShape.setSize(sf::Vector2f(5,0));
    redShape.setOutlineThickness(2);
    redShape.setOutlineColor(sf::Color::Black);
    greenShape.setFillColor(sf::Color::Green);
    redShape.setFillColor(sf::Color::Red);
    greenShape.setPosition(npcSprite.getPosition().x-10,npcSprite.getPosition().y);
    redShape.setPosition(npcSprite.getPosition().x-10,npcSprite.getPosition().y);
}

Infantry_1::Infantry_1() : Npc()
{
    hp=hpconst=25;
    npcTexture.loadFromFile("Textures/infantry_1.png");
    textureSize.x=npcTexture.getSize().x/4;
    textureSize.y=npcTexture.getSize().y/4;
    npcSprite.setTexture(npcTexture);
    npcAnim.update(npcTexture,sf::Vector2u(4,4),1000,true,0);
}

Cavalry_1::Cavalry_1() : Npc()
{
    hp=hpconst=50;
    npcTexture.loadFromFile("Textures/cavalry_1.png");
    textureSize.x=npcTexture.getSize().x/4;
    textureSize.y=npcTexture.getSize().y/4;
    npcSprite.setTexture(npcTexture);
    npcAnim.update(npcTexture,sf::Vector2u(4,4),1000,true,0);
}

Infantry_2::Infantry_2() : Npc()
{
    hp=hpconst=40;
    npcTexture.loadFromFile("Textures/infantry_2.png");
    textureSize.x=npcTexture.getSize().x/4;
    textureSize.y=npcTexture.getSize().y/4;
    npcSprite.setTexture(npcTexture);
    npcAnim.update(npcTexture,sf::Vector2u(4,4),1000,true,0);
    armor = true;
}

Cavalry_2::Cavalry_2() : Npc()
{
    hp=hpconst=80;
    npcTexture.loadFromFile("Textures/cavalry_2.png");
    textureSize.x=npcTexture.getSize().x/4;
    textureSize.y=npcTexture.getSize().y/4;
    npcSprite.setTexture(npcTexture);
    npcAnim.update(npcTexture,sf::Vector2u(4,4),1000,true,0);
    armor = true;
}



Npc::~Npc()
{
	
}

Infantry_1::~Infantry_1()
{
    amountOfNpc--;
}

Cavalry_2::~Cavalry_2()
{
    amountOfNpc--;
}
Infantry_2::~Infantry_2()
{
    amountOfNpc--;
}

Cavalry_1::~Cavalry_1()
{
    amountOfNpc--;
}



void Npc::draw(sf::RenderWindow &window)
{
    if(alive&&point!=0)
    {
        window.draw(npcSprite);
        window.draw(greenShape);
        window.draw(redShape);
    }
}

void Npc::moveNpc(int x, int y)
{
        npcSprite.move(x,y);
        redShape.move(x,y);
        greenShape.move(x,y);
}

float Npc::getPositionY()
{
        return (float)npcSprite.getPosition().y;
}

float Npc::getPositionX()
{
        return (float)npcSprite.getPosition().x;
}

float Npc::getCenterOfSpritePositionX()
{
    return float(npcSprite.getPosition().x+.5*textureSize.x);
}

float Npc::getCenterOfSpritePositionY()
{
    return float(npcSprite.getPosition().y+.5*textureSize.y)+20;
}

int Npc::getSpeed()
{     
    return NpcSpeed;
}

sf::Vector2f Npc::getPosition()
{
    return npcSprite.getPosition();
}

int Npc::getHp()
{
    return hp;
}

void Npc::setHp(int dmg)
{
    hp-=dmg;
    if(dmg<1)
        return;
    float size = float(hp)/float(hpconst);
    redShape.setSize(sf::Vector2f(5,50-(50*size)));
}

bool Npc::isAlive()
{
    return alive;
}