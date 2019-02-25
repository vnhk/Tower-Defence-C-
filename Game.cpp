#include "Game.h"

void game(int id, sf::RenderWindow &window)
{
    std::fstream f;
    std::string str = "";
    int amountOfCavalry[2];
    int amountOfInfantry[2];
    int amountOfGold = 0;
    int amountOfLives = 0;
    std::string name = "";

    TowerPlace towerShadow(sf::Mouse::getPosition());
    std::ostringstream t;
    t << id;
    std::string filename = "Files/Levels/Level";
    filename += t.str() + "/settings.txt";
    f.open(filename.c_str(), std::ios::in);

    if (f.is_open())
    {
        getline(f, str);
        name = str;
        getline(f, str);
        std::istringstream tmp(str);
        tmp >> amountOfInfantry[0];
        getline(f, str);
        tmp.str("");
        tmp.str(str);
        tmp >> amountOfCavalry[0];
        getline(f, str);
        tmp.str("");
        tmp.str(str);
        tmp >> amountOfInfantry[1];
        getline(f, str);
        tmp.str("");
        tmp.str(str);
        tmp >> amountOfCavalry[1];
        getline(f, str);
        tmp.str("");
        tmp.str(str);
        tmp >> amountOfGold;
        getline(f, str);
        tmp.str("");
        tmp.str(str);
        tmp >> amountOfLives;
        f.close();
    }

    filename = "Files/Levels/Level";
    filename += t.str() + "/placeToPointsEditor.txt";
    f.open(filename.c_str(), std::ios::in);
    int n;
    if (f.is_open())
    {
        getline(f, str);
        std::istringstream tmp1(str);
        tmp1 >> n;
        f.close();
    }
    Game gameRun(name, amountOfInfantry, amountOfCavalry, n, amountOfLives);

    load(filename.c_str(), gameRun, 'P');

    filename = "Files/Levels/Level";
    filename += t.str() + "/placeToRoadEditor.txt";
    load(filename.c_str(), gameRun, 'R');

    Gold gold;
    gold.setGold(amountOfGold);
    Animation goldAnimation(gold.goldAnim);

    HUD hud(window);
    gameRun.setMapTexture(id);
    std::vector<Animation *> npcAnimation;
    std::vector<T_Arrow *> ArrowTower;        //0
    std::vector<T_Gun *> GunTower;            //1
    std::vector<T_Cannon *> CannonTower;      //2
    std::vector<T_Supp *> SuppTower;          //3
    std::vector<sf::Vector2i> TowersPosition; //4

    int prize[] = {PT, PG, PC, PS};
    struct Npcbuf npc;
    for (int y = 0; y < gameRun.amountOfInfantry[0]; ++y)
    {
        npc.Infantry.push_back(new Infantry_1());
        npcAnimation.push_back(new Animation(npc.Infantry[y]->npcAnim));
    }
    for (int y = 0; y < gameRun.amountOfCalvary[0]; ++y)
    {
        npc.Cavalry.push_back(new Cavalry_1());
        npcAnimation.push_back(new Animation(npc.Cavalry[y]->npcAnim));
    }
    for (int y = 0; y < gameRun.amountOfInfantry[1]; ++y)
    {
        npc.Infantry_Arm.push_back(new Infantry_2());
        npcAnimation.push_back(new Animation(npc.Infantry_Arm[y]->npcAnim));
    }
    for (int y = 0; y < gameRun.amountOfCalvary[1]; ++y)
    {
        npc.Cavalry_Arm.push_back(new Cavalry_2());
        npcAnimation.push_back(new Animation(npc.Cavalry_Arm[y]->npcAnim));
    }

    //wlasciwa gra
    window.setFramerateLimit(55);
    window.setTitle(gameRun.getName());
    goldAnimation.Start();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                lvlUpTower(ArrowTower, GunTower, CannonTower, SuppTower, gold, sf::Mouse::getPosition(window));
            }
            if (event.type == sf::Event::Closed)
            {
                npc.deleteObj();
                clearVectors(npcAnimation, ArrowTower, GunTower, CannonTower, SuppTower, TowersPosition);
                return;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                Tower T;
                T.defaultSelectedTower();
                hud.active = true;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (sf::Mouse::getPosition(window).x < 1000)
                {
                    if (!gameRun.isOnBlockedFile(sf::Mouse::getPosition(window), TowersPosition))
                    {
                        unsigned t = hud.getSelectedTower();
                        if (t == 0)
                        {
                            if (gold.isEnoughGold(prize[0]))
                            {
                                ArrowTower.push_back(new T_Arrow(sf::Mouse::getPosition(window)));
                                TowersPosition.push_back(sf::Mouse::getPosition(window));
                                gold.subGold(prize[0]);
                            }
                        }
                        else if (t == 1)
                        {
                            if (gold.isEnoughGold(prize[1]))
                            {
                                GunTower.push_back(new T_Gun(sf::Mouse::getPosition(window)));
                                TowersPosition.push_back(sf::Mouse::getPosition(window));
                                gold.subGold(prize[1]);
                            }
                        }
                        else if (t == 2)
                        {
                            if (gold.isEnoughGold(prize[2]))
                            {
                                CannonTower.push_back(new T_Cannon(sf::Mouse::getPosition(window)));
                                TowersPosition.push_back(sf::Mouse::getPosition(window));
                                gold.subGold(prize[2]);
                            }
                        }
                        else if (t == 3)
                        {
                            if (gold.isEnoughGold(prize[3]))
                            {
                                SuppTower.push_back(new T_Supp(sf::Mouse::getPosition(window)));
                                TowersPosition.push_back(sf::Mouse::getPosition(window));
                                gold.subGold(prize[3]);
                            }
                        }
                    }
                    else
                    {
                        for (unsigned i = 0; i < CannonTower.size(); ++i)
                            if (CannonTower[i]->selectTower(sf::Mouse::getPosition(window)))
                                hud.active = false;
                        for (unsigned i = 0; i < SuppTower.size(); ++i)
                            if (SuppTower[i]->selectTower(sf::Mouse::getPosition(window)))
                                hud.active = false;
                        for (unsigned i = 0; i < GunTower.size(); ++i)
                            if (GunTower[i]->selectTower(sf::Mouse::getPosition(window)))
                                hud.active = false;
                        for (unsigned i = 0; i < ArrowTower.size(); ++i)
                            if (ArrowTower[i]->selectTower(sf::Mouse::getPosition(window)))
                                hud.active = false;
                    }
                }
                else
                {
                    hud.click(sf::Mouse::getPosition(window), towerShadow);
                }
            }
        }
        goldAnimation.Update(gold.goldSprite);
        window.clear();
        gameRun.draw(window);
        hud.draw(window);
        gold.draw(window);

        for (unsigned i = 0; i < ArrowTower.size(); ++i)
        {
            ArrowTower[i]->draw(window);
            ArrowTower[i]->attack(npc,gold);
        }

        for (unsigned i = 0; i < CannonTower.size(); ++i)
        {
            CannonTower[i]->draw(window);
            CannonTower[i]->attack(npc, gold);
        }

        for (unsigned i = 0; i < GunTower.size(); ++i)
        {
            GunTower[i]->draw(window);
            GunTower[i]->attack(npc, gold);
        }

        for (unsigned i = 0; i < SuppTower.size(); ++i)
        {
            SuppTower[i]->draw(window);
            SuppTower[i]->attack(npc, gold);
        }

        for (int i = 0; i < gameRun.amountOfInfantry[0]; ++i)
        {
            gameRun.road(npc.Infantry[i], npcAnimation[i]);
        }
        for (int i = 0; i < gameRun.amountOfCalvary[0]; ++i)
        {
            gameRun.road(npc.Cavalry[i], npcAnimation[i + gameRun.amountOfInfantry[0]]);
        }
        for (int i = 0; i < gameRun.amountOfInfantry[1]; ++i)
        {
            gameRun.road(npc.Infantry_Arm[i],
                         npcAnimation[i + gameRun.amountOfInfantry[0] + gameRun.amountOfCalvary[0]]);
        }
        for (int i = 0; i < gameRun.amountOfCalvary[1]; ++i)
        {
            gameRun.road(npc.Cavalry_Arm[i],
                         npcAnimation[i + gameRun.amountOfInfantry[0] + gameRun.amountOfCalvary[0] + gameRun.amountOfInfantry[1]]);
        }
        npc.draw(window);

        towerShadow.setShadow(sf::Mouse::getPosition(window));
        if (!gameRun.isOnBlockedFile(sf::Mouse::getPosition(window), TowersPosition))
            towerShadow.draw(window, hud.getSelectedTower());


        if(!Npc::isSomeoneAlive())
        {
            gameRun.setVictory(true);
        }

        if (gameRun.gameStatus(window,ArrowTower,GunTower,CannonTower,SuppTower,hud) == 0)
        {
            npc.deleteObj();
            clearVectors(npcAnimation, ArrowTower, GunTower, CannonTower, SuppTower, TowersPosition);
            return;
        }
        window.display();
    }
}
