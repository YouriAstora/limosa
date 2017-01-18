#ifndef TOOLS_H
#define TOOLS_H

#include <sstream>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#define PI 3.14159265

class Tools
{
public:
    static Tools& Instance();

    sf::Font get_font();

    template <typename T>
    std::string to_string(T value)
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
    int square_distance(float x0, float y0, float x1, float y1){
        int value = (x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0);
        return value;
    }
    sf::Font m_font;

private:
    Tools& operator= (const Tools&){}
    Tools (const Tools&){}

    static Tools m_instance;
    Tools();
    ~Tools();

};

#endif // TOOLS_H
