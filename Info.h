#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

//! Klasa umozliwiajaca przedstawienie kazdego przeciwnikia wraz z jego wlasciwosciami
/*!
    @param Presentation::sprite obraz przedstawiajacy przeciwnika
    @param Presentation::texture tekstura przypisywana do obrazu
    @param Presentation::font czcionka
    @param Presentation::descripion opis przeciwnika 
    @param Presentation::AP struktura Animation_Parameters opisujaca animacje obrazow
*/

class Presentation
{
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Font font;
    sf::Text description;
    //! Metoda wymalowujaca na ekran
    /*!
        @param sf::RenderWindow & oryginal okna gry

        Metoda pozwala na wymalowanie wszystkich elementow graficznych klasy.
    */
    void draw(sf::RenderWindow &);
    struct Animation_Parameters AP;
    //! Konstruktor
    /*!
        @param struct Animation_Parameters struktura opisujaca animacje
        @param sf::Vector2i zmienna okreslajaca pozycje
        @param std::string opis przeciwnika

        Struktura z parametru jest przypisywana do struktury z klasy.
        Pobrana pozycja okresla polozenie w oknie opisu oraz obrazu przeciwnika.
    */
    Presentation(struct Animation_Parameters,sf::Vector2i,std::string);
    //! Destruktor
    ~Presentation();
    //! Zaprzyjazniona z klasa Presentation funkcja.
    /*!
        @param sf::RenderWindow & oryginal okna gry

        Funkcja pozwala na przedstawienie na ekranie opisu przeciwnikow wraz z ich animacjami.

    */
    friend void game_rules(sf::RenderWindow &window);
};

    void game_rules(sf::RenderWindow &window);
    //! Funkcja wczytujaca dane
    /*!
        @param sf::Texture * tablica tekstur
        @param std::string * tablica opisow
        @param struct Animation_Parameters * tablica struktur opisujacych animacje

        Funkcja wczytuje tekstury z pliku. Wypelnia na ich podstawie strukture, na koniec
        ustawia opis dla kazdego z przeciwnikow.

    */
    void load(sf::Texture *npcT,std::string *npcS,struct Animation_Parameters *npcAP);