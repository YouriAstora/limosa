#ifndef WINDOW_L_H
#define WINDOW_L_H

#include <SFML/Graphics.hpp>

class Window_L : public sf::RenderWindow
{
public:
    Window_L(unsigned int w, unsigned int h);

    void update_view_position(float x, float y);
    void update_size(sf::Vector2u size);

private :
        sf::View m_view;
};

#endif // WINDOW_L_H
