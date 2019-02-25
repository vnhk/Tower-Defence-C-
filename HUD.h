#pragma once
#include "Tower.h"
#include <SFML/Graphics.hpp>

//! Klasa opisujaca menu znajdujace sie na planszy gry
/*!
    @param HUD::hudTexture tekstura menu
    @param HUD::hudSprite obrazek ktory przyjmuje teksture hudTexture
    @param HUD::taSprite obrazek okreslajacy wieze typu Arrow Tower
    @param HUD::tgSprite obrazek okreslajacy wieze typu Gun Tower
    @param HUD::tcSprite obrazek okreslajacy wieze typu Cannon Tower
    @param HUD::tsSprite obrazek okreslajacy wieze typu Supp Tower
    @param HUD::selectedTower przymuje id aktualnie wybranej wiezy
    @param HUD::active okresla aktywnosc obiektu
    @param HUD::towerok tekstura przycisku wyboru
*/

class HUD
{
    sf::Texture hudTexture,towerok;
    sf::Sprite hudSprite;
    
    sf::Sprite taSprite;
    sf::Sprite tgSprite;
    sf::Sprite tcSprite;
    sf::Sprite tsSprite;
    
    int selectedTower;
    
    
public:
    //! Konstruktor
    /*!
        @param sf::RenderWindow & oryginal okna gry

        Przypisuje odpowiednie tekstury do sprite'ow. Nastepnie ustawia je w odpowiednich miejscach.
    */
    HUD(sf::RenderWindow &window);
    //! Metoda pozwalajaca na wymalowanie na ekran skladowych klasy
    /*!
        @param sf::RenderWindow & oryginal okna gry

        Pozwala na wymalowanie wszystkich prywatnych graficznych skladowych klasy.

    */
    void draw(sf::RenderWindow &window);
    bool active;
    //! Metoda sprawdzajaca ktora opcja zostala wybrana
    /*!
        @param sf::Vector2i okresla pozycje myszki w oknie gry
        @param TowerPlace & oryginal obrazka wymalowywanego na ekranie

        Sprawdza czy zostala wybrana opcja z menu. Jesli tak to zostaje podmiemiona 
        tekstura na taka ktora odpowiada wybranej opcji.

    */
    void click(sf::Vector2i mouse,TowerPlace &);
    // Metoda sluzaca do pobierania wartosci pola selectedTower
    /*!
        @return wartosc zmiennej selectedTower
    */
    int getSelectedTower();
};
