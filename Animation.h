#pragma once
#include <SFML/Graphics.hpp>


/*!
*
@brief Struktura opisujaca animacje, z ktorej będzie tworzony obiekt klasy Animation
*
*
@param Animation_Parameters::texture 
*
@param Animation_Parameters::amountOfImages liczba obrazow potrzebnych w animacji 
*
@param Animation_Parameters::sizeX rozmiar w poziomie jednego obrazu 
*
@param Animation_Parameters::sizeY rozmiar w pionie jednego obrazu
*
@param Animation_Parameters::dimensions wymiary tekstury
*
@param Animation_Parameters::time_ms calkowity czas animacji w ms
*
@param Animation_Parameters::loopRow okresla czy animacja przechodzi do kolejnego etapu
*
@param Animation_Parameters::numberOfReptitions ilosc powtorzen
*/

struct Animation_Parameters
{
    sf::Texture texture;
    int amountOfImages;
    int sizeX;
    int sizeY;
    sf::Vector2u dimensions;
    unsigned time_ms;
    bool loopRow;
    int numberOfReptitions;
    //! Metoda pozwalajaca na ustawienie wszystkich skladowych struktury
    /*! 
        @param sf::Texture tekstura animacji 
        @param sf::Vector2u wymiary tekstury
        @param unsigned czas animacji w ms
        @param bool okresla czy animacja przechodzi do kolejnego etapu
        @param int ilosc powtorzen animacji
    */ 
    void update(sf::Texture,sf::Vector2u,unsigned,bool,int);
};

/*!
*
@brief Klasa opisujaca animacje
*
*
@param Animation::animationTime czas animacji
*
@param Animation::amountOfImages ilosc obrazow potrzebnych w animacji 
*
@param Animation::actualImage numer aktualnego obrazu
*
@param Animation::actualRow aktualny wiersz wykorzystany w animacji
*
@param Animation::numberOfReptitions ilosc powtorzen animacji
*
@param Animation::actualNumberOfReptitions aktualne powtorzenie animacji
*
@param Animation::sizeX rozmiar jednego obrazu w poziomie
*
@param Animation::sizeY rozmiar jednego obrazu w pionie
*
@param Animation::last numer ostatniego obrazku
*
@param Animation::loopRow okresla czy animacja przechodzi do kolejnego etapu
*
@param Animation::on okresla czy animacja jest wlaczona
*
@param Animation::dimensions wymiary tekstury
*
@param Animation::clock zmienna typu sf::Clock
*
@param Animation::time zmienna typu sf::Time, przechowuje ilosc ms
*
@param Animation::texture tekstura animacji
*/

class Animation
{
    float animationTime;
    unsigned amountOfImages;
    unsigned actualImage;
    unsigned actualRow;
    int numberOfReptitions;
    int actualNumberOfReptitions;
    int sizeX;
    int sizeY;
    int last;
    bool loopRow;
    bool on;
    sf::Vector2u dimensions;
    sf::Clock clock;
    sf::Time time;
    sf::Texture texture;
    public:
    //! Konstruktor
    /*!
      Przymuje strukture zawierajaca wszystkie potrzebne elementy do stworzenia animacji
      @param struct Animation_Parameters
    */
    Animation(struct Animation_Parameters);
    //! Domyslny konstruktor
    /*!
        Nie przyjmuje oraz nie przypisuje zadnych wartosci
    */
    Animation();
    //! Destruktor
    ~Animation();
    //! Metoda do ustawiania wszystkich potrzebnych elementow wymaganych do stworzenia animacji
    /*!
      @param struct Animation_Parameters
    */
    void setParameters(struct Animation_Parameters);
    //! Metoda rozpoczynajaca animacje
    void Start();
    //! Metoda aktualizujaca wyswietlany obraz
    /*!
        @param sf::Sprite &sprite
    */   
    void Update(sf::Sprite &sprite);
    //! Metoda wymuszajaca zmiane animacji
    void changeAnimation(int);
    //! Metoda zwracajaca wartosc pola bool on
    /*!
        @return true/false
    */
    bool getOn();
};
