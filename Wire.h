#ifndef WIRE_H
#define WIRE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <initializer_list>
#include <algorithm>

class Wire
{
public:
    Wire(std::string, size_t);
    Wire(){};
    void set_name(std::string);
    void set_level(size_t);
    std::string get_name();
    size_t get_level();
    void disp();
    bool is_valid();
    std::string split(std::string);
    bool operator==(Wire);
    friend std::ostream &operator<<(std::ostream &os, Wire w)
    {
        os << "name:" << w.name << "-level:" << w.level;
        return os;
    }

private:
    std::string name{};
    size_t level{};
};

#endif