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
    Gate getelem(const std::string &);
    void disp() const;
    void getwire(const std::string &);
    Wire &searchwire(Wire &&v);
    friend std::ostream &operator<<(std::ostream &os, VerilogtoCPP v)
    {
        for (auto x : v.Gates)
            os << x;
        os << v.Gates.size();
        return os;
    }
    void setlayyer();
    void print() const;
    void sort();
    void setinput(const std::vector<char> &);

private:
    std::vector<Gate> Gates{};
    std::vector<Wire> Wires{};
    std::vector<size_t> InputWires{};
    std::string wirereading{};
    bool count{true};
    int lines{};
    int startgateline{-1};
};

#endif