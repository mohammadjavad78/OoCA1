#ifndef GATE_H
#define GATE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <initializer_list>
#include <algorithm>
#include "Wire.h"

class Gate
{
public:
    Gate(std::string, std::string, size_t, std::initializer_list<std::string>);
    Gate(){};
    void set_name(std::string);
    void set_solve_name(std::string);
    void set_pins(std::vector<std::string>);
    std::vector<std::string> get_pins();
    void disp();
    bool is_valid();
    std::string split(std::string);

private:
    std::string name{};
    std::string solve_name{};
    std::vector<std::string> pins;
    size_t level{};
};

#endif