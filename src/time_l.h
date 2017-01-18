#ifndef TIME_L_H
#define TIME_L_H

#include <SFML/Graphics.hpp>

class Time_L : public sf::Clock
{
public:
    Time_L();

    void step();
    void pause();
    sf::Time lap();
    float lap_s();
    float lap_ms();
    sf::Time total();
    void clean();
    void print_framerate();
    unsigned int get_framerate();

private :
    sf::Time m_lap;
    sf::Time m_total;
    bool m_state;
};

#endif // TIME_L_H
