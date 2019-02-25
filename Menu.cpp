#include "Menu.h"

void menu(sf::RenderWindow &window, bool developer)
{
    Menu menu(developer);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (menu.LevelClick(sf::Mouse::getPosition(window)))
                    game(menu.getLevelId(), window);
                else if(menu.BookClick(sf::Mouse::getPosition(window)))
                        game_rules(window);
                else
                    menu.ArrowClick(sf::Mouse::getPosition(window));
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                if (menu.isDeveloperMode())
                {
                    if (menu.LevelClick(sf::Mouse::getPosition(window)))
                        editor(window, menu.getLevelId());
                }
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }
}

bool Menu::isDeveloperMode()
{
    return developer;
}

Menu::Menu(bool developer)
{
    this->developer = developer;
    activeLevelID = 0;
    Levels[0].activate(true);

    leftArrowTexture.loadFromFile("Textures/Menu/leftArrow.png");
    rightArrowTexture.loadFromFile("Textures/Menu/rightArrow.png");
    
    backgroundTexture.loadFromFile("Textures/Menu/background.png");
    backgroundSprite.setTexture(backgroundTexture);

    frameTexture.loadFromFile("Textures/Menu/frame.png");
    frameSprite.setTexture(frameTexture);
    frameSprite.setPosition(sf::Vector2f(650-.5*frameTexture.getSize().x,600-frameTexture.getSize().y-25));

    bookTexture.loadFromFile("Textures/Menu/book.png");
    bookSprite.setTexture(bookTexture);
    bookSprite.setPosition(650-bookTexture.getSize().x/2,10);

    leftArrowSprite.setTexture(leftArrowTexture);
    rightArrowSprite.setTexture(rightArrowTexture);

    leftArrowSprite.setPosition(0, 0);
    rightArrowSprite.setPosition(1300 - rightArrowTexture.getSize().x, 0);

    if(developer)
    {
        font.loadFromFile("Files/Fonts/Gold/28 Days Later.ttf");
        text.setFont(font);
        text.setString("Developer Mode\nEsc Saves\n");
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Cyan);
        text.setPosition(leftArrowTexture.getSize().x,0);
    }

}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
    //window.draw(backgroundSprite);
    for (int i = 0; i < amountOfLevels; ++i)
        Levels[i].draw(window);
    window.draw(frameSprite);    
    window.draw(leftArrowSprite);
    window.draw(rightArrowSprite);
    window.draw(bookSprite);
    if(developer)
        window.draw(text);
}

bool Menu::LevelClick(sf::Vector2i mouse)
{
    for (int i = 0; i < amountOfLevels; ++i)
    {
        if (Levels[i].isMouseOn(mouse) == true)
            return true;
    }
    return false;
}

bool Menu::BookClick(sf::Vector2i mouse)
{
    if(bookSprite.getGlobalBounds().contains(mouse.x,mouse.y))
    {
        return true;
    }
    return false;
}

void Menu::ArrowClick(sf::Vector2i mouse)
{
    if (leftArrowSprite.getGlobalBounds().contains(mouse.x, mouse.y))
    {
        if (activeLevelID == 0)
        {
            activeLevelID = amountOfLevels - 1;
            Levels[0].activate(false);
            Levels[amountOfLevels - 1].activate(true);
        }
        else
        {
            Levels[activeLevelID].activate(false);
            Levels[activeLevelID - 1].activate(true);
            --activeLevelID;
        }
    }

    else if (rightArrowSprite.getGlobalBounds().contains(mouse.x, mouse.y))
    {
        if (activeLevelID == amountOfLevels - 1)
        {
            activeLevelID = 0;
            Levels[amountOfLevels - 1].activate(false);
            Levels[0].activate(true);
        }
        else
        {
            Levels[activeLevelID].activate(false);
            Levels[activeLevelID + 1].activate(true);
            ++activeLevelID;
        }
    }
}

int Menu::getLevelId()
{
    return activeLevelID;
}