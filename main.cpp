#include "Menu.h"

//!Funkcja main
/*!
    @param int ilosc argumentow wywolania programu
    @param char * tablica przchowujaca wartosci kazdego z argumentow

    Tworzone jest tutaj okno gry o wymiarach 1300x600 o nazwie "Tower Defence".
    Zmiana rozmiaru okna jest wylaczona.

    Sprawdza czy ilosc argumentow wywolania wynosi 3 i czy ich wartosc wynosi odpowiedno:
    1. Nazwa programu
    2. dev
    3. dev
    Jesli tak otwierany jest tryb edycji, pozwalajacy na tworzenie i modyfikowanie poziomow gry.

    Inne wywolanie programu powoduje domyslne wlaczenie gry.
*/
int main(int argc, char *argv[])
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1300, 600), "Tower Defence" , sf::Style::Close);
    window.setFramerateLimit(45);
    if(argc==3)
    {
        if(std::string(argv[1])=="dev"&&std::string(argv[2])=="dev")
        {
            menu(window,true);
            return 1;
        }
    }
    menu(window,false);


    return 0;
}
