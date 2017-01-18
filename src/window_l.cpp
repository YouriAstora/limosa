#include "window_l.h"

Window_L::Window_L(unsigned int w, unsigned int h)
{
    create(sf::VideoMode(w,h),"Limosa");
    setFramerateLimit(60);
    //setVerticalSyncEnabled(true);

//    m_view.setSize((float)w,(float)h);
//    setView(m_view);
}

void Window_L::update_view_position(float x, float y)
{
    m_view.setCenter(x, y);
    setView(m_view);
}

void Window_L::update_size(sf::Vector2u size)
{
    setSize(size);
    m_view.setSize((float)size.x,(float)size.y);
    setPosition(sf::Vector2i(0,0));
}
