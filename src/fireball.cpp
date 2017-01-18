#include "fireball.h"
#include "tools.h"

Fireball::Fireball():
    ball(3),
    death_mark(false),
    m_active(false)
{
    Tools& g_tools=Tools::Instance();

    ball.setFillColor(sf::Color(10, 10, 10));
    ball.setOrigin(sf::Vector2f(3, 3));
    //ball.setOutlineThickness(1);
    //ball.setOutlineColor(sf::Color(255, 255, 255));

    m_angle = 0;
    m_speed = 200;
    m_radial_speed = 200;

    number.setFont(g_tools.m_font);
    number.setColor(sf::Color::Green);
    number.setCharacterSize(18);
    number.setStyle(sf::Text::Bold);
    number.setPosition(0,0);
    number.setOrigin(5,10);
}

void Fireball::set_active(bool active)
{
    m_active = active;
    death_mark = false;
}

bool Fireball::get_active() const
{
    return m_active;
}

sf::Vector2f Fireball::getPosition()
{
    return ball.getPosition();
}

void Fireball::setPosition(float x, float y)
{
    ball.setPosition(x, y);
}

float Fireball::get_angle()
{
    return m_angle;
}

void Fireball::set_angle(float angle)
{
    m_angle = angle;
}

int Fireball::get_id()
{
    return m_id;
}

void Fireball::set_id(int id)
{
    Tools& g_tools=Tools::Instance();

    m_id = id;
    number.setString(g_tools.to_string(id));
}

unsigned int Fireball::get_player()
{
    return m_player;
}

void Fireball::set_player(unsigned int player)
{
    m_player = player;
    switch(m_player)
    {
    case 0:
        ball.setFillColor(sf::Color(255, 10, 10));
        break;
    case 1:
        ball.setFillColor(sf::Color(10, 255, 10));
        break;
    case 2:
        ball.setFillColor(sf::Color(10, 10, 255));
        break;
    default:
        ball.setFillColor(sf::Color(200, 200, 200));
        break;
    }

}

void Fireball::update_position(float lap)
{
    float true_speed = (float) (m_speed * lap);
    float true_radial_speed = (float) (m_radial_speed * lap);

    float x = ball.getPosition().x;
    float y = ball.getPosition().y;

//    if (sf::Keyboard::isKeyPressed(m_commands[2]))
//        set_angle(get_angle() - true_radial_speed);
//    if (sf::Keyboard::isKeyPressed(m_commands[3]))
//        set_angle(get_angle() + true_radial_speed);

    float mx = true_speed * cos(PI * get_angle() / 180);
    float my = true_speed * sin(PI * get_angle() / 180);

    if (x < 0 || x > 1280 || y < 0 | y > 720)
    {
        death_mark = true;
    }

    ball.move(mx, my);
    number.setPosition(ball.getPosition().x, ball.getPosition().y);
    //ball.setRotation(get_angle() + 90);
}

void Fireball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(ball, states);
    //target.draw(number);
}
