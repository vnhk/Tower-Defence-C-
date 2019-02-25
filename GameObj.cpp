#include "Game.h"

void Game::draw(sf::RenderWindow &window)
{
    window.draw(mapSprite);
    window.draw(amountOfLivesText);
    window.draw(heartSprite);
}

void Game::setVictory(bool v)
{
    victory = v;
}

void Game::setMapTexture(int id)
{
    std::ostringstream t;
    t << id;
    std::string newString = t.str() + ".png";

    mapTexture.loadFromFile("Textures/Maps/map" + newString);
    mapSprite.setTexture(mapTexture);
}

std::string Game::getName()
{
    return name;
}

bool Game::isOnBlockedFile(sf::Vector2i pos, std::vector<sf::Vector2i> TowersPosition)
{
    if (pos.x < 75 || pos.y < 75)
        return true;
    if (pos.x > 1000)
        return true;

    for (unsigned i = 0; i < roadPosition.size(); ++i)
    {
        if (pos.x >= roadPosition[i].x - RoadSize && pos.x <= roadPosition[i].x + RoadSize)
        {
            if (pos.y >= roadPosition[i].y - RoadSize && pos.y <= roadPosition[i].y + RoadSize)
                return true;
        }
    }

    for (unsigned i = 0; i < TowersPosition.size(); ++i)
    {
        if (pos.x >= TowersPosition[i].x - TowerSize && pos.x <= TowersPosition[i].x + TowerSize)
        {
            if (pos.y >= TowersPosition[i].y - TowerSize && pos.y <= TowersPosition[i].y + TowerSize)
                return true;
        }
    }

    return false;
}

void Game::road(Npc *npc, Animation *animation)
{
    if (npc->isAlive() == false)
        return;

    if ((unsigned)npc->point >= points.size())
    {
        subLives();
        npc->kill();
        return;
    }

    float x = npc->getCenterOfSpritePositionX();
    float y = npc->getCenterOfSpritePositionY();

    int speed = npc->getSpeed();

    if (x < points[npc->point].x)
    {
        npc->moveNpc(speed, 0);
        animation->changeAnimation(2);
    }
    else if (x > points[npc->point].x)
    {
        npc->moveNpc(-speed, 0);
        animation->changeAnimation(1);
    }
    if (y < points[npc->point].y)
    {
        npc->moveNpc(0, speed);
        animation->changeAnimation(0);
    }
    else if (y > points[npc->point].y)
    {
        npc->moveNpc(0, -speed);
        animation->changeAnimation(3);
    }

    if (x > points[npc->point].x - 20 && x < points[npc->point].x + 20 && y > points[npc->point].y - 20 && y < points[npc->point].y + 20)
    {
        npc->point++;
    }
    animation->Update(npc->npcSprite);
}

void Game::setName(std::string name)
{
    this->name = name;
}

Game::Game(std::string name, int *aoi, int *aoc, int aop, int aol)
{
    this->name = name;
    amountOfInfantry[0] = aoi[0];
    amountOfCalvary[0] = aoc[0];
    amountOfInfantry[1] = aoi[1];
    amountOfCalvary[1] = aoc[1];
    amountOfPoints = aop;
    amountOfLives = amountOfLivesR = aol;
    defeat = false;
    victory = false;
    amountOfLivesText.setCharacterSize(30);
    amountOfLivesText.setFillColor(sf::Color::Red);
    font.loadFromFile("Files/Fonts/Gold/28 Days Later.ttf");
    amountOfLivesText.setFont(font);
    setTextString();
    heartTexture.loadFromFile("Textures/Heart.png");
    heartSprite.setTexture(heartTexture);
    heartSprite.setPosition(0, 0);
    amountOfLivesText.setPosition(heartTexture.getSize().x + 5, 0);
}

void Game::subLives()
{
    if (amountOfLives > 0)
        --amountOfLives;
    if (amountOfLives == 0)
        defeat = true;
    setTextString();
}

void Game::setTextString()
{
    amountOfLivesText.setString(std::to_string(amountOfLives));
}

Game::Game()
{
    defeat = false;
    victory = false;
}

