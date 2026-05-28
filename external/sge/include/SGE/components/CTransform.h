#ifndef SGE_CTRANSFORM_H
#define SGE_CTRANSFORM_H
#include <SGE/util/Vec2.h>
#include <SGE/components/Component.h>
#include <initializer_list>

namespace sge {

class CTransform : public Component {
public:
    sge::Vec2 position;
    sge::Vec2 prevPosition;
    sge::Vec2 velocity;
    sge::Vec2 scale;
    float angle;

    CTransform();
    CTransform(const CTransform &otherTransform);
    CTransform(const sge::Vec2 &position, const sge::Vec2 &velocity, float angle);


    ~CTransform();
    CTransform& operator = (const CTransform &otherTransform);
};

}

#endif // SGE_CTRANSFORM_H