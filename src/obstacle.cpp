#include "obstacle.h"
#include "tools.h"

Obstacle::Obstacle():
    sf::CircleShape(50)
{
    setOrigin(50,50);
    setFillColor(sf::Color(0, 0, 0));
}

bool Obstacle::is_touched(float x, float y)
{
    Tools& g_tools = Tools::Instance();
    if(g_tools.square_distance(x, y, getPosition().x, getPosition().y) < getRadius()*getRadius())
        return true;
    else
        return false;

}
