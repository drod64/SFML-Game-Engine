#include <SGE/util/Action.h>

sge::Action::Action() :
Action("NONE", "NONE") {}

sge::Action::Action(const std::string &name, const std::string &type) :
_name(name), _type(type) {}

const std::string& sge::Action::getName() const
{
    return this->_name;
}

const std::string& sge::Action::getType() const
{
    return this->_type;
}

void sge::Action::setName(const std::string &name)
{
    this->_name = name;
}

void sge::Action::setType(const std::string &type)
{
    this->_type = type;
}