#include "Gate.h"

Gate::Gate(std::string _name, std::string _solve_name, size_t _level, std::initializer_list<std::string> _pins) : name{split(_name)}, solve_name{split(_solve_name)}, level{_level}, pins{_pins} {}
std::vector<std::string> Gate::get_pins() { return pins; }
void Gate::set_name(std::string _name) { name = split(_name); }
void Gate::set_solve_name(std::string _solve_name) { solve_name = split(_solve_name); }
void Gate::set_pins(std::vector<std::string> _pins) { pins = _pins; }
void Gate::disp()
{
    std::cout << name << "," << solve_name << "{";
    for (auto x : pins)
        std::cout << x << ",";
    std::cout << "}" << std::endl;
}
bool Gate::is_valid()
{
    if (name != "")
        return true;
    return false;
}
std::string Gate::split(std::string s)
{
    std::string ss{};
    for (auto x : s)
    {
        if (static_cast<int>(x) < 127 && static_cast<int>(x) > 32)
            ss += x;
    }
    return ss;
}