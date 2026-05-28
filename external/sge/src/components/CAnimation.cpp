#include <SGE/components/CAnimation.h>

sge::CAnimation::CAnimation()
{}

sge::CAnimation::CAnimation(const sge::Animation &animation, bool repeat)
{
    this->animation = animation;
    this->repeat = repeat;
}