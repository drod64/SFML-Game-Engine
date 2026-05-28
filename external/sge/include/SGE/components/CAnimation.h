#ifndef SGE_CANIMATION_H
#define SGE CANIMATION_H
#include <SGE/util/Animation.h>
#include <SGE/components/Component.h>

namespace sge {

class CAnimation : public Component {
public:
    sge::Animation animation;
    bool repeat = false;

    CAnimation();
    CAnimation(const sge::Animation &animation, bool repeat);
};

}

#endif // SGE_CANIMATION_H