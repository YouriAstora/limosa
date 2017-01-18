#include "tools.h"

Tools Tools::m_instance=Tools();

Tools::Tools()
{
    if (!m_font.loadFromFile("fonts/Roboto-Thin.ttf"))
    {
        printf("ERROR\n");
        // error...
    }
}

Tools::~Tools()
{
}

Tools& Tools::Instance()
{
    return m_instance;
}


sf::Font Tools::get_font()
{
    return m_font;
}
