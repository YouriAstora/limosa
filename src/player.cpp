#include "player.h"
#include "tools.h"
#define PI 3.14159265
#define MAX_LIFE 60
#define SAVE_LAP 0.08
#define COOLDOWN 0
#define BUFFER_RATIO 5


void Player::init_body_color()
{
    m_color.r = 10;
    m_color.g = 10;
    m_color.b = 10;
    switch(m_id)
    {
    case 0:
        m_color.r = 240;
        break;
    case 1:
        m_color.g = 240;
        break;
    case 2:
        m_color.b = 240;
        break;
    case 3:
        m_color.r = 240;
        m_color.g = 240;
        break;
    case 4:
        m_color.g = 240;
        m_color.b = 240;
        break;
    case 5:
        m_color.r = 240;
        m_color.b = 240;
        break;
    default:
        m_color.r = 240;
        m_color.g = 240;
        m_color.b = 240;
        break;
    }
}
sf::Color Player::get_body_color(int part)
{
    switch(m_id)
    {
    case 0:
        return sf::Color(m_color.r - part*4, m_color.g, m_color.b);
    case 1:
        return sf::Color(m_color.r, m_color.g - part*4, m_color.b);
    case 2:
        return sf::Color(m_color.r, m_color.g, m_color.b - part*4);
    case 3:
        return sf::Color(m_color.r - part*4, m_color.g - part*4, m_color.b);
    case 4:
        return sf::Color(m_color.r, m_color.g - part*4, m_color.b - part*4);
    case 5:
        return sf::Color(m_color.r - part*4, m_color.g, m_color.b - part*4);
    default:
        return sf::Color(m_color.r - part*4, m_color.g, m_color.b);
    }
}

Player::Player():
    head(5),
    m_life(60),
    m_alive(true),
    m_recoil(false)
{
    m_color.r = 240;
    m_color.g = 240;
    m_color.b = 240;
    head.setFillColor(sf::Color(255, 255, 255));
    head.setOrigin(sf::Vector2f(5, 5));
    for (int i = 0; i < m_life; i++)
    {
        sf::RectangleShape body_part(sf::Vector2f(6, 6));
        body_part.setFillColor(sf::Color::White);
        body_part.setOrigin(sf::Vector2f(3, 3));
        body_part.setOutlineThickness(1);
        body_part.setOutlineColor(sf::Color(50, 50, 50));
        body.push_back(body_part);
    }
    for (int i = 0; i < MAX_LIFE * BUFFER_RATIO; i++)
    {
        last_positions.push_back(sf::Vector2f(0, 0));
        last_angles.push_back(0);
    }

    m_angle = 0;
    m_speed = 117;
    m_radial_speed = 200;
}

void Player::set_commands(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right)
{
    m_commands[0] = up;
    m_commands[1] = down;
    m_commands[2] = left;
    m_commands[3] = right;
}

sf::Keyboard::Key Player::get_fire_command()
{
    return m_commands[0];
}

unsigned int Player::get_id()
{
    return m_id;
}

void Player::set_id(unsigned int id)
{
    m_id = id;
    init_body_color();
    for (int i = 0; i < m_life; i++)
    {
        body.at(i).setFillColor(get_body_color(i));
    }
}

float Player::get_angle()
{
    return m_angle;
}

void Player::set_angle(float angle)
{
    m_angle = angle;
}

void Player::update_position(float lap)
{
    float true_speed = (float) (m_speed * lap);
    float true_radial_speed = (float) (m_radial_speed * lap);

    float x = head.getPosition().x;
    float y = head.getPosition().y;

    if (x < 0 || x > 1280 || y < 0 || y > 720)
        set_alive(false);

    float factor = 1;
    float jitter = 0;
    if (m_recoil)
    {
        factor = -2;
        jitter = 5 * ( 2 * (float)random() / RAND_MAX - 1);
        m_recoil = false;
    }
    if (sf::Keyboard::isKeyPressed(m_commands[2]))
        set_angle(get_angle() - true_radial_speed);
    if (sf::Keyboard::isKeyPressed(m_commands[3]))
        set_angle(get_angle() + true_radial_speed);

    set_angle(get_angle() + jitter);
    float mx = factor * true_speed * cos(PI * get_angle() / 180);
    float my = factor * true_speed * sin(PI * get_angle() / 180);

    if (m_alive)
    {
        head.move(mx, my);
        head.setRotation(get_angle() + 90);
    }

    for (int i = 0; i < m_life; i++)
    {
        body.at(i).setPosition(last_positions.at((marker - 1 - i * BUFFER_RATIO) % (MAX_LIFE * BUFFER_RATIO)));
        body.at(i).setRotation(last_angles.at((marker - 1 - i * BUFFER_RATIO) % (MAX_LIFE * BUFFER_RATIO)));
    }

    if (!get_warm())
    {
        m_cooldown += lap;
        if (m_cooldown > COOLDOWN)
        {
            set_warm(true);
            m_cooldown = 0;
        }
    }

    if (m_alive)
    {
        save_time += lap;
        if (save_time >= SAVE_LAP / (float) BUFFER_RATIO)
        {
            last_positions.at(marker % (MAX_LIFE * BUFFER_RATIO)) = sf::Vector2f(x + mx, y + my);
            last_angles.at(marker % (MAX_LIFE * BUFFER_RATIO)) = get_angle();
            marker++;
            save_time = 0;
        }
    }
}

void Player::setPosition(float x, float y)
{
    head.setPosition(x, y);
    for (int i = 0; i < m_life; i++)
        body.at(i).setPosition(x, y);

}

sf::Vector2f Player::getPosition()
{
    return head.getPosition();
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int i = 1; i <= m_life; i++)
        target.draw(body.at(m_life - i), states);
    target.draw(head, states);
}

unsigned int Player::get_life()
{
    return m_life;
}

void Player::set_life(unsigned int life)
{
    if (life < MAX_LIFE)
    {
        body.clear();
        for (int i = 0; i < life; i++)
        {
            sf::RectangleShape body_part(sf::Vector2f(6, 6));
            if (m_alive)
                body_part.setFillColor(get_body_color(i));
            else
                body_part.setFillColor(sf::Color(45,45,45));
            body_part.setOrigin(sf::Vector2f(3, 3));
            body_part.setOutlineThickness(1);
            body_part.setOutlineColor(sf::Color(50, 50, 50));
            body.push_back(body_part);
        }
        m_life = life;
        if (m_life == 0)
            set_alive(false);
    }
}

void Player::recoil()
{
    m_recoil = true;
}

bool Player::is_touched(float x, float y)
{
    Tools& g_tools=Tools::Instance();
    for (int i = 0; i < m_life; i++)
    {
        float xb = body.at(i).getPosition().x;
        float yb = body.at(i).getPosition().y;
        if (g_tools.square_distance(x, y, xb, yb) < 25)
            return true;
    }
    return false;
}

bool Player::get_alive()
{
    return m_alive;
}

void Player::set_alive(bool alive)
{
    m_alive = alive;
    if(!alive)
        for (int i = 0; i < m_life; i++)
        {
            body.at(i).setFillColor(sf::Color(45,45,45));
        }
}

bool Player::get_warm()
{
    return m_warm;
}

void Player::set_warm(bool warm)
{
    m_warm = warm;
}

