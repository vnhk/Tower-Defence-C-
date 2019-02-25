#include "Animation.h"


Animation::Animation(struct Animation_Parameters AP)
{
    amountOfImages = AP.amountOfImages-1;
    animationTime = AP.time_ms;
    sizeX = AP.sizeX;
    sizeY = AP.sizeY;
    dimensions = AP.dimensions;
    texture = AP.texture;
    actualRow = 0;
    last = -1;
    on = true;
    numberOfReptitions = AP.numberOfReptitions;
    loopRow = AP.loopRow;
}
Animation::Animation()
{
    
}

void Animation::setParameters(struct Animation_Parameters AP)
{
    amountOfImages = AP.amountOfImages-1;
    animationTime = AP.time_ms;
    sizeX = AP.sizeX;
    sizeY = AP.sizeY;
    dimensions = AP.dimensions;
    texture = AP.texture;
    actualRow = 0;
    last = -1;
    numberOfReptitions=AP.numberOfReptitions;
    actualNumberOfReptitions = 0;
    loopRow = AP.loopRow;
}
   
   
void Animation::changeAnimation(int direction)
{
    if(last == direction)
        return;
    last = direction;

    //dol/lew/pr/gor/
    actualRow = direction;
}

Animation::~Animation()
{
}

bool Animation::getOn()
{
    return on;
}

void Animation::Update(sf::Sprite &sprite)
{
    time = clock.getElapsedTime();
    if (time.asMilliseconds() >= animationTime / dimensions.x)
    {
        if (numberOfReptitions > 0)
        {
            if (actualNumberOfReptitions >= numberOfReptitions * dimensions.x * dimensions.y - 1)
            {
                on = false;
                return;
            }
            actualNumberOfReptitions++;
        }
        if (actualImage == amountOfImages)
            actualImage = 0;
        else
            actualImage++;
        if (loopRow == false)
        {
            if (actualImage % dimensions.x == 0)
                actualRow++;
            if (actualRow >= dimensions.y)
                actualRow = 0;
        }
        sprite.setTextureRect(sf::IntRect(actualImage % (dimensions.x) * sizeX, actualRow * sizeY, sizeX, sizeY)); //0
        clock.restart();
    }
}

void Animation::Start()
{
    clock.restart();
    on = true;
    actualNumberOfReptitions = 0;
}

void Animation_Parameters::update(sf::Texture texture, sf::Vector2u dimensions, unsigned time_ms, bool loopRow, int numberOfReptitions)
{
    this->texture = texture;
    amountOfImages = dimensions.x * dimensions.y;
    this->dimensions.x = dimensions.x;
    this->dimensions.y = dimensions.y;
    this->time_ms = time_ms;
    this->numberOfReptitions = numberOfReptitions;
    sizeX = texture.getSize().x / dimensions.x;
    sizeY = texture.getSize().y / dimensions.y;
    this->loopRow = loopRow;
}