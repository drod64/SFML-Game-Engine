#ifndef SGE_CSHAPE_COMPONENT_H
#define SGE_CSHAPE_COMPONENT_H
#include <SFML/Graphics/CircleShape.hpp>
#include <SGE/components/Component.h>

namespace sge
{

class CShape : public Component {
public:
    sf::CircleShape shape;

    CShape();
    CShape(float radius, int points, const sf::Color &fillColor, const sf::Color &outlineColor, float outlineThickness);
};

} // namespace sge

#endif // SGE_CSHAPE_COMPONENT_H