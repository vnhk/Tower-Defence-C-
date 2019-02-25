#include "Info.h"

Presentation::Presentation(struct Animation_Parameters AP,sf::Vector2i pos,std::string strDescription)
{
    texture = AP.texture;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect());
    sprite.setPosition(pos.x,pos.y);

    this->AP = AP;

    font.loadFromFile("Files/Fonts/Gold/28 Days Later.ttf");
    description.setFont(font);

    description.setCharacterSize(30);
    description.setFillColor(sf::Color::White);
    description.setPosition(pos.x+texture.getSize().x + 10,pos.y);
    description.setString(strDescription);
}
Presentation::~Presentation()
{

}


void Presentation::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
    window.draw(description);
}

void load(sf::Texture *npcT,std::string *npcS,struct Animation_Parameters *npcAP)
{
    npcT[0].loadFromFile("Textures/infantry_1.png");
    npcT[1].loadFromFile("Textures/infantry_2.png");
    npcT[2].loadFromFile("Textures/cavalry_1.png");
    npcT[3].loadFromFile("Textures/cavalry_2.png");

    npcAP[0].update(npcT[0],sf::Vector2u(4,4),1000,false,0);
    npcAP[1].update(npcT[1],sf::Vector2u(4,4),1000,false,0);
    npcAP[2].update(npcT[2],sf::Vector2u(4,4),1000,false,0);
    npcAP[3].update(npcT[3],sf::Vector2u(4,4),1000,false,0);

    npcS[0] = "Light Infantry\nHP 25\nUnarmored\n";
    npcS[1] = "Heavy Infantry\nHP 40\nArmored\n";
    npcS[2] = "Light Cavalry\nHP 50\nUnarmored\n";
    npcS[3] = "Knight\nHP 80\nArmored";
}

void game_rules(sf::RenderWindow &window)
{
    sf::Texture npcTexture[4];
    std::string npcDesc[4];
    struct Animation_Parameters npcAP[4];
    load(npcTexture,npcDesc,npcAP);

    Presentation p1(npcAP[0],sf::Vector2i(15,15),npcDesc[0]);
    Presentation p2(npcAP[1],sf::Vector2i(15,175),npcDesc[1]);
    Presentation p3(npcAP[2],sf::Vector2i(15,325),npcDesc[2]);
    Presentation p4(npcAP[3],sf::Vector2i(15,475),npcDesc[3]);
    
    Animation p1Anim(p1.AP);
    Animation p2Anim(p2.AP);
    Animation p3Anim(p3.AP);
    Animation p4Anim(p4.AP);

    p1Anim.Start();
    p1Anim.Start();
    p1Anim.Start();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return;
        }
        p1Anim.Update(p1.sprite);
        p2Anim.Update(p2.sprite);
        p3Anim.Update(p3.sprite);
        p4Anim.Update(p4.sprite);
        window.clear();
        p1.draw(window);
        p2.draw(window);
        p3.draw(window);
        p4.draw(window);
        window.display();
    }
}