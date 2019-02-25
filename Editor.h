#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Road.h"
#include "Tower.h"
#include <fstream>
#include <sstream>

void editor(sf::RenderWindow &window,int id);

/*!
*
@brief Klasa opisujaca punkty na mapie po ktorej przeciwnicy sie poruszaja
*
*
@param Point::circle pole typu sf::CircleShape opisujace graficznie punkt
*/


class Point
{
    sf::CircleShape circle;
    //! Zaprzyjazniona z klasa Point funkcja editior
    /*!
        @param sf::RenderWindow &window oryginal okna gry
        @param int id numer etapu gry ktory edytujemy

        O mozliwosci wlaczenia edytora informuje napis na ekranie glownym.
        Klikniecie prawym przyciskiem myszy na danym etapie otwiera jego edytor.

        Zadaniem ten funkcji jest umozliwienie tworzenia i modyfikowania nowych etapow gry w szybki sposob.
        Pozwala na okreslenie drogi po ktorej beda poruszac sie przeciwnicy oraz
        miejsca w ktorej gracz moze postawic wieze.
        Kazda opcja moze zostac cofnieta.
        Klikniecie przycisku Escape, powoduje zapisanie wszystkich zmian, beda one dostepne na danym etapie
        przy uruchomieniu gry.
        Zamkniecie "krzyzykiem" powoduje wyjscie z edytora wraz z odrzuceniem wszystich wprowadzonych zmian.

        Aby uzyskac dostep do tej funkcji nalezy wykonac program z opcjami 'dev dev'.

    */
    friend void editor(sf::RenderWindow &window,int id);
public:
    //! Konstruktor
    /*!
        @param sf::Vector2i xy wspolrzedne punktu
    */   
    Point(sf::Vector2i xy);
    //! Destruktor
    ~Point();
};
