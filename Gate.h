#ifndef GATE_H
#define GATE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <initializer_list>
#include <algorithm>
#include "Wire.h"
#include <functional>

class Gate
{
public:
    Gate(){};
    void set_name(std::string);
    void set_solve_name(std::string);
    void set_pins(std::vector<std::reference_wrapper<Wire>>);
    std::vector<std::reference_wrapper<Wire>> get_pins() const;
    void disp() const;
    bool is_valid() const;
    std::string split(const std::string &) const;
    void solvecontrollability();
    friend std::ostream &operator<<(std::ostream &os, const Gate &g)
    {
        os << g.solve_name << " " << g.name << "(";
        for (size_t i{}; i < g.get_pins().size(); i++)
            if (i != g.get_pins().size() - 1)
                os << g.get_pins()[i].get() << ",";
            else
                os << g.get_pins()[i].get();
        os << ");" << std::endl;
        return os;
    }
    void setlevel();
    size_t getlevel() const;
    operator size_t() const;
    void solve();

private:
    std::string name{};
    std::string solve_name{};
    std::vector<std::reference_wrapper<Wire>> pins;
    size_t level{};
};

#endif