#include "VerilogtoCPP.h"

VerilogtoCPP::VerilogtoCPP(std::string s)
{
    std::string myText;
    std::ifstream MyReadFile(s);
    std::ofstream MyFile("filename.txt");
    while (getline(MyReadFile, myText))
    {
        getwire(myText);
        Gate ee{getelem(myText)};
        if (ee.is_valid())
            Gates.push_back(ee);
    }
    MyReadFile.close();
}
Gate VerilogtoCPP::getelem(std::string line)
{
    std::vector<std::string> elems{"not", "nand", "and", "nor", "xor", "or"};
    std::string name{};
    std::vector<std::string> pins{};
    Gate g{};
    for (auto elem : elems)
    {
        int i{static_cast<int>(line.find(elem))};
        if (i != -1)
        {
            int firstpar{static_cast<int>(line.find('('))};
            int lastpar{static_cast<int>(line.find(')'))};
            g.set_solve_name(elem);
            g.set_name(line.substr(i + elem.length() + 1, firstpar - i - elem.length() - 1));
            int ss{firstpar};
            while (ss != -1 && ss < lastpar)
            {
                std::string s{};
                std::string pin{line.substr(ss + 1, line.find(',', ss + 1) - ss - 1)};
                ss = line.find(',', ss + 1);
                if (ss == -1)
                    pin = pin.substr(0, pin.find(')'));
                pins.push_back(pin);
            }
            g.set_pins(pins);
            return g;
        }
    }
    return g;
}
void VerilogtoCPP::disp()
{
    for (auto x : Gates)
        x.disp();
    for (auto x : Wires)
        x.disp();
}

void VerilogtoCPP::getwire(std::string line)
{
    std::vector<std::string> elems{"input", "output", "wire"};
    std::string name{};
    Wire w{};
    if (wirereading == "")
    {
        for (auto elem : elems)
        {
            int wires{static_cast<int>(line.find(elem))};
            if (wires == -1)
                continue;
            else
            {
                int lastsim{static_cast<int>(line.find(';'))};
                if (lastsim != -1)
                    wirereading = "";
                else
                {
                    lastsim = line.size();
                    wirereading = elem;
                }
                int ss{wires + elem.size()};
                while (ss != -1 && ss < lastsim)
                {
                    std::string pin{line.substr(ss + 1, line.find(',', ss + 1) - ss - 1)};
                    ss = line.find(',', ss + 1);
                    if (ss == -1)
                        pin = pin.substr(0, pin.find(','));
                    w.set_name(pin);
                    if (w.is_valid())
                        Wires.push_back(w);
                    w.set_name("");
                }
            }
        }
    }
    else
    {
        int lastsim{static_cast<int>(line.find(';'))};
        if (lastsim != -1)
            wirereading = "";
        else
            lastsim = line.size();
        int ss{0};
        while (ss != -1 && ss < lastsim)
        {
            std::string pin{line.substr(ss + 1, line.find(',', ss + 1) - ss - 1)};
            ss = line.find(',', ss + 1);
            if (ss == -1)
                pin = pin.substr(0, pin.find(','));
            w.set_name(pin);
            if (w.is_valid())
                Wires.push_back(w);
            w.set_name("");
        }
    }
}