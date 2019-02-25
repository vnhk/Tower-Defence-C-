#pragma once
#include <SFML/Graphics.hpp>
#include "Gold.h"
#include "Animation.h"

//! Klasa podstawowa opisujaca przeciwnikow
/*!
    @param Npc::sf::Texture tekstura przeciwnika
    @param Npc::sf::greenShape ksztal okreslajacy ilosc zycia przeciwnika
    @param Npc::sf::redShape ksztal okreslajacy ilosc zycia przeciwnika
    @param Npc::sf::hp aktualna ilosc zycia przeciwnika
    @param Npc::sf::hpconst ilosc zycia przeciwnika
    @param Npc::amountOfGold ilosc zlota jaka gracz dostaje za pokonanie przeciwnika
    @param Npc::NpcSpeed predkosc poruszania sie przeciwnika
    @param Npc::alive okresla czy przeciwnik zostal pokonany
    @param Npc::direction okresla kierunek ruchu
    @param Npc::armor okresla czy przeciwnik jest opancerzony
    @param Npc::textureSize rozmiar tekstury
    @param Npc::amountOfNpc statyczne pole okreslajace ilosc przeciwnikow
    @param Npc::amountOfDeadNpc statyczne pole okreslajace ilosc pokonanych przeciwnikow
    @param Npc::point okresla aktualny punkt do ktorego idzie przeciwnik
    @param Npc::npcSprite obrazek przeciwnika
    @param Npc::npcAnim struktura opisujaca animacje przeciwnika
*/

class Npc
{
    protected:
    sf::Texture npcTexture;
    sf::RectangleShape greenShape;
    sf::RectangleShape redShape;
    int hp,hpconst;
    int amountOfGold;
    int NpcSpeed;
    bool alive;
    char direction;
    bool armor;
public:
    sf::Vector2f textureSize;
    //! Statyczna metoda sprawdzajaca status przeciwnikow
    /*!
        @return true jesli wszyscy przeciwnicy zostali pokonani, false w przeciwnym wypadku

    */
    static bool isSomeoneAlive();
    static int amountOfNpc;
    static int amountOfDeadNpc;
    int point;
    sf::Sprite npcSprite;
    //! Metoda zmieniajaca status przeciwnika
    /*!
        @param Gold & obiekt klasy Gold

        Metoda zmienia status zmiennej alive na false oraz dodaje ilosc zlota pobranego z pola
        amountOfGold do pola obiektu klasy Gold za pomoca odpowiedniej metody.

    */
	void kill(Gold &gold);
    //! Metoda zmieniajaca status przecinika
    /*!
        Metoda zmienia status zmiennej alive na false.
    */
    void kill();
    //! Metoda ustawiajaca kierunek
    /*!
        @param char okresla kierunek poruszania
        Metoda ustawia wartosc pola direction na podana w parametrze.  
    */
    void setDirection(char );
    //! Metoda pobiera kierunek
    /*!
       @return wartosc pola direction 
    */
    char getDirection();
    struct Animation_Parameters npcAnim;
    //! Konstruktor
    /*!
        Ustawia wartosci oraz wlasciwosci podstawowych oraz uniwersalnych skladowych klasy,
        ktore nie beda zmieniane w konstruktorach klas potomnych. 

        Kazde wywolanie konstruktora powoduje zwiekszenie wartosci pola statycznego amountOfNpc o jeden.
    */
    Npc();
    //! Destruktor
    ~Npc();
    //! Metoda zwracajaca pozycje
    /*!
       @return pozycja w pionie obrazu 
    */
    float getPositionY();
    //! Metoda zwracajaca pozycje
    /*!
       @return pozycja w poziomie srodka obrazu 
    */
    float getCenterOfSpritePositionX();
    //! Metoda zwracajaca pozycje
    /*!
       @return pozycja w pionie srodka obrazu 
    */
    float getCenterOfSpritePositionY();
    //! Metoda zwracajaca pozycje
    /*!
       @return pozycja w poziomie obrazu 
    */
    float getPositionX();
    //! Metoda przesuwajaca obraz
    /*!
       @param int przesuniecie w poziomie
       @param int przesuniecie w pionie

       Przesuwa przeciwnika o okreslona ilosc podana w argumentach wywolania metody.

    */
    void moveNpc(int x, int y);
    //! Metoda malujaca graficzne skladowe klasy
    /*!
        @param sf::RenderWindow & oryginal okna gry

        Metoda malujaca na ekran gry graficznych skladowych klasy Npc.  
    */
    void draw(sf::RenderWindow &window);
    //! Metoda pobierajca predkosc
    /*!
       @return wartosc pola NpcSpeed 
    */
    int getSpeed();
    //! Metoda pobierajaca punkty zdrowia
    /*!
       @return wartosc pola hp 
    */
    int getHp();
    //! Metoda ustawiajaca punkty zycia
    /*!
       @param int ilosc punktow zycia

       Metoda odejmuje podana w argumencie wywolania metody wartosc od wartosci pola hp.
    */
    void setHp(int dmg);
    //! Metoda zwraca status przeciwnika
    /*!
        @return wartosc pola alive
    */
    bool isAlive();
    //! Metoda pobierajaca pozycje
    /*!
        @return wspolrzedne obrazu npcSprite
    */
    sf::Vector2f getPosition();
};

