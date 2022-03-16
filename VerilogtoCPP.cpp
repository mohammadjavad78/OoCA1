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
        if (lines == startgateline && count)
            MyFile << myText;
        lines++;
    }
    MyReadFile.close();
    // std::cout << lines << startgateline << myText << std::endl;

    // std::ifstream MyReadFile2(s);
    // std::string myText2;
    // for (int i{}; i < startgateline; i++)
    // {
    //     getline(MyReadFile2, myText2);
    //     MyFile << myText2;
    // }
    // MyReadFile2.close();
    // MyFile.close();
}
Gate VerilogtoCPP::getelem(const std::string &line)
{
    std::vector<std::string> elems{"not", "nand", "and", "nor", "xor", "or"};
    std::vector<std::reference_wrapper<Wire>> pins{};
    Gate gate{};
    for (auto elem : elems)
    {
        int is_elem_inline{static_cast<int>(line.find(elem))};
        if (count)
            startgateline = lines;
        if (is_elem_inline != -1)
        {
            count = false;
            int firstparam{static_cast<int>(line.find('('))};
            int lastpar{static_cast<int>(line.find(')'))};
            gate.set_solve_name(elem);
            gate.set_name(line.substr(is_elem_inline + elem.length() + 1, firstparam - is_elem_inline - elem.length() - 1));
            while (firstparam != -1 && firstparam < lastpar)
            {
                std::string pin{line.substr(firstparam + 1, line.find(',', firstparam + 1) - firstparam - 1)};
                firstparam = line.find(',', firstparam + 1);
                if (firstparam == -1)
                    pin = pin.substr(0, pin.find(')'));
                pins.push_back(searchwire(Wire(pin, 0)));
            }
            gate.set_pins(pins);
            return gate;
        }
    }
    return gate;
}
void VerilogtoCPP::disp() const
{
    for (auto x : Gates)
        x.disp();
    for (auto x : Wires)
    {
        x.disp();
        std::cout << std::endl;
    }
}

void VerilogtoCPP::getwire(const std::string &line)
{
    std::vector<std::string> elems{"input", "output", "wire"};
    Wire wire{};
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
                int firstparam{wires + static_cast<int>(elem.size())};
                while (firstparam != -1 && firstparam < lastsim)
                {
                    std::string pin{line.substr(firstparam + 1, line.find(',', firstparam + 1) - firstparam - 1)};
                    firstparam = line.find(',', firstparam + 1);
                    if (firstparam == -1)
                        pin = pin.substr(0, pin.find(','));
                    wire.set_name(pin);
                    if (wire.is_valid())
                    {
                        if (elem == "input" || wirereading == "input")
                        {
                            InputWires.push_back(Wires.size());
                            wire.setcontrollability(0.5);
                        }
                        Wires.push_back(wire);
                    }
                    wire.set_name("");
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
        int firstparam{};
        while (firstparam != -1 && firstparam < lastsim)
        {
            std::string pin{line.substr(firstparam + 1, line.find(',', firstparam + 1) - firstparam - 1)};
            firstparam = line.find(',', firstparam + 1);
            if (firstparam == -1)
                pin = pin.substr(0, pin.find(','));
            wire.set_name(pin);
            if (wire.is_valid())
            {
                if (wirereading == "input")
                {
                    InputWires.push_back(Wires.size());
                    wire.setcontrollability(0.5);
                }
                Wires.push_back(wire);
            }
            wire.set_name("");
        }
    }
}

Wire &VerilogtoCPP::searchwire(Wire &&v)
{
    for (auto &x : Wires)
        if (x == v)
            return x;
    return v;
}

void VerilogtoCPP::setlayyer()
{
    size_t k{}, k_new{1};
    while (k_new != k)
    {
        k = k_new;
        for (size_t i{}; i < Gates.size(); i++)
        {
            Gates[i].setlevel();
            if (Gates[i].getlevel() > k_new)
                k_new = Gates[i].getlevel();
        }
    }
}
void VerilogtoCPP::print() const
{
    std::string myText;
    std::ofstream MyFile("filename.txt", std::ios_base::app);
    for (size_t i{}; i < Gates.size(); i++)
        MyFile << Gates[i];
    MyFile << "endmodule";
    MyFile.close();
}
void VerilogtoCPP::sort()
{
    std::sort(Gates.begin(), Gates.end());
    for (auto x : Gates)
        x.solvecontrollability();
}

void VerilogtoCPP::setinput(const std::vector<char> &v)
{
    for (size_t i{}; i < InputWires.size(); i++)
        Wires[InputWires[i]].setvalue(v[i]);
    for (auto gate : Gates)
        gate.solve();
}