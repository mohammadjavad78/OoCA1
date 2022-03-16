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
    std::string get_name() const;
    size_t get_level() const;
    void disp() const;
    bool is_valid() const;
    std::string split(std::string) const;
    bool operator==(const Wire &) const;
    friend std::ostream &operator<<(std::ostream &os, const Wire &w)
    {
        os << w.name;
        return os;
    }
    char getvalue() const;
    void setvalue(char);
    double getcontrollability() const;
    void setcontrollability(double);
    void operator=(const Wire &w);
    void operator=(char x);
    friend Wire operator!(Wire &w)
    {
        Wire ww{w.get_name(), w.get_level()};
        switch (w.getvalue())
        {
        case '0':
            ww.setvalue('1');
            break;
        case '1':
            ww.setvalue('0');
            break;
        case 'x':
            ww.setvalue('x');
            break;
        case 'z':
            ww.setvalue('x');
            break;
        default:
            ww.setvalue('x');
            break;
        }
        return ww;
    }

    friend Wire operator|(Wire &w1, Wire &w2)
    {
        Wire ww{w1.get_name() + "or" + w2.get_name(), std::max(w1.get_level(), w2.get_level()) + 1};
        if (w1.getvalue() == '1' || w2.getvalue() == '1')
            ww.setvalue('1');
        else if (w1.getvalue() == '0' && w2.getvalue() == '0')
            ww.setvalue('0');
        else
            ww.setvalue('x');
        return ww;
    }

    friend Wire operator&(Wire &w1, Wire &w2)
    {
        Wire ww{w1.get_name() + "or" + w2.get_name(), std::max(w1.get_level(), w2.get_level()) + 1};
        if (w1.getvalue() == '1' && w2.getvalue() == '1')
            ww.setvalue('1');
        else if (w1.getvalue() == '0' || w2.getvalue() == '0')
            ww.setvalue('0');
        else
            ww.setvalue('x');
        return ww;
    }

    friend Wire operator^(Wire &w1, Wire &w2)
    {
        Wire ww{w1.get_name() + "or" + w2.get_name(), std::max(w1.get_level(), w2.get_level()) + 1};
        if (w1.getvalue() == '1' && w2.getvalue() == '0')
            ww.setvalue('1');
        else if (w1.getvalue() == '0' && w2.getvalue() == '1')
            ww.setvalue('1');
        else if (w1.getvalue() == '0' && w2.getvalue() == '0')
            ww.setvalue('0');
        else if (w1.getvalue() == '1' && w2.getvalue() == '1')
            ww.setvalue('0');
        else
            ww.setvalue('x');
        return ww;
    }

private:
    std::string name{};
    size_t level{};
    char value{'x'};
    double controllability{};
};

#endif