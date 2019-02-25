#include <SFML/Graphics.hpp>
#include <sstream>
#pragma once

//! Klasa umozliwiajaca wybor etapu gry przez gracza
/*!
    @param LevelsObject::levelTexture tekstura jako screen poziomu
    @param LevelsObject::levelSprite obraz przyjmujacy powyzsza teksture
    @param LevelsObject::id numer poziomu
    @param LevelsObject::active okresla aktywnosc poziomu

*/


class LevelsObject
{
    sf::Texture levelTexture;
    sf::Sprite levelSprite;
    int id;
    bool active;
public:
    //! Konstruktor
    /*!
        @param int numer poziomu

        Wczytuje i ustawia teksture z pliku dla odpowiadajacemu mu numeru poziomu podanego w parametrze konstruktora.
        Nastepnie ustawia pozycje obrazu odzwierciedlajacego wyglad danego poziomu.

    */
    LevelsObject(int id);
    //! Destruktor
    ~LevelsObject();
    //! Metoda sprawdzajaca pozycje myszki
    /*!
        @param sf::Vector2i pozycja myszki na oknie gry
        @return true jezeli wskaznik myszki znajduje sie na obrazku danego poziomu, false w przeciwnym wypadku
    */
    bool isMouseOn(sf::Vector2i mouse);
    //! Metoda wymalowujaca graficzne skladowe klasy
    /*!
        @param sf::RenderWindow & oryginal okna gry

        Metoda pozwala na wymalowanie na ekranie gry prywatnych graficzych skladowych klasy.
    */
    void draw(sf::RenderWindow &window);
    //! Metoda okreslajaca aktywnosc wybranego etapu
    /*!
        @param bool 

        Metoda ustawia wartosc pola active na wartosc podana w argumencie wywolania tej metody.

    */
    void activate(bool );
    //! Metoda zwracajaca rozmiar tekstury
    /*!
          @return rozmiar tekstury w postaci wektora liczb typu unsigned int  
    */
    sf::Vector2u getTextureSize();
};
