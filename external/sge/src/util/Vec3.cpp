#include <sge/util/Vec3.h>

sge::Vec3::Vec3()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->_pad = 0;
}

sge::Vec3::Vec3(real x, real y, real z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->_pad = 0;
}

void sge::Vec3::invert()
{
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
}

sge::real sge::Vec3::magnitude() const
{
    return real_sqrt(this->x * this->x +
                    this->y * this->y +
                    this->z * this->z);
}

sge::real sge::Vec3::sqrMagnitude() const
{
    return  this->x * this->x +
            this->y * this->y +
            this->z * this->z;
}

void sge::Vec3::normalize()
{
    real mag = this->magnitude();

    if (mag > 0)
    {
        *this *= ((real)1 / mag);
    }
}

sge::Vec3& sge::Vec3::operator = (const sge::Vec3 &vec)
{
    if (this != &vec)
    {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }
    
    return *this;
}

sge::Vec3& sge::Vec3::operator *= (real scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    
    return *this;
}

sge::Vec3& sge::Vec3::operator += (const sge::Vec3 &vec)
{
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;

    return *this;
}

sge::Vec3& sge::Vec3::operator -= (const sge::Vec3 &vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
    this->z -= vec.z;
    
    return *this;
}

sge::Vec3& sge::Vec3::operator %= (const sge::Vec3 &vec)
{
    *this = *this % vec;

    return *this;
}

sge::Vec3 sge::Vec3::operator * (real scalar) const
{
    return Vec3(this->x * scalar, this->y * scalar, this->z * scalar);
}

sge::Vec3 sge::Vec3::operator + (const sge::Vec3 &vec) const
{
    return Vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

sge::Vec3 sge::Vec3::operator - (const sge::Vec3 &vec) const
{
    return Vec3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}

sge::Vec3 sge::Vec3::operator % (const sge::Vec3 &vec) const
{
    return Vec3(this->y * vec.z - this->z * vec.y,
                this->z * vec.x - this->x * vec.z,
                this->x * vec.y - this->y * vec.y);
}

sge::Vec3& sge::Vec3::componentProductUpdate(const sge::Vec3 &vec)
{
    this->x *= vec.x;
    this->y *= vec.y;
    this->z *= vec.z;
}

sge::Vec3& sge::Vec3::addScaledVector(const sge::Vec3 &vec, real scalar)
{
    this->x += (vec.x * scalar);
    this->y += (vec.y * scalar);
    this->z += (vec.z * scalar);

    return *this;
}

sge::real sge::Vec3::dotProduct(const sge::Vec3 &vec) const
{
    return  this->x * vec.x +
            this->y * vec.y +
            this->z * vec.z;
}

sge::Vec3 sge::Vec3::componentProduct(const sge::Vec3 &vec) const
{
    return Vec3(this->x * vec.x, this->y * vec.y, this->z * vec.z);
}

sge::Vec3 sge::Vec3::vectorProduct(const sge::Vec3 &vec) const
{
    return *this % vec;
}