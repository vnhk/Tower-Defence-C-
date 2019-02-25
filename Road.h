#pragma once
#include <SFML/Graphics.hpp>

//! Klasa opisujaca droge
/*!
    @param sf::RectangleShape kwadratowy ksztalt
*/

class Road
{
    sf::RectangleShape rect;
public:
    //! Metoda wymalujaca na ekran graficzne skladowe klasy
    /*!
        @param sf::RenderWindow & oryginal okna gry

        Metoda pozwala na wymalowanie prywatnej skladowej klasy Road.
    */
    void draw(sf::RenderWindow &window);
    //! Metoda ustawiajaca pozycje
    /*!
        @param sf::Vector2i pozycja wskaznika myszki w oknie gry

        Metoda pozwala na ustawienie pozycji skladowej rect na pozycji rownej pozycji wskaznika myszki.

    */
    void setShadow(sf::Vector2i pos);
    //!Konstruktor
    /*!
        @param sf::Vector2i pozycja wskaznika myszki w oknie gry
        Ustawia rozmiar,pozycje oraz kolor skladowej rect.
        */
    Road(sf::Vector2i pos);
};
