#include "Game.h"

template <typename T> void deleteDynObjFromVect(std::vector<T *> &x)
{
    for (unsigned i = 0; i < x.size(); i++)
    {
        delete x[i];
    }
}

void clearVectors(std::vector<Animation *> &npcAnimation,
                  std::vector<T_Arrow *> &ArrowTower,
                  std::vector<T_Gun *> &GunTower,
                  std::vector<T_Cannon *> &CannonTower,
                  std::vector<T_Supp *> &SuppTower,
                  std::vector<sf::Vector2i> &TowersPosition)
{
    if (npcAnimation.size() > 0)
    {
        deleteDynObjFromVect<Animation>(npcAnimation);
        npcAnimation.clear();
    }
    if (ArrowTower.size() > 0)
    {
        deleteDynObjFromVect<T_Arrow>(ArrowTower);
        ArrowTower.clear();
    }
    if (GunTower.size() > 0)
    {
        deleteDynObjFromVect<T_Gun>(GunTower);
        GunTower.clear();
    }
    if (CannonTower.size() > 0)
    {
        deleteDynObjFromVect<T_Cannon>(CannonTower);
        CannonTower.clear();
    }
    if (SuppTower.size() > 0)
    {
        deleteDynObjFromVect<T_Supp>(SuppTower);
        SuppTower.clear();
    }
    if (TowersPosition.size() > 0)
    {
        TowersPosition.clear();
    }
}

void lvlUpTower(
    std::vector<T_Arrow *> &ArrowTower,
    std::vector<T_Gun *> &GunTower,
    std::vector<T_Cannon *> &CannonTower,
    std::vector<T_Supp *> &SuppTower,
    Gold &gold, sf::Vector2i pos)
{
    for (unsigned i = 0; i < CannonTower.size(); ++i)
        if (CannonTower[i]->improve(gold, pos))
            return;
    for (unsigned i = 0; i < SuppTower.size(); ++i)
        if (SuppTower[i]->improve(gold, pos))
            return;
    for (unsigned i = 0; i < GunTower.size(); ++i)
        if (GunTower[i]->improve(gold, pos))
            return;
    for (unsigned i = 0; i < ArrowTower.size(); ++i)
        if (ArrowTower[i]->improve(gold, pos))
            return;
}

void load(std::string filename, Game &game, char type)
{
    std::fstream f;
    std::string str;
    f.open(filename.c_str(), std::ios::in);

    int n;
    getline(f, str);
    std::istringstream tmp1(str);
    tmp1 >> n;

    for (int i = 0; i < n; ++i)
    {
        int x;
        int y;
        getline(f, str);
        std::istringstream tmp2(str);
        tmp2 >> x;
        getline(f, str);
        std::istringstream tmp3(str);
        tmp3 >> y;
        switch (type)
        {
        case 'P':
            game.points.push_back(sf::Vector2f(x, y));
            break;
        case 'R':
            game.roadPosition.push_back(sf::Vector2f(x, y));
            break;
        }
    }

    f.close();
}