#ifndef SPE_PARTICLE_H
#define SPE_PARTICLE_H
#include <SM/Vec3.h>

namespace spe {

class Particle3 {
public:
    sm::Vec3 position;

    sm::Vec3 velocity;

    sm::Vec3 acceleration;
};

} // namespace spe

#endif // SPE_PARTICLE_H