Game::~Game()
{
    if (points.size() > 0)
        points.clear();
}

int Game::gameStatus(sf::RenderWindow &window, std::vector<T_Arrow *> ArrowTower,
                     std::vector<T_Gun *> GunTower,
                     std::vector<T_Cannon *> CannonTower,
                     std::vector<T_Supp *> SuppTower,
                     HUD hud)
{
    if (defeat || victory)
    {
        sf::RectangleShape background(sf::Vector2f(window.getSize()));
        sf::Sprite okSprite;
        sf::Texture okTexture;
        sf::Font fontWD;
        fontWD.loadFromFile("Files/Fonts/New Walt Disney UI.ttf");
        okTexture.loadFromFile("Textures/okTexture.png");
        sf::Text finalText("Defeat...", fontWD, 100);
        okTextureHover.loadFromFile("Textures/okTextureHover.png");
        okSprite.setTexture(okTexture);
        okSprite.setPosition(window.getSize().x / 2 - okTexture.getSize().x / 2, window.getSize().y / 2 - okTexture.getSize().y / 2 + 100);

        if (defeat)
        {
            background.setFillColor(sf::Color(124, 10, 2, 200));
            finalText.setFillColor(sf::Color::Red);
            finalText.setPosition(window.getSize().x / 2 - finalText.getLocalBounds().width / 2, 5);
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (okSprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                    {
                        okSprite.setTexture(okTextureHover);
                        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        okSprite.setTexture(okTexture);
                    }
                    if (event.type == sf::Event::Closed)
                    {
                        return 0;
                    }
                }
                window.clear();
                draw(window);
                hud.draw(window);
                for (unsigned i = 0; i < ArrowTower.size(); ++i)
                    ArrowTower[i]->draw(window);

                for (unsigned i = 0; i < CannonTower.size(); ++i)
                    CannonTower[i]->draw(window);

                for (unsigned i = 0; i < GunTower.size(); ++i)
                    GunTower[i]->draw(window);

                for (unsigned i = 0; i < SuppTower.size(); ++i)
                    SuppTower[i]->draw(window);
                window.draw(background);
                window.draw(okSprite);
                window.draw(finalText);
                window.display();
            }
            return 0;
        }
        else if (victory)
        {
            int stars;
            background.setFillColor(sf::Color(199,234, 70, 200));
            finalText.setString("VICTORY!");
            finalText.setFillColor(sf::Color::White);
            finalText.setPosition(window.getSize().x / 2 - finalText.getLocalBounds().width / 2, 5);
            if (amountOfLives > 0.9 * amountOfLivesR)
                stars = 3;
            else if (amountOfLives > 0.5 * amountOfLivesR)
                stars = 2;
            else
                stars = 1;
            sf::Texture starTexture;
            sf::Sprite starSprite[stars];
            starTexture.loadFromFile("Textures/starTexture.png");
            for (int i = 0; i < stars; i++)
            {
                starSprite[i].setTexture(starTexture);
                starSprite[i].setPosition((i + 1) * window.getSize().x / 4 - starTexture.getSize().x / 2, 100);
            }

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (okSprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                    {
                        okSprite.setTexture(okTextureHover);
                        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        okSprite.setTexture(okTexture);
                    }
                    if (event.type == sf::Event::Closed)
                    {
                        return 0;
                    }
                }
                window.clear();
                draw(window);
                hud.draw(window);
                for (unsigned i = 0; i < ArrowTower.size(); ++i)
                    ArrowTower[i]->draw(window);

                for (unsigned i = 0; i < CannonTower.size(); ++i)
                    CannonTower[i]->draw(window);

                for (unsigned i = 0; i < GunTower.size(); ++i)
                    GunTower[i]->draw(window);

                for (unsigned i = 0; i < SuppTower.size(); ++i)
                    SuppTower[i]->draw(window);
                window.draw(background);
                window.draw(okSprite);
                window.draw(finalText);
                for (int i = 0; i < stars; i++)
                    window.draw(starSprite[i]);
                window.display();
            }
            return 0;
        }
    }
    return 1;
}