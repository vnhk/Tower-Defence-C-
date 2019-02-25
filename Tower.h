#pragma once
#include <SFML/Graphics.hpp>
#include "Shot.h"
#include "Npc.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include "Gold.h"
#include "Animation.h"
#define PT 100
#define PG 200
#define PC 300
#define PS 400

#define TowerSize 60

//! Klasa podstawowa opisujaca wieze
/*!
    @param Tower::towerSprite obraz wiezy
    @param Tower::shot obiekt klasy ShotClass
    @param Tower::set okresla czy wieza jest wybrana
    @param Tower::reload okresla czy wieza jest gotowa do ataku
    @param Tower::goodForArmEne okresla czy wieza jest dobra przeciwko opancerzonym przeciwnikom
    @param Tower::mouse okresla pozycje wskaznika myszki na ekranie
    @param Tower::Towers statyczne pole okreslajace ilosc wiez
    @param Tower::restTime okresla ilosc czasu potrzebnego na przeladowanie
    @param Tower::lastAtack zmienna czasowa okreslajaca czas ostatniego ataku
    @param Tower::lastCheck zmienna czasowa okreslajaca czas ostatniego sprawdzania
    @param Tower::updateCost[3] tablica posiadajaca informacje o koszcie ulepszenia wiez
    @param Tower::towerLvl okresla poziom ulepszenia wiezy
    @param Tower::id okresla unikalny numer wiezy
    @param Tower::name okresla nazwe wiezy
    @param Tower::range okresla zasieg ataku wiezy
    @param Tower::dmg okresla wartosc ataku wiezy
    @param Tower::valueOfTurret stala okreslajaca cene ulepszenia wiez
    @param Tower::informationText przedstawia graficznie informacje o wiezy
    @param Tower::informationBackground ksztalt wykorzystywany jako tlo pod informacje o wiezach
    @param Tower::font czcionka
    @param Tower::lvlUpTexture tekstura przycisku do ulepszania
    @param Tower::lvlUpSprite obraz przycisku to ulepszania
    @param Tower::shotAnimation animacja ataku wiezy

*/

class Tower
{
protected:
    sf::Sprite towerSprite;
    ShotClass shot;
    sf::CircleShape RangeSprite;
    bool set;
    bool reload;
    bool goodForArmEne;
    sf::Vector2i mouse;
    static int Towers;
    float restTime;
    time_t lastAttack;
    time_t lastCheck;
    int updateCost[3];
    int towerLvl;
    int id;
    std::string name;
    unsigned range;
    int dmg;
    const int valueOfTurret = 100;
    sf::Text informationText;
    sf::RectangleShape informationBackground;
    sf::Font font;
    sf::Texture lvlUpTexture;
    sf::Sprite lvlUpSprite;
    Animation shotAnimation;
    sf::Texture texture,texture1,texture2;
    //! Metoda ustawiajaca informacje o wiezy
    /*!
        Metoda ustawia wlasciosci pola informationText.
    */
    void setInformation();
    //! Metoda uzupelniajaca
    /*!
        Metoda ustawia pozostale uniwersalne wlasciwosci oraz wartosci dla pol klasy.
    */
    void afterTowerConstructor();
public:
    static int selectedTower;
    //!Konstruktor
    /*!

        @param sf::Vector2i pozycja wskaznika myszki na ekranie gry

        Ustawia wartosci i wlasciwosci podstawowych oraz uniwersalnych skladowych klasy,
        ktore nie beda zmieniane w konstruktorach klas potomnych. 
        Pozycja wiezy jest rowna pozycji myszki pobranej z parametru konstruktora.

        Kazde wywolanie konstruktora powoduje zwiekszenie wartosci pola statycznego Towers o jeden.


    */
    Tower(sf::Vector2i);
    //! Domyslny Konstruktor
    Tower();
    //! Destruktor
    ~Tower();
    //! Metoda zwracajaca cene.
    /*!
        @return zwraca wartosc pola valueOfTurret

        Metoda zwraca koszt ulepszenia wiezy.
    */
    int getPrize();
    //! Metoda resetujaca wybor wiezy
    /*!
        Metoda ustawia wybor wiezy na domyslny.
    */
    void defaultSelectedTower();
    //! Metoda malujaca graficzne skladowe klasy
    /*!
        @param sf::RenderWindow & oryginal okna gry

        Metoda malujaca na ekran gry graficznych skladowych klasy Tower.  
    */
    void draw(sf::RenderWindow &window);
    //! Metoda sprawdzajaca zasieg
    /*!
        @return true jesli w zasiegu wiezy znajduje sie przeciwnik, false w przeciwnym wypadku
    */
    bool towerRange(Npc *npc);
    //! Metoda ustawiajaca teksture
    /*!
        Metoda ustawia odpowiednia teksture dla wiezy w zaleznosci od posiadanego przez nia poziomu.
    */ 
    void setTexture();
    //! Metoda symulujaca atak wiezy
    /*!
        @param struct Npcbuf & struktura zawierajca wszystkich przeciwnikow
        @param Gold & obiekt klasy Gold

        Metoda sprawdza czy czas ktory minal od ostatniego ataku i sprawdzenia jest wystarczajacy.
        Jesli nie, konczy swoje dzialanie.

        W przeciwnym wypadku sprawdza czy w zasiegu ataku wiezy znajduje sie przeciwnik.
        Jesli nie to resetuje czas sprawdzania.

        Gdy przeciwnik znajduje sie w zasiegu ataku wiezy, to nastepuje obliczenie wartosci ataku oraz
        odjecie tej wartosci od punktow zycia przeciwnika.

        */
    void attack(struct Npcbuf &npc,Gold &gold);
    bool improve(Gold &gold,sf::Vector2i pos);
    //! Metoda sprawdzajaca
    /*!
        @param sf::Vector2i pozycja wskaznika myszki na ekranie gry

        @return true jesli wskaznik myszki znajduje sie na obrazie wiezy, false w przeciwnym wypadku        
    */
    bool selectTower(sf::Vector2i mouse);
};
//! Klasa potomna opisujaca 1 rodzaj wiez
class T_Arrow : public Tower
{
public:
    //!Konstruktor
    /*!
        Ustawia unikatowe pola dla danego rodzaju wiezy, takie jak:
        - zasieg ataku
        - czas przeladowania
        - obrazenia
        - koszt
        - tekstura
    */
    T_Arrow(sf::Vector2i mouse);
    //! Destruktor
    ~T_Arrow();
};
//! Klasa potomna opisujaca 2 rodzaj wiez

