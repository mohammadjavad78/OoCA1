#include "Gate.h"

// Gate::Gate(std::string _name, std::string _solve_name, size_t _level, std::initializer_list<std::vector<std::reference_wrapper<Wire>>> _pins) : name{split(_name)}, solve_name{split(_solve_name)}, level{_level}, pins{_pins} {}
std::vector<std::reference_wrapper<Wire>> Gate::get_pins() { return pins; }
void Gate::set_name(std::string _name) { name = split(_name); }
void Gate::set_solve_name(std::string _solve_name) { solve_name = split(_solve_name); }
void Gate::set_pins(std::vector<std::reference_wrapper<Wire>> _pins)
{
    pins = _pins;
}
void Gate::disp()
{
    std::cout << name << "," << solve_name << "{";
    for (auto x : pins)
        x.get().disp();
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

void Gate::setlevel()
{
    size_t max{0};
    for (size_t i{1}; i < get_pins().size(); i++)
    {
        if (get_pins()[i].get().get_level() > max)
            max = get_pins()[i].get().get_level();
    }
    this->get_pins()[0].get().set_level(max + 1);
    level = max + 1;
}
size_t Gate::getlevel() { return level; }

Gate::operator size_t() { return level; }

void Gate::solve()
{
    Wire ww{"solved", 0};
    ww.setvalue('1');
    if (solve_name == "not")
        get_pins()[0].get() = !get_pins()[1].get();
    else if (solve_name == "nand")
        for (size_t i{1}; i < get_pins().size(); i++)
        {
            ww = ww & get_pins()[i].get();
            get_pins()[0].get() = !ww;
        }
    else if (solve_name == "and")
        for (size_t i{1}; i < get_pins().size(); i++)
        {
            ww = ww & get_pins()[i].get();
            get_pins()[0].get() = ww;
        }
    else if (solve_name == "or")
    {
        ww.setvalue('0');
        for (size_t i{1}; i < get_pins().size(); i++)
        {
            ww = ww | get_pins()[i].get();
            get_pins()[0].get() = ww;
        }
    }
    else if (solve_name == "nor")
    {
        ww.setvalue('0');
        for (size_t i{1}; i < get_pins().size(); i++)
        {
            ww = ww | get_pins()[i].get();
            get_pins()[0].get() = !ww;
        }
    }
    else if (solve_name == "xor")
    {
        ww.setvalue('0');
        for (size_t i{1}; i < get_pins().size(); i++)
        {
            ww = ww ^ get_pins()[i].get();
            get_pins()[0].get() = !ww;
        }
    }
}