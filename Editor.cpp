#include "Editor.h"


void saveToFile(std::string filename, std::vector <sf::Vector2i> data)
{
    std::fstream file;
    file.open(filename.c_str(),std::ios::out);

    file<<data.size();
    file<<"\n";
    for(unsigned i = 0; i < data.size(); ++i)
    {
        file<<data[i].x;
        file<<"\n";
        file<<data[i].y;
        file<<"\n";
    }
    file.close();
}


Point::Point(sf::Vector2i xy)
{
    circle.setFillColor(sf::Color::Blue);
    circle.setRadius(5);
    circle.setPosition(xy.x,xy.y);
}

Point::~Point()
{
    
}

void editor(sf::RenderWindow &window,int id)
{
    Game test;

    std::vector <sf::Vector2i> points;

    std::vector <Point> pointObj;
    
    std::vector <sf::Vector2i> roads;
    std::vector <Road> roadObj;
    Road tmpRoadShadow(sf::Mouse::getPosition());

    test.setMapTexture(id);

    bool pointsbool = false;
    bool roadbool = false;
    char lastAction;

    sf::RectangleShape fieldForEdit;
    fieldForEdit.setPosition(75,75);
    fieldForEdit.setFillColor(sf::Color(0,0,0,80));
    fieldForEdit.setSize(sf::Vector2f(1000,600));

    window.clear();
    window.setKeyRepeatEnabled(false);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                if(pointObj.size()>0)
                    pointObj.clear();
                if(points.size()>0)
                    points.clear();


                if(roads.size()>0)
                    roads.clear();
                if(roadObj.size()>0)
                    roadObj.clear();
                return;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                std::ostringstream t;
                t<<id;

                std::string filename = "Files/Levels/Level";
                filename+=t.str()+"/placeToPointsEditor.txt";
                saveToFile(filename,points);

                filename = "Files/Levels/Level";
                filename+= t.str()+"/placeToRoadEditor.txt";
                saveToFile(filename,roads);



                if(pointObj.size()>0)
                    pointObj.clear();
                if(points.size()>0)
                    points.clear();


                if(roads.size()>0)
                    roads.clear();
                if(roadObj.size()>0)
                    roadObj.clear();

                return;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {
                pointsbool=true;
                roadbool=false;
                lastAction='P';
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                pointsbool=false;
                roadbool=true;
                lastAction='R';
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))//cofniecie
            {
                pointsbool=false;
                roadbool=false;

                switch(lastAction)
                {
                case 'P':
                    if(points.size()>0)
                    {
                        pointObj.pop_back();
                        points.pop_back();
                    }
                    break;
                case 'R':
                    if(roads.size()>0)
                    {
                        roadObj.pop_back();
                        roads.pop_back();
                    }
                    break;
                default: break;

                }
            }

            if((event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left))
            {
                if(pointsbool)
                {
                    points.push_back(sf::Mouse::getPosition(window));
                    pointObj.push_back(sf::Mouse::getPosition(window));
                }
                else if(roadbool)
                {
                    roads.push_back(sf::Mouse::getPosition(window));
                    roadObj.push_back(sf::Mouse::getPosition(window));
                }
            }
        }
        test.draw(window);

        for(unsigned i = 0; i < roadObj.size(); ++i)
        {
            roadObj[i].draw(window);
        }
        for(unsigned i = 0; i < pointObj.size(); ++i)
        {
            window.draw(pointObj[i].circle);
        }

        if(roadbool)
        {
            tmpRoadShadow.setShadow(sf::Mouse::getPosition(window));
            tmpRoadShadow.draw(window);
        }
        window.draw(fieldForEdit);

        window.display();


    }

}
