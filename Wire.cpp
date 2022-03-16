#include "Wire.h"

Wire::Wire(std::string _name, size_t _level) : name{split(_name)}, level{_level} {}

void Wire::set_name(std::string _name) { name = split(_name); }
void Wire::set_level(size_t _level) { level = _level; }
std::string Wire::get_name() const { return name; }
size_t Wire::get_level() const { return level; }
void Wire::disp() const { std::cout << "(name:" << name << ",level:" << level << ",value:" << value << ",controllability:" << controllability << ")"; }
bool Wire::is_valid() const { return (name == "" || name == "\r") ? false : true; }
std::string Wire::split(std::string str) const
{
    std::string result{};
    for (auto s_char : str)
        if (static_cast<int>(s_char) < 127 && static_cast<int>(s_char) > 32 && static_cast<int>(s_char) != 59)
            result += s_char;
    return result;
}

bool Wire::operator==(const Wire &v) const { return split(v.name) == split(this->name) ? true : false; }

char Wire::getvalue() const { return value; }
void Wire::setvalue(char v) { value = v; }

double Wire::getcontrollability() const { return controllability; }
void Wire::setcontrollability(double v) { controllability = v; }
void Wire::operator=(const Wire &w) { value = w.getvalue(); }
void Wire::operator=(char x) { value = x; }