class T_Gun : public Tower
{
public:
    //!Konstruktor
    /*!
        Ustawia unikatowe pola dla danego rodzaju wiezy, takie jak:
        - zasieg ataku
        - czas przeladowania
        - obrazenia
        - koszt
        - tekstura
    */
    T_Gun(sf::Vector2i mouse);
    //! Destruktor
    ~T_Gun();
};

//! Klasa potomna opisujaca 3 rodzaj wiez
class T_Supp : public Tower
{
public:
    //!Konstruktor
    /*!
        Ustawia unikatowe pola dla danego rodzaju wiezy, takie jak:
        - zasieg ataku
        - czas przeladowania
        - obrazenia
        - koszt
        - tekstura
    */
    T_Supp(sf::Vector2i mouse);
    //! Destruktor
    ~T_Supp();
};

//! Klasa potomna opisujaca 4 rodzaj wiez
class T_Cannon : public Tower
{
public:
    //!Konstruktor
    /*!
        Ustawia unikatowe pola dla danego rodzaju wiezy, takie jak:
        - zasieg ataku
        - czas przeladowania
        - obrazenia
        - koszt
        - tekstura
    */
    T_Cannon(sf::Vector2i mouse);
    //! Destruktor
    ~T_Cannon();

};

//! Klasa tworzaca obraz wiez, ktory pomaga ustawiac je na planszy
/*!
    @param TowerPlace::towerShadow obraz
    @param TowerPlace::towerShadowTexture[4] tablica tekstur kazdej z wiez
 */
class TowerPlace
{
    sf::Sprite towerShadow;
    sf::Texture towerShadowTexture[4];
    public:
    //! Konstruktor
    /*!
        @param pozycja wskaznika myszki

        Pozycja myszki jest przypisywana do pozycji w jakiej bedzie znajdowal sie obrazek.
    */
    TowerPlace(sf::Vector2i xy);
    //! Metoda do ustawiania pozycji
    /*!
        @param pozycja wskaznika myszki

        Pozycja myszki jest przypisywana do pozycji w jakiej bedzie znajdowal sie obrazek.
        W ten sposob obrazek jest w tym samym miejscu w ktorym znajduje sie wskaznik myszy,
        pomaga to na ustawienie wiezy w dogodnym miejscu.
    */
    void setShadow(sf::Vector2i pos);
    //! Metoda wymalowujaca na ekran
    /*!
        @param sf::RenderWindow & oryginal okna gry

        Metoda pozwala na wymalowanie wszystkich elementow graficznych klasy.
    */
    void draw(sf::RenderWindow &window, int id);
    //! Metoda ustawiajaca teksture obrazka
    /*!
        @param int numer okreslajacy typ aktualnie wybranej wiezy z menu gry

        Ustawia odpowiednia teksture w zaleznosci od podanego w parametrze numeru.
    */
    void setTexture(int);
};
