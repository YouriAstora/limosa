#include "time_l.h"

Time_L::Time_L()
{
    m_lap = sf::seconds(0);
    m_total = sf::seconds(0);
    m_state = 0;
}

void Time_L::step()
{
    if (m_state == 1)
    {
        restart();
        m_state = 0;
    }
    else
    {
        m_lap = restart();
        m_total += m_lap;
    }
}

void Time_L::pause()
{
    if (m_state == 0)
    {
        m_lap = getElapsedTime();
        m_total += m_lap;
        m_state = 1;
    }
    restart();
}

sf::Time Time_L::lap()
{
    return m_lap;
}

float Time_L::lap_s()
{
    return m_lap.asSeconds();
}

float Time_L::lap_ms()
{
    return m_lap.asMilliseconds();
}

sf::Time Time_L::total()
{
    return m_total;
}

void Time_L::clean()
{
    m_total = sf::seconds(0);
    m_lap = sf::seconds(0);
}

void Time_L::print_framerate()
{
    printf("fps : %d\n", (int)(1.f / m_lap.asSeconds()));
}

unsigned int Time_L::get_framerate()
{
    return (unsigned int)(1.f / m_lap.asSeconds());
}