//!Klasa opisujaca pierwszy z rodzajow przeciwnikow
class Infantry_1 : public Npc
{
    public:
    //!Konstruktor
    /*!
        Ustawia unikatowe pola dla danego rodzaju przeciwnika, takie jak:
        - ilosc zycia
        - tekstura
        - animacje
    */
    Infantry_1();
   //! Destruktor 
    ~Infantry_1();
};

//!Klasa opisujaca drugi z rodzajow przeciwnikow
class Cavalry_1 : public Npc
{
    public:
    //!Konstruktor
    /*!
        Ustawia unikatowe pola dla danego rodzaju przeciwnika, takie jak:
        - ilosc zycia
        - tekstura
        - animacje
    */
    Cavalry_1();
   //! Destruktor 
    ~Cavalry_1();
};

//!Klasa opisujaca trzeci z rodzajow przeciwnikow
class Infantry_2 : public Npc
{
    public:
    //!Konstruktor
    /*!
        Ustawia unikatowe pola dla danego rodzaju przeciwnika, takie jak:
        - ilosc zycia
        - tekstura
        - animacje
    */
    Infantry_2();
   //! Destruktor 
    ~Infantry_2();
};

//!Klasa opisujaca czwarty z rodzajow przeciwnikow
class Cavalry_2 : public Npc
{
    public:
    //!Konstruktor
    /*!
        Ustawia unikatowe pola dla danego rodzaju przeciwnika, takie jak:
        - ilosc zycia
        - tekstura
        - animacje
    */
    Cavalry_2();
   //! Destruktor 
    ~Cavalry_2();
};

//!Struktura przechowujaca wszystkie rodzaje jednostek
/*!
    @param Npcbuf::Cavalry przechowuje informacje o kazdej jednostce typu Kawaleria
    @param Npcbuf::Cavalry_Arm przechowuje informacje o kazdej jednostce typu Opancerzona Kawaleria
    @param Npcbuf::Infantry przechowuje informacje o kazdej jednostce typu Piechota
    @param Npcbuf::Infantry_Arm przechowuje informacje o kazdej jednostce typu Opancerzona Piechota
*/
struct Npcbuf
{
    std::vector<Cavalry_1 *> Cavalry;
    std::vector<Infantry_1 *> Infantry;
    std::vector<Cavalry_2 *> Cavalry_Arm;
    std::vector<Infantry_2 *> Infantry_Arm;
    //! Metoda usuwajaca
    /*!
        Metoda najpierw usuwa dynamicznie stworzone obiekty, nastepnie czysci wektory ktore je przechowywaly.
    */
    void deleteObj();
    //! Metoda malujaca
    /*!
        @param sf::RenderWindow & oryginal okna gry

        Metoda pozwala na malowanie na ekranie wszystkich przeciwnikow.
    */
    void draw(sf::RenderWindow &);
};