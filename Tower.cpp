#include "Tower.h"

int Tower::Towers;
int Tower::selectedTower;

int Tower::getPrize()
{
    return valueOfTurret;
}

bool Tower::improve(Gold &gold,sf::Vector2i pos)
{
    if (towerLvl == 3)
        return false;
    if (selectedTower != id)
        return false;
    if (!gold.isEnoughGold(valueOfTurret))
        return false;

    if(!lvlUpSprite.getGlobalBounds().contains(pos.x,pos.y))
        return false;       

    gold.subGold(valueOfTurret);
    gold.updateGold();

    towerLvl++;
    dmg *= 1.4;
    restTime *= 0.9;
    setInformation();
    setTexture();

    return true;
}

void Tower::setInformation()
{
    if (goodForArmEne)
        informationText.setString(name + "\nRange: " + std::to_string(range) +
                                  "\nDamage: " + std::to_string(dmg) + "\nReload: " + (std::to_string(restTime)).substr(0, 4) +
                                  "\nStrong aganist:\n-Armored enemies\n\nLevel: "+std::to_string(towerLvl)+"/3");
    else
        informationText.setString(name + "\nRange: " + std::to_string(range) +
                                  "\nDamage: " + std::to_string(dmg) + "\nReload: " + (std::to_string(restTime)).substr(0, 4) +
                                  "\nWeak aganist:\n-Armored enemies\n\nLevel: "+std::to_string(towerLvl)+"/3");
}

T_Arrow::T_Arrow(sf::Vector2i mouse) : Tower(sf::Vector2i(mouse))
{
    name = "Arrow Tower";
    restTime = 4.0;
    texture.loadFromFile("Textures/Towers/ArrowTower.png");
    texture1.loadFromFile("Textures/Towers/ArrowTowerUp1.png");
    texture2.loadFromFile("Textures/Towers/ArrowTowerUp2.png");
    range = 70;
    dmg = 6;
    afterTowerConstructor();
}

T_Gun::T_Gun(sf::Vector2i mouse) : Tower(sf::Vector2i(mouse))
{
    name = "Gun Tower";
    restTime = 5.0;
    texture.loadFromFile("Textures/Towers/GunTower.png");
    texture1.loadFromFile("Textures/Towers/GunTowerUp1.png");
    texture2.loadFromFile("Textures/Towers/GunTowerUp2.png");
    range = 80;
    dmg = 7;
    goodForArmEne = true;
    afterTowerConstructor();
}

T_Supp::T_Supp(sf::Vector2i mouse) : Tower(sf::Vector2i(mouse))
{
    name = "Support Tower";
    texture.loadFromFile("Textures/Towers/SuppTower.png");
    texture1.loadFromFile("Textures/Towers/SuppTowerUp1.png");
    texture2.loadFromFile("Textures/Towers/SuppTowerUp2.png");
    range = 50;
    dmg = 15;
    restTime = 3.0;
    afterTowerConstructor();
}

T_Cannon::T_Cannon(sf::Vector2i mouse) : Tower(sf::Vector2i(mouse))
{
    name = "Cannon Tower";
    texture.loadFromFile("Textures/Towers/CannonTower.png");
    texture1.loadFromFile("Textures/Towers/CannonTowerUp1.png");
    texture2.loadFromFile("Textures/Towers/CannonTowerUp2.png");
    range = 90;
    goodForArmEne = true;
    dmg = 12;
    restTime = 5.0;
    afterTowerConstructor();
}

void Tower::setTexture()
{
    switch (towerLvl)
    {
    case 1:
        towerSprite.setTexture(texture);
        break;
    case 2:
        towerSprite.setTexture(texture1);
        break;
    case 3:
        towerSprite.setTexture(texture2);
    }
    if (!set)
    {
        towerSprite.setPosition(mouse.x - texture.getSize().x / 2, mouse.y - texture.getSize().y / 2);
        RangeSprite.setPosition(mouse.x - range, mouse.y - range);
    }
}


void Tower::attack(struct Npcbuf &npc, Gold &gold)
{
    time_t start;
    time(&start);
    bool isOnRange = false;

    if (difftime(start, lastAttack) < restTime)
    {
        return;
    }
    if (difftime(start, lastCheck) < 0.2)
    {
        return;
    }
    reload = false;
    unsigned j = 0;
    unsigned i = 0;
    unsigned k = 0;
    unsigned l = 0;
    bool inf[2] = {false, false};
    bool calv[2] = {false, false};
    for (i = 0; i < npc.Infantry.size(); i++)
    {
        if (towerRange(npc.Infantry[i]))
        {
            isOnRange = true;
            inf[0] = true;
            break;
        }
    }
    if (isOnRange == false)
        for (j = 0; j < npc.Cavalry.size(); j++)
        {
            if (towerRange(npc.Cavalry[j]))
            {
                calv[0] = true;
                isOnRange = true;
                break;
            }
        }
    if (isOnRange == false)
        for (k = 0; k < npc.Infantry_Arm.size(); k++)
        {
            if (towerRange(npc.Infantry_Arm[k]))
            {
                isOnRange = true;
                inf[1] = true;
                break;
            }
        }
    if (isOnRange == false)
        for (l = 0; l < npc.Cavalry_Arm.size(); l++)
        {
            if (towerRange(npc.Cavalry_Arm[l]))
            {
                calv[1] = true;
                isOnRange = true;
                break;
            }
        }
    if (isOnRange)
    {
        shotAnimation.Start();
        reload = true;
        if (inf[0])
        {
            npc.Infantry[i]->setHp(dmg);
            shot.sprite.setPosition(npc.Infantry[i]->getPosition());
            if (npc.Infantry[i]->getHp() <= 0)
            {
                npc.Infantry[i]->kill(gold);
            }
        }
        else if (calv[0])
        {
            npc.Cavalry[j]->setHp(dmg);
            shot.sprite.setPosition(npc.Cavalry[j]->getPosition());
            if (npc.Cavalry[j]->getHp() <= 0)
            {
                npc.Cavalry[j]->kill(gold);
            }
        }
        else if (inf[1])
        {
            if (goodForArmEne)
                npc.Infantry_Arm[k]->setHp(dmg * 1.1);
            else
                npc.Infantry_Arm[k]->setHp(0.7 * dmg);
            shot.sprite.setPosition(npc.Infantry_Arm[k]->getPosition());
            if (npc.Infantry_Arm[k]->getHp() <= 0)
            {
                npc.Infantry_Arm[k]->kill(gold);
            }
        }
        else if (calv[1])
        {
            if (goodForArmEne)
                npc.Cavalry_Arm[l]->setHp(dmg * 1.1);
            else
                npc.Cavalry_Arm[l]->setHp(0.7 * dmg);
            shot.sprite.setPosition(npc.Cavalry_Arm[l]->getPosition());
            if (npc.Cavalry_Arm[l]->getHp() <= 0)
            {
                npc.Cavalry_Arm[l]->kill(gold);
            }
        }
    
        time(&lastAttack);
        return;
    }
    time(&lastCheck);
}

