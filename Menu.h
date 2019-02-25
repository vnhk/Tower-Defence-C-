#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include "LevelsObject.h"
#include "Npc.h"
#include "Game.h"
#include "Editor.h"
#include "Info.h"

void menu(sf::RenderWindow &window,bool developer);

//! Klasa opisujaca menu glowne gry
/*!
    @param Menu::amountOfLevels statyczna stala okreslajaca liczbe poziomow gry
    @param Menu::Levels[amountOfLevels] tablica objektow klasy LevelsObject
    @param Menu::activeLevelID numer aktywnego poziomu
    @param Menu::developer okresla tryb wlaczenia gry
    @param Menu::font czcionka
    @param Menu::text tekst o podanej czcionce font
    @param Menu::backgroundTexture tekstura tla
    @param Menu::rightArrowTexture tekstura strzalki wskazujacej w prawo
    @param Menu::leftArrowTexture tekstura strzalki wskazujacej w lewo
    @param Menu::bookTexure tekstura w ksztalcie ksiazki
    @param Menu::frameTexture tekstura ramki
    @param Menu::frameSprite obraz z tekstura frameTexture
    @param Menu::bookSprite obraz z tekstura bookTexture
    @param Menu::backgroundSprite obraz z tekstura backgroundTexture
    @param Menu::rightArrowSprite obraz z tekstura rightArrowTexture
    @param Menu::leftArrowSprite obraz z tekstura leftArrowTexture

*/


class Menu
{
    const static int amountOfLevels = 10;
    LevelsObject Levels[amountOfLevels] = {0,1,2,3,4,5,6,7,8,9};
    int activeLevelID;
    bool developer;
    sf::Font font;
    sf::Text text;
    sf::Texture backgroundTexture;
    sf::Texture rightArrowTexture;
    sf::Texture leftArrowTexture;
    sf::Texture bookTexture;
    sf::Texture frameTexture;
    sf::Sprite frameSprite;
    sf::Sprite bookSprite;
    sf::Sprite backgroundSprite;
    sf::Sprite rightArrowSprite;
    sf::Sprite leftArrowSprite;
    public:
    //! Konstruktor
    /*!
        @param bool okresla typ wlaczenia gry

        Wczytuje tekstury, ustawia obrazy na odpowiednich miejscach oraz przypisuje im odpowiednie tekstury.
        Jesli wartosc parametru wynosi true to dodatkowo zostaje wczytana czcionka oraz tekst, ktory bedzie
        widoczny na ekranie.
    */
    Menu(bool developer);
    //! Destruktor
    ~Menu();
    //! Metoda obslugujaca klikniecie myszy
    /*!
        @param sf::Vector2i pozycja wskaznika myszki na ekranie gry
        @return true jesli wskaznik myszki znajduje sie na aktualnie wyswietlanej miniaturce poziomu, false w przeciwnym wypadku
    */
    bool LevelClick(sf::Vector2i mouse);
    //! Metoda obslugujaca klikniecie myszy
    /*!
        @param sf::Vector2i pozycja wskaznika myszki na ekranie gry
    
        Metoda sprawdza czy wskaznik myszki znajduje sie na 1 z 2 strzalek, jesli tak to zostaje zmieniona miniaturka
        poziomu na nastepna (strzalka w prawo) lub na poprzednia (strzalka w lewo).
        Zmiana miniatur jest cykliczna, po przelaczeniu ostatniego elementu w prawo pojawia sie pierwszy,
        po przelaczeniu pierwszego elementu w lewo pojawia sie ostatni.
    */
    void ArrowClick(sf::Vector2i mouse);
    //! Metoda malujaca
    /*!
        @param sf::RenderWindow & oryginal okna gry

        Metoda pozwala na malowanie na ekranie wszystkich przeciwnikow.
    */
    void draw(sf::RenderWindow &window);
    //! Metoda obslugujaca klikniecie myszy
    /*!
        @param sf::Vector2i pozycja wskaznika myszki na ekranie gry
        @return true jesli wskaznik myszki znajduje sie na obrazku ksiazki, false w przeciwnym wypadku
    */
    bool BookClick(sf::Vector2i);
    //! Metoda zwracajaca
    /*!
        @return aktualna wartosc pola activeLevelID
    */
    int getLevelId();
    //! Metoda zwracajaca
    /*!
        @return aktualna wartosc pola developer
    */
    bool isDeveloperMode();
};