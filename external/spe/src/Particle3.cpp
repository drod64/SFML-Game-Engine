#include <SPE/Particle3.h>

spe::Particle3::Particle3()
:
position(0,0,0),
velocity(0,0,0),
acceleration(0,0,0),
damping(0.5f),
inverseMass(0)
{}

spe::Particle3::Particle3(const sm::Vec3 &pos, const sm::Vec3 &vel, const sm::Vec3 &acc, sm::real damping)
:
Particle3()
{
    this->position = pos;
    this->velocity = vel;
    this->acceleration = acc;
    this->damping = damping;
}

void spe::Particle3::setInverseMass(sm::real inverseMass)
{
    this->inverseMass = inverseMass;
}

void spe::Particle3::setMass(sm::real mass)
{
    this->inverseMass = 1.0f / mass;
}

sm::real spe::Particle3::getInverseMass() const
{
    return this->inverseMass;
}

sm::real spe::Particle3::getMass() const
{
    return 1.0f / this->inverseMass;
}