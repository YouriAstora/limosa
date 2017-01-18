#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"

class Player : public sf::Drawable, public sf::Transformable
{
public:
    Player();

    void set_commands(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right);
    sf::Keyboard::Key get_fire_command();

    unsigned int get_id();
    void set_id(unsigned int id);

    float get_angle();
    void set_angle(float angle);
    void update_position(float lap);

    sf::Vector2f getPosition();
    void setPosition(float x, float y);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    unsigned int get_life();
    void set_life(unsigned int life);
    bool is_touched(float x, float y);

    bool get_alive();
    void set_alive(bool alive);

    void recoil();

    bool get_warm();
    void set_warm(bool warm);

private:
    sf::CircleShape head;
    std::vector<sf::RectangleShape> body;
    sf::Keyboard::Key m_commands[4];

    float m_angle;
    int m_speed;
    int m_radial_speed;

    unsigned int m_life;
    bool m_alive;

    bool m_recoil;
    bool m_warm;
    float m_cooldown;

    std::vector<sf::Vector2f> last_positions;
    std::vector<int> last_angles;
    unsigned int marker;
    float save_time;

    unsigned int m_id;

    sf::Color m_color;
    void init_body_color();
    sf::Color get_body_color(int part);
};

#endif // PLAYER_H
