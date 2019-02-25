#pragma once
#include <sstream>
#include "Animation.h"

//! Klasa opisujaca Zloto posiadane przez gracza
/*!
    @param Gold::amountOfGold pole okreslajace graficzna wersje ilosci zlota w postaci tekstu
    @param Gold::font pole okreslace czcionke ktora wykorzystuje amountOfGold
    @param Gold::amount ilosc zlota
    @param Gold::MAX_GOLD maksymalna ilosc zlota rowna 9999
    @param Gold::goldSprite obraz wyswietlany na ekranie, w ksztalcie monety
    @param Gold::goldTexture tekstura wykorzystywana przez goldSprite
    @param Gold::goldAnim struktura opisujaca animacje monety 
*/

class Gold
{
    sf::Text amountOfGold;
    sf::Font font;
    int amount;
    const int MAX_GOLD = 9999;
   
    public:
    sf::Sprite goldSprite;
    sf::Texture goldTexture;
    struct Animation_Parameters goldAnim;
    //!Konstruktor
    /*!
        Ustawia wartosci i wlasciwosci pol klasy min. wyglad, rozmiar tekstu, tekstury, animacje dla monety itp.
    */
    Gold();
    //! Destruktor
    ~Gold();
    //! Metoda sluzaca do wymalowania skladowych klasy
    /*!
        @param sf::RenderWindow & oryginal okna gry

        Metoda pozwala wymalowac na ekran ilosc zlota posiadanego przez gracza oraz obrazek monety znajdujacy sie obok niej.
    */
    void draw(sf::RenderWindow &window);
    //! Metoda pozwalajaca zwiekszyc ilosc zlota
    /*!
        @param int okresla ilosc zlota jaka nalezy dodac do aktualnej jego ilosci

        Ilosc zlota jest dodawana do zlota posiadanego przez gracza. 
        Jesli wynikowa wartosc jest za duza to zostaje zaokraglana do wartosci maksymalnej.
    */
    void addGold(int amount);
    //! Metoda pozwalajaca zmniejszyc ilosc zlota
    /*!
        @param int okresla ilosc zlota jaka nalezy odjac od aktualnej jego ilosci

        Ilosc zlota jest odejmowana od zlota posiadanego przez gracza. 
        Wartosc wynikowa musi byc wieksza badz rowna zero dlatego w przypadku gdy jest mniejsza - zostaje ustawiona na zero.

    */
    void subGold(int amount);
    //! Metoda pozwalajaca zwrocic ilosc zlota
    /*!
        @return ilosc zlota posiadana przez gracza
    */
    int getGold();

    //! Metoda pozwalajaca ustawic dowolna ilosc zlota
    /*!
        @param int okresla ilosc zlota na jaka nalezy zamienic aktualna jego ilosc

        Ilosc zlota posiadana przez gracza jest zamieniana na ilosc zlota znajdujaca sie w zmiennej typu int.
    */
    void setGold(int amount);

    //! Metoda sprawdzajaca czy gracz posiada wystarczajaca ilosc zlota
    /*!
        @param int okresla ilosc zlota potrzebnej do wykonania danej operacji np. kupno/ulepszenie wiezy

        @return true jesli gracz ma wystarczajaca ilosc zlota, false w przeciwnym wypadku
    */
    bool isEnoughGold(int amount);
    //! Metoda aktualizujaca ilosc zlota posiadana przez gracza
    /*!
        Metoda ta jest wywolywana przy kazdej zmianie ilosci zlota.

        Przypisuje aktualna wartosc zmiennej amount do wartosci wypisywanej na ekran (amountOfGold).

    */
    void updateGold();
};
