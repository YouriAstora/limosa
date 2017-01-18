#include "fireballs.h"
#include "tools.h"

Fireballs::Fireballs():
    marker(0)
{

}

void Fireballs::add(float x, float y, float angle, unsigned int i)
{
    m_fireballs[marker].setPosition(x, y);
    m_fireballs[marker].set_angle(angle);
    m_fireballs[marker].set_active(true);
    m_fireballs[marker].set_id(marker);
    m_fireballs[marker].set_player(i);
    marker = (marker + 1) % MAX_BALLS;
}

void Fireballs::remove(unsigned int i)
{
    m_fireballs[i].set_active(false);
}

void Fireballs::update(float lap)
{
    for (unsigned int i=0; i < MAX_BALLS; i++)
        if (m_fireballs[i].get_active())
        {
            if (m_fireballs[i].death_mark)
                remove(i);
            else
                m_fireballs[i].update_position(lap);
        }
}

void Fireballs::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (unsigned int i=0; i < MAX_BALLS; i++)
        if (m_fireballs[i].get_active())
            target.draw(m_fireballs[i], states);
}

bool Fireballs::is_touching_player(Player* player)
{
    int ip = player->get_id();
    for (unsigned int i=0; i < MAX_BALLS; i++)
        if (m_fireballs[i].get_active() && m_fireballs[i].get_player() != ip)
        {
            if (player->is_touched(m_fireballs[i].getPosition().x, m_fireballs[i].getPosition().y))
            {
                remove(i);
                return true;
            }
        }
    return false;
}

bool Fireballs::is_touching_obstacle(Obstacle* obstacle)
{
    for (unsigned int i=0; i < MAX_BALLS; i++)
        if (m_fireballs[i].get_active())
        {
            if (obstacle->is_touched(m_fireballs[i].getPosition().x, m_fireballs[i].getPosition().y))
            {
                float a = atan2(m_fireballs[i].getPosition().y - obstacle->getPosition().y, m_fireballs[i].getPosition().x - obstacle->getPosition().x);
                m_fireballs[i].set_angle(a*180/PI);
                m_fireballs[i].set_player(100);
                return true;
            }
        }
    return false;
}

