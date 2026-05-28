#ifndef SGE_CBOUNDING_BOX
#define SGE_CBOUNDING_BOX
#include <sge/components/Component.h>
#include <sge/util/Vec2.h>

namespace sge {
class CBoundingBox : public Component {
private:
    sge::Vec2 m_size;
    sge::Vec2 m_halfSize;

public:
    CBoundingBox();
    CBoundingBox(const CBoundingBox &otherBox);
    CBoundingBox(const Vec2 &size);

    sge::Vec2 size() const;
    sge::Vec2 halfSize() const;

    void setSize(const sge::Vec2 &size);

};
}

#endif // SGE_CBOUNDING_BOX