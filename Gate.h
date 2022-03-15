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
    // Gate(std::string, std::string, size_t, std::initializer_list<std::vector<std::reference_wrapper<Wire>>>);
    Gate(){};
    void set_name(std::string);
    void set_solve_name(std::string);
    void set_pins(std::vector<std::reference_wrapper<Wire>>);
    std::vector<std::reference_wrapper<Wire>> get_pins();
    void disp();
    bool is_valid();
    std::string split(std::string);
    friend std::ostream &operator<<(std::ostream &os, Gate g)
    {
        for (size_t i{}; i < g.get_pins().size(); i++)
            os << g.name << "," << g.solve_name << "{" << g.get_pins()[i].get() << ","
               << "}" << std::endl;
        return os;
    }

private:
    std::string name{};
    std::string solve_name{};
    std::vector<std::reference_wrapper<Wire>> pins;
    size_t level{};
};

#endif