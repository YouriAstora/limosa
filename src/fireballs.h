#ifndef FIREBALLS_H
#define FIREBALLS_H

#include "fireball.h"
#include "player.h"
#include "obstacle.h"

#define MAX_BALLS 50

class Fireballs : public sf::Drawable, public sf::Transformable
{
public:
    Fireballs();

    void add(float x, float y, float angle, unsigned int i);
    void remove(unsigned int i);

    void update(float lap);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    bool is_touching_player(Player* player);
    bool is_touching_obstacle(Obstacle *obstacle);
private:
    Fireball m_fireballs[MAX_BALLS];
    int marker;
};

#endif // FIREBALLS_H
