#include "particlesystem.h"
#include <cmath>

ParticleSystem::ParticleSystem() :
    m_particles(50),
    m_vertices(sf::Points, 50),
    m_lifetime(sf::seconds(3)),
    m_emitter(0, 0)
{
}

void ParticleSystem::setEmitter(sf::Vector2f position)
{
    m_emitter = position;
}

void ParticleSystem::update(sf::Time elapsed)
{
    for (std::size_t i = 0; i < m_particles.size(); ++i)
    {
        // on met à jour la durée de vie de la particule
        Particle& p = m_particles[i];
        p.lifetime -= elapsed;

        // si la particule est arrivée en fin de vie, on la réinitialise
        if (p.lifetime <= sf::Time::Zero)
            resetParticle(i);

        // on met à jour la position du vertex correspondant
        m_vertices[i].position += p.velocity * elapsed.asSeconds();

        // on met à jour l'alpha (transparence) de la particule en fonction de sa durée de vie
        float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
        m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
    }
}

void ParticleSystem::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // on applique la transformation
    states.transform *= getTransform();

    // nos particules n'utilisent pas de texture
    states.texture = NULL;

    // on dessine enfin le vertex array
    target.draw(m_vertices, states);
}

void ParticleSystem::resetParticle(std::size_t index)
{
    // on donne une vitesse et une durée de vie aléatoires à la particule
    float angle = (std::rand() % 360) * 3.14f / 180.f;
    float speed = (std::rand() % 50) + 50.f;
    m_particles[index].velocity = sf::Vector2f(cos(angle) * speed, sin(angle) * speed);
    m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

    // on remet à zéro la position du vertex correspondant à la particule
    m_vertices[index].position = m_emitter;
}
