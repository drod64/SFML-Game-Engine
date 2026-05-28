#ifndef SGE_ACTION_H
#define SGE_ACTION_H
#include <string>

namespace sge {

class Action {
private:
    std::string _name;
    std::string _type;

public:
    Action();
    Action(const std::string &name, const std::string &type);

    // Getters
    const std::string& getName() const;
    const std::string& getType() const;

    // Setters
    void setName(const std::string &name);
    void setType(const std::string &type);
};

} // namespace sge

#endif // SGE_ACTION_H