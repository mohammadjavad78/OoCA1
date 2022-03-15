#ifndef VERILOGTOCPP_H
#define VERILOGTOCPP_H

#include <iostream>
#include <string>
#include <fstream>
#include "Gate.h"
#include "Wire.h"
#include <vector>

class VerilogtoCPP
{
public:
    VerilogtoCPP(std::string);
    VerilogtoCPP(){};
    Gate getelem(std::string);
    void getwire(std::string);
    void disp();
    Wire searchwire(std::string);

private:
    std::vector<Gate> Gates{};
    std::vector<Wire> Wires{};
    std::string wirereading{};
};

#endif