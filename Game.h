#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include "HUD.h"
#include "Npc.h"
#include "Tower.h"
#include "Gold.h"
#include "Animation.h"
#define RoadSize 35
/*!
*
@brief Klasa opisujaca glowne skladowe wymagane do uruchomienia rozgrywki
*
*
@param Game::name nazwa etapu gry
*
@param Game::points przechowuje wspolrzedne kazdego z punktow tworzacych droge po ktorej poruszali sie przeciwnicy
*
@param Game::roadPosition przechowuje wspolrzednego kazdego pola na ktorych nie moze zostac umieszczona wieza
*
@param Game::bool_points okresla czy przeciwnik byl w danym punkcie
*
@param Game::amountOfPoints ilosc wszystkich punktow tworzacych droge
*
@param Game::amountOfLives ilosc pozostalych zyc gracza
*
@param Game::amountOfLivesR ilosc wszystkich zyc gracza
*
@param Game::defeat okresla czy nastapila porazka
*
@param Game::victory okresla czy nastapilo zwyciestwo
*
@param Game::mapTexture unikatowa tekstura kazdej z map
*
@param Game::heartTexture tekstura w ksztalcie serca
*
@param Game::okTextureHover tekstura przycisku
*
@param Game::mapSprite obraz przyjmujacy teksture mapTexture
*
@param Game::heartSprite obraz przyjmujacy teksture heartTexture
*
@param Game::font czcionka
*
@param Game::amountOfLivesText tekst przedstawiajacy ilosc pozostalych zyc gracza, wykorzystuje czcionke font
*
@param Game::amountOfInfantry[2] okresla ilosc przeciwnikow typu piechota
*
@param Game::amountOfCavalry[2] okresla ilosc przeciwnikow typu kawaleria
*
*/

class Game
{

    std::string name;
    std::vector<sf::Vector2f> points;
    std::vector<sf::Vector2f> roadPosition;
    std::vector<bool> bool_points;
    int amountOfPoints;
    int amountOfLives;
    int amountOfLivesR;
    bool defeat;
    bool victory;
    sf::Texture mapTexture;
    sf::Texture heartTexture;
    sf::Texture okTextureHover;
    sf::Sprite mapSprite;
    sf::Sprite heartSprite;
    sf::Font font;
    sf::Text amountOfLivesText;
    //! Zaprzyjazniona z klasa Game funkcja.
    /*!
        @param int id okresla etap ktory wybral gracz
        @param sf::RenderWindow &window oryginal okna gry

        Jest to glowna funkcja rozgrywki.
        W zaleznosci od podanego w jej wywolaniu argumentu id zostaja wczytane wszystkie ustawienia dotyczace
        tego etapu, takie jak ilosc przeciwnikow, ilosc zlota, ilosc zyc gracza itp.
        W wczytywaniu ustawien bierze udzial pomocnicza funkcja:
        void load(std::string filename,Game &game,char type);

        W opraciu o uzyskane z plikow informacje, funkcja ta tworzy wszystkie potrzebne do gry elementy
        z ktorych gracz moze korzystac.
    */
    friend void game(int id, sf::RenderWindow &window);
    //! Zaprzyjazniona z klasa Game funkcja
    /*!
        @param std::string filename nazwa pliku z ktorego beda wczytywane informacje
        @param Game &game oryginal obiektu klasy Game, do niego beda przypisane wszystkie pobrane informacje
        @param char type okresla typ operacji

        Otwiera plik o podanej nazwie, pobiera z niego informacje i w oparciu 
        o podany typ operacji przypisuje je do obiektu game.
    */
    friend void load(std::string filename, Game &game, char type);
    //! Metoda zmieniaja ilosc pozostalych zyc gracza
    /*!
        Kazde wywolanie tej metody powoduje zmniejszenie pozostalej ilosci zyc o 1.
        Jezeli wynikowa liczba zyc bedzie mniejsza od 1, to pole defeat zostanie ustawione na true.
    */
    void subLives();
    //! Metoda ustawiajaca napis w polu sf::Text amountOfLivesText
    /*!
        Metoda ta jest wykonywana po kazdej zmianie wartosci pola amountOfLives.
        Przeksztalca wartosc tego pola na zmienna typu string a nastepnie ustawia napis w polu
        amountOfLivesText.
    */
    void setTextString();

