#ifndef FIREBALL_H
#define FIREBALL_H

#include "SFML/Graphics.hpp"

class Fireball : public sf::Drawable, public sf::Transformable
{
public:
    Fireball();

    void set_active(bool active);
    bool get_active() const;

    float get_angle();
    void set_angle(float angle);
    void update_position(float lap);

    sf::Vector2f getPosition();
    void setPosition(float x, float y);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    bool death_mark;

    int get_id();
    void set_id(int id);
    unsigned int get_player();
    void set_player(unsigned int player);

private:
    sf::CircleShape ball;
    sf::Text number;
    bool m_active;

    float m_angle;
    int m_speed;
    int m_radial_speed;

    int m_id;
    int m_player;
};

#endif // FIREBALL_H
