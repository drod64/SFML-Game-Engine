#include <SGE/Components/CShape.h>

namespace sge
{

    CShape::CShape() :
    CShape(10.f, 4.f, sf::Color(255, 255, 255), sf::Color(0, 0, 0), 2.f)
    {}

    CShape::CShape(float radius, int points, const sf::Color &fillColor, const sf::Color &outlineColor, float outlineThickness) :
    shape(radius, points)
    {
        this->shape.setFillColor(fillColor);
        this->shape.setOutlineColor(outlineColor);
        this->shape.setOutlineThickness(outlineThickness);
        this->shape.setOrigin(radius, radius);
    }

} // namespace sge