#include "Wire.h"

Wire::Wire(std::string _name, size_t _level) : name{split(_name)}, level{_level} {}

void Wire::set_name(std::string _name) { name = split(_name); }
void Wire::set_level(size_t _level) { level = _level; }
std::string Wire::get_name() { return name; }
size_t Wire::get_level() { return level; }
void Wire::disp()
{
    std::cout << "name:" << name << ",level:" << level << ",value:" << value << std::endl;
}
bool Wire::is_valid()
{
    if (name == "" || name == "\r")
        return false;
    return true;
}
std::string Wire::split(std::string s)
{
    std::string ss{};
    for (auto x : s)
    {
        if (static_cast<int>(x) < 127 && static_cast<int>(x) > 32 && static_cast<int>(x) != 59)
            ss += x;
    }
    return ss;
}

bool Wire::operator==(Wire v)
{
    if (split(v.name) == split(this->name))
        return true;
    return false;
}

char Wire::getvalue() { return value; }
void Wire::setvalue(char v) { value = v; }
