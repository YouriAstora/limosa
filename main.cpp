#include "src/time_l.h"
#include "src/window_l.h"
#include "src/player.h"
#include "src/fireballs.h"
#include "src/obstacle.h"
#include "src/tools.h"
#include "src/particlesystem.h"

#define W_WIDTH 1280
#define W_HEIGHT 720

#define NB_PLAYERS 3
#define NB_OBSTACLES 3

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Window_L window(W_WIDTH, W_HEIGHT);
    Time_L time;

    Tools& g_tools=Tools::Instance();

    g_tools.m_font.loadFromFile("fonts/Roboto-Thin.ttf");
    sf::Text fps_text;
    fps_text.setFont(g_tools.m_font);
    fps_text.setCharacterSize(24);
    fps_text.setColor(sf::Color::Blue);
    fps_text.setStyle(sf::Text::Bold);
    fps_text.setPosition(0,0);

    sf::RectangleShape background(sf::Vector2f(W_WIDTH,W_HEIGHT));
    background.setFillColor(sf::Color(25, 25, 25));

    Obstacle obstacles[NB_OBSTACLES];
    obstacles[0].setPosition(600,300);
    obstacles[1].setPosition(300,150);
    obstacles[2].setPosition(1000,500);

    Player players[NB_PLAYERS];
    players[0].set_id(0);
    players[0].setPosition(5,5);
    players[0].set_angle(45);
    players[0].set_commands(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);
    players[1].set_id(1);
    players[1].setPosition(W_WIDTH-5,5);
    players[1].set_angle(135);
    players[1].set_commands(sf::Keyboard::Z, sf::Keyboard::S, sf::Keyboard::Q, sf::Keyboard::D);
    players[2].set_id(2);
    players[2].setPosition(5,W_HEIGHT-5);
    players[2].set_angle(-45);
    players[2].set_commands(sf::Keyboard::I, sf::Keyboard::K, sf::Keyboard::J, sf::Keyboard::L);

    Fireballs fireballs;

    ParticleSystem particles[3];

    bool start = false;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyReleased)
            {
                for (int i=0; i<NB_PLAYERS; i++)
                {
                    if (event.key.code == players[i].get_fire_command() && players[i].get_alive() && players[i].get_warm())
                    {
                        fireballs.add(players[i].getPosition().x, players[i].getPosition().y, players[i].get_angle(), i);
                        players[i].set_warm(false);
                        //players[i].recoil();
                    }
                }
            }
        }
        time.step();
        fps_text.setString(g_tools.to_string(time.get_framerate()));

        if (start)
        {
            float lap = time.lap_s();
            for (int o=0; o<NB_OBSTACLES; o++)
            {
                fireballs.is_touching_obstacle(&(obstacles[o]));
            }
            for (int i=0; i<NB_PLAYERS; i++)
            {
                if (fireballs.is_touching_player(&(players[i])))
                {
                    unsigned int new_life = players[i].get_life() - 1;
                    players[i].set_life(new_life);
                }
                for (int o=0; o<NB_OBSTACLES; o++)
                {
                    if(obstacles[o].is_touched(players[i].getPosition().x, players[i].getPosition().y))
                        players[i].set_alive(false);
                }
                for (int j=0; j<NB_PLAYERS; j++)
                {
                    if (i != j)
                    {
                        if (players[i].is_touched(players[j].getPosition().x, players[j].getPosition().y))
                        {
                            players[j].set_alive(false);
                        }
                    }
                }
                players[i].update_position(lap);
            }
            fireballs.update(lap);
//            for (int i=0; i<3; i++)
//            {
//                particles[i].setEmitter(players[i].getPosition());
//                particles[i].update(time.lap());
//            }
        }
        else
            start = true;

        window.clear();
        window.draw(background);
        for (int i=0; i<NB_OBSTACLES; i++)
        {
            window.draw(obstacles[i]);
        }
        window.draw(fireballs);
        for (int i=0; i<NB_PLAYERS; i++)
        {
            window.draw(players[i]);
        }
//        for (int i=0; i<3; i++)
//        {
//            window.draw(particles[i]);
//        }
        window.draw(fps_text);
        window.display();

    }

    return 0;
}
