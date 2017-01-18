#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "SFML/Graphics.hpp"

class Obstacle : public sf::CircleShape
{
public:
    Obstacle();
    bool is_touched(float x, float y);
};

#endif // OBSTACLE_H
