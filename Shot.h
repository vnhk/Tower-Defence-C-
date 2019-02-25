#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
//#include "Tower.h"

//! Klasa opisujaca graficznie atak wiez
/*!
    @param ShotClass::sprite obraz ataku
    @param ShotClass::texture tekstura ataku
    @param ShotClass::ap struktura opisujaca animacje ataku 
*/
class ShotClass
{
    friend class Tower;
    sf::Sprite sprite;
    sf::Texture texture;
    Animation_Parameters ap;
    public:
    //! Metoda malujaca
    /*!
        @param sf::RenderWindow & oryginal okna gry

        Metoda pozwalajaca na malowanie prywatnego pola klasy. 
    */
    void draw(sf::RenderWindow &);
    
    //! Konstruktor
    /*!
        Wczytywanie tekstur z pliku oraz ustawianie skladowych struktury Animation_Parameters.
    */
    ShotClass();
    //! Destruktor
    ~ShotClass();
};