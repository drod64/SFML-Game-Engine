#ifndef SGE_VEC3_H
#define SGE_VEC3_H
#include <SGE/util/Precision.h>

namespace sge {

class Vec3 {
public:
    real x;
    real y;
    real z;

    /**
     * Default constructor.
     */
    Vec3();

    /**
     * Explicit constructor.
     * @param x the x-axis position
     * @param y the y-axis position
     * @param z the z-axis position
     */
    Vec3(real x, real y, real z);

    void invert();

    real magnitude() const;

    real sqrMagnitude() const;

    void normalize();
    
    Vec3& operator = (const Vec3 &vec);
    Vec3& operator *= (real scalar);
    Vec3& operator += (const Vec3 &vec);
    Vec3& operator -= (const Vec3 &vec);
    Vec3& operator %= (const Vec3 & vec);
    
    Vec3 operator * (const real scalar) const;
    Vec3 operator + (const Vec3 &vec) const;
    Vec3 operator - (const Vec3 &vec) const;
    Vec3 operator % (const Vec3 &vec) const;

    
    Vec3& componentProductUpdate(const Vec3 &vec);
    Vec3& addScaledVector(const Vec3 &vec, real scalar);

    real dotProduct(const Vec3 &vec) const;
    Vec3 componentProduct(const Vec3 &vec) const;
    Vec3 vectorProduct(const Vec3 &vec) const;

private:
    float _pad;
};

} // namespace sge

#endif // SGE_VEC3_H