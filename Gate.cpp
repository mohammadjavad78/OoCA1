#include "Gate.h"

std::vector<std::reference_wrapper<Wire>> Gate::get_pins() const { return pins; }
void Gate::set_name(std::string _name) { name = split(_name); }
void Gate::set_solve_name(std::string _solve_name) { solve_name = split(_solve_name); }
void Gate::set_pins(std::vector<std::reference_wrapper<Wire>> _pins) { pins = _pins; }
void Gate::disp() const
{
    std::cout << name << "," << solve_name << "{";
    for (auto x : pins)
        x.get().disp();
    std::cout << "}" << std::endl;
}
bool Gate::is_valid() const { return name != "" ? true : false; }
std::string Gate::split(const std::string &str) const
{
    std::string result{};
    for (auto s_char : str)
        if (static_cast<int>(s_char) < 127 && static_cast<int>(s_char) > 32 && static_cast<int>(s_char) != 59)
            result += s_char;
    return result;
}

void Gate::setlevel()
{
    size_t max{};
    for (size_t i{1}; i < get_pins().size(); i++)
        if (get_pins()[i].get().get_level() > max)
            max = get_pins()[i].get().get_level();
    get_pins()[0].get().set_level(max + 1);
    level = max + 1;
}
size_t Gate::getlevel() const { return level; }

Gate::operator size_t() const { return level; }

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
void Gate::solvecontrollability()
{
    double cont{1};
    if (solve_name == "not")
        get_pins()[0].get().setcontrollability(get_pins()[1].get().getcontrollability());
    else if (solve_name == "nand")
    {
        for (size_t i{1}; i < get_pins().size(); i++)
            cont *= get_pins()[i].get().getcontrollability();
        cont = 1 - cont;
        get_pins()[0].get().setcontrollability(cont);
    }
    else if (solve_name == "and")
    {
        for (size_t i{1}; i < get_pins().size(); i++)
            cont *= get_pins()[i].get().getcontrollability();
        get_pins()[0].get().setcontrollability(cont);
    }
    else if (solve_name == "or")
    {
        for (size_t i{1}; i < get_pins().size(); i++)
            cont *= (1 - get_pins()[i].get().getcontrollability());
        cont = 1 - cont;
        get_pins()[0].get().setcontrollability(cont);
    }
    else if (solve_name == "nor")
    {
        for (size_t i{1}; i < get_pins().size(); i++)
            cont *= (1 - get_pins()[i].get().getcontrollability());
        get_pins()[0].get().setcontrollability(cont);
    }
    else if (solve_name == "xor")
    {
        for (size_t i{1}; i < get_pins().size(); i++)
            if (i % 2 == 0)
                cont *= get_pins()[i].get().getcontrollability();
            else
                cont *= (1 - get_pins()[i].get().getcontrollability());
        for (size_t i{1}; i < get_pins().size(); i++)
            if (i % 2 == 1)
                cont *= get_pins()[i].get().getcontrollability();
            else
                cont *= (1 - get_pins()[i].get().getcontrollability());
        get_pins()[0].get().setcontrollability(cont);
    }
}