bool Tower::towerRange(Npc *npc)
{
    if (npc->isAlive() == false)
        return false;

    if ((RangeSprite.getGlobalBounds()).intersects(npc->npcSprite.getGlobalBounds()))
    {
        return true;
    }
    if ((npc->npcSprite.getGlobalBounds()).intersects(RangeSprite.getGlobalBounds()))
    {
        return true;
    }

    return false;
}

void Tower::draw(sf::RenderWindow &window)
{
    if (selectedTower == id)
    {
        window.draw(RangeSprite);
        window.draw(informationBackground);
        window.draw(informationText);
        window.draw(lvlUpSprite);
    }
    window.draw(towerSprite);
    if(reload)
    {
        shotAnimation.Update(shot.sprite);
        if(shotAnimation.getOn())
            window.draw(shot.sprite);
    }
    
}

TowerPlace::TowerPlace(sf::Vector2i pos)
{
    towerShadowTexture[0].loadFromFile("Textures/Towers/ArrowTower.png");
    towerShadowTexture[1].loadFromFile("Textures/Towers/GunTower.png");
    towerShadowTexture[2].loadFromFile("Textures/Towers/CannonTower.png");
    towerShadowTexture[3].loadFromFile("Textures/Towers/SuppTower.png");
    towerShadow.setPosition(pos.x - towerShadowTexture[0].getSize().x / 2, pos.y - towerShadowTexture[0].getSize().y / 2);
}

void TowerPlace::setShadow(sf::Vector2i pos)
{
    towerShadow.setPosition(pos.x - towerShadowTexture[0].getSize().x / 2, pos.y - towerShadowTexture[0].getSize().y / 2);
}

void TowerPlace::setTexture(int id)
{
    towerShadow.setTexture(towerShadowTexture[id]);
}

void TowerPlace::draw(sf::RenderWindow &window, int id)
{
    if (id != -1)
        window.draw(towerShadow);
}

bool Tower::selectTower(sf::Vector2i mouse)
{
    if (towerSprite.getGlobalBounds().contains(mouse.x, mouse.y))
    {
        selectedTower = id;
        return true;
    }
    return false;
}
T_Arrow::~T_Arrow()
{
}

T_Gun::~T_Gun()
{
}

T_Supp::~T_Supp()
{
}

T_Cannon::~T_Cannon()
{
}

Tower::Tower(sf::Vector2i mouse)
{
    this->mouse.x = mouse.x;
    this->mouse.y = mouse.y;
    shotAnimation.setParameters(shot.ap);
    reload = false;
    towerLvl = 1;
    goodForArmEne = false;
    lastAttack = 0.0;
    lastCheck = 0.0;
    id = (Towers++);
    font.loadFromFile("Files/Fonts/Sallita.ttf");
    informationText.setFont(font);
    informationText.setCharacterSize(50);
    informationText.setFillColor(sf::Color::White);
    informationBackground.setFillColor(sf::Color::Black);
    informationBackground.setSize(sf::Vector2f(300, 600));
    informationBackground.setPosition(1000, 0);
    informationText.setPosition(1010, 10);
    set = false;
}

Tower::~Tower()
{
}

Tower::Tower()
{
}

void Tower::defaultSelectedTower()
{
    selectedTower = -1;
}
void Tower::afterTowerConstructor()
{
    RangeSprite.setRadius(range);
    towerSprite.setTexture(texture);
    towerSprite.setPosition(mouse.x - texture.getSize().x / 2, mouse.y - texture.getSize().y / 2);
    RangeSprite.setPosition(mouse.x - range, mouse.y - range);
    lvlUpTexture.loadFromFile("Textures/Towers/upArrow.png");
    lvlUpSprite.setTexture(lvlUpTexture);
    lvlUpSprite.setPosition(1200,490);
    RangeSprite.setFillColor(sf::Color(0, 0, 0, 70));
    RangeSprite.setOutlineThickness(5);
    RangeSprite.setOutlineColor(sf::Color(0, 0, 0, 200));
    setInformation();
}