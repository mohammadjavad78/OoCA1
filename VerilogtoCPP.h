#ifndef VERILOGTOCPP_H
#define VERILOGTOCPP_H

#include <iostream>
#include <string>
#include <fstream>
#include "Gate.h"
#include "Wire.h"
#include <vector>
#include <functional>

class VerilogtoCPP
{
public:
    VerilogtoCPP(std::string);
    VerilogtoCPP(){};
    Gate getelem(std::string);
    void getwire(std::string);
    void disp();
    Wire &searchwire(Wire &&v);
    friend std::ostream &operator<<(std::ostream &os, VerilogtoCPP v)
    {
        for (auto x : v.Gates)
            std::cout << x;
        return os;
    }

    // private:
    std::vector<Gate> Gates{};
    std::vector<Wire> Wires{};
    std::string wirereading{};
};

#endif