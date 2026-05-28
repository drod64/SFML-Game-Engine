#ifndef SGE_CINPUT_H
#define SGE_CINPUT_H
#include <SGE/components/Component.h>

namespace sge {

class CInput : public Component {
public:
    bool up;
    bool down;
    bool right;
    bool left;
    bool shoot;

    CInput();
};

} // namespace sge

#endif // SGE_CINPUT_H