  public:
    int amountOfInfantry[2];
    int amountOfCalvary[2];
    //! Konstruktor
    /*!

        @param std::string name okresla nazwe etapu gry
        @param int *aoi tablica zawierajaca informacje o ilosci jednostek typu piechota
        @param int *aoc tablica zawierajaca informacje o ilosci jednostek typu kawaleria
        @param int aop ilosc punktow opisujacych droge
        @param int aol ilosc zyc gracza
    
        Przypisuje podane informacje do odpowiednich pol klasy.
    */
    Game(std::string name, int *, int *, int, int);
    //! Domyslny konstruktor
    /*!
        Pozwala stworzyc obiekt bez okreslania pol w klasie.
    */
    Game();
    //! Destruktor
    ~Game();
    //! Metoda pozwalajaca na przypisanie wartosci polu victory
    /*!
        @param bool v 
    */
    void setVictory(bool);
    //! Metoda pozwalajaca na przypisanie wartosci polu name
    /*!
        @param std::string name;
    */
    void setName(std::string name);
    //! Metoda wymalowujaca elementy klasy na ekranie.
    /*!
        @param sf::RenderWindow &window oryginal okna gry na którym beda wymalowane elementy klasy.

        Metoda ta pozwala na wymalowanie wszystkich wymaganych prywatnych elementow klasy.

    */ 
    void draw(sf::RenderWindow &window);
    //! Metoda ustawiajaca teksture mapy gry
    /*!
        @param int id okresla numer etapu gry

        Ustawia teksture mapy dla etapu okreslonego za pomoca parametru id.
    */
    void setMapTexture(int id);
    //! Metoda odwzorujaca droge po ktorej poruszaja sie przeciwnicy
    /*!
        @param Npc *npc oryginal obiektu klasy Npc opisujacy przeciwnika
        @param Animation *animation oryginal klasy Animation opisujacy animacje

        Metoda przypisuje kierunek i przesuniecie przeciwnika w kierunku kolejnego z punktow
        ustawiajac przy tym jego animacje.
    */
    void road(Npc *npc, Animation *animation);
    //! Metoda sprawdzajaca czy miejsce wskazane przez myszke jest zablokowane
    /*!
        @param sf::Vector2i pos pozycja myszki na ekranie 
        @param std::vector<sf::Vector2i> TowersPosition wektor zawierajacy informacje o wspolrzednych wiez
        postawionych przez gracza
        @return true - jesli obszar mapy jest wolny, false w przeciwnym wypadku

        Metoda korzysta ze skladowych klasy okreslajacych min. pozycje drogi po ktorej poruszaja sie przeciwnicy
        oraz z parametrow i sprawdza czy wskaznik myszy znajduje sie na nich.
  

    */
    bool isOnBlockedFile(sf::Vector2i pos, std::vector<sf::Vector2i> TowersPosition);
    //! Metoda tworzaca ekran koncowy gry
    /*!
        @param sf::RenderWindow& oryginal okna gry
        @param std::vector<T_Arrow *> wektor wskaznikow na obiekt klasy T_Arrow
        @param std::vector<T_Gun *> wektor wskaznikow na obiekt klasy T_Gun
        @param std::vector<T_Cannon *> wektor wskaznikow na obiekt klasy T_Cannon
        @param std::vector<T_Supp *> wektor wskaznikow na obiekt klasy T_Supp
        @param HUD kopia obiektu klasy HUD

        @return 0 w przypadku zakonczenia fukncji gdy pole defeat lub victory mialo wartosc true
        lub 1 w przeciwnym wypadku

        Jesli wartosc defeat wynosi true:
        Tworzony jest ekran koncowy z polprzezroczystym czerwonym tlem nalozonym na wymalowanej wczesniej
        planszy, menu oraz wiezami.
        Ponadto pokazywany jest napis oznaczajacy porazke oraz przycisk powrotu do menu glownego.

        Jesli wartosc victory wynosi true:
        Tworzony jest ekran koncowy z polprzezroczystym zielonym tlem nalozonym na wymalowanej wczesniej
        planszy, menu oraz wiezami.
        Ponadto pokazywany jest napis oznaczajacy zwyciestwo, ilosc gwiazek(1-3) oraz przycisk powrotu do menu glownego.

        Ilosc gwiazdek jest okreslona na podstawie wyniku gracza.
        Im wiecej zyc zostalo graczowi po wygranej tym wiekszy uzyska on wynik.

    */
    int gameStatus(sf::RenderWindow &, std::vector<T_Arrow *>,
                  std::vector<T_Gun *>,
                  std::vector<T_Cannon *>,
                  std::vector<T_Supp *>,
                  HUD); 
     //! Metoda zwracajaca wartosc pola name
    /*!
        @return wartosc pola name.
    */              
    std::string getName();
};

void game(int, sf::RenderWindow &);

void load(std::string, Game &, char);

//!Funkcja do usuwania objektow z wektorow
/*!
   @param std::vector<T *>& gdzie T jest typem danych

   Uniwersalna funkcja do usuwania stworzonych wczesniej dynamicznych obiektow.

*/

template <typename T> void deleteDynObjFromVect(std::vector<T *> &x);

//!Funkcja do czyszczenia wektorow
/*!
   @param std::vector<Animation *> & wektor wskaznikow na objekt klasy Animation
   @param std::vector<T_Arrow *> & wektor wskaznikow na objekt klasy T_Arrow
   @param std::vector<T_Gun *> & wektor wskaznikow na objekt klasy T_Gun
   @param std::vector<T_Cannon *> & wektor wskaznikow na objekt klasy T_Cannon
   @param std::vector<T_Supp *> & wektor wskaznikow na objekt klasy T_Supp
   @param std::vector<sf::Vector2i> & wektor typu sf::Vector2i przechowujacy pozycje wiez


*/
void clearVectors(std::vector<Animation *> &,
                  std::vector<T_Arrow *> &,
                  std::vector<T_Gun *> &,
                  std::vector<T_Cannon *> &,
                  std::vector<T_Supp *> &,
                  std::vector<sf::Vector2i> &);

//! Funkcja pozwalajaca ulepszac wieze
/*!
   @param std::vector<T_Arrow *> & wektor wskaznikow na objekt klasy T_Arrow
   @param std::vector<T_Gun *> & wektor wskaznikow na objekt klasy T_Gun
   @param std::vector<T_Cannon *> & wektor wskaznikow na objekt klasy T_Cannon
   @param std::vector<T_Supp *> & wektor wskaznikow na objekt klasy T_Supp
   @param Gold & obiekt klasy Gold
   @param sf::Vector2i okresla pozycje myszy na ekranie

   Jesli gracz ma wystarczajaca ilosc zlota to funkcja ulepsza wybrana wieze, 
   zwiekszajac jej obrazenia oraz zmniejszajac czas oczekiwania na kolejny atak.
   Maksymalnie wieze mozna ulepszyc 2 razy.

*/
void lvlUpTower(std::vector<T_Arrow *> &,
                std::vector<T_Gun *> &,
                std::vector<T_Cannon *> &,
                std::vector<T_Supp *> &,
                Gold &,
                sf::Vector2i);
