#include "VerilogtoCPP.h"

VerilogtoCPP::VerilogtoCPP(std::string s)
{
    std::string myText;
    std::ifstream MyReadFile(s);
    while (getline(MyReadFile, myText))
    {
        getwire(myText);
        Gate ee{getelem(myText)};
        if (ee.is_valid())
            Gates.push_back(ee);
        lines++;
    }
    MyReadFile.close();

    std::ifstream MyReadFile2(s);
    std::string myText2;
    std::ofstream MyFile("filename.txt");
    for (int i{}; i < startgateline; i++)
    {
        getline(MyReadFile2, myText2);
        MyFile << myText2;
    }
    MyReadFile2.close();
    MyFile.close();
}
Gate VerilogtoCPP::getelem(std::string line)
{
    std::vector<std::string> elems{"not", "nand", "and", "nor", "xor", "or"};
    std::string name{};
    std::vector<std::reference_wrapper<Wire>> pins{};
    Gate g{};
    for (auto elem : elems)
    {
        int i{static_cast<int>(line.find(elem))};
        if (count)
            startgateline = lines;
        if (i != -1)
        {
            count = false;
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
                // searchwire(Wire(pin, 0)).disp();
                pins.push_back(searchwire(Wire(pin, 0)));
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
                int ss{wires + static_cast<int>(elem.size())};
                while (ss != -1 && ss < lastsim)
                {
                    std::string pin{line.substr(ss + 1, line.find(',', ss + 1) - ss - 1)};
                    ss = line.find(',', ss + 1);
                    if (ss == -1)
                        pin = pin.substr(0, pin.find(','));
                    w.set_name(pin);
                    if (w.is_valid())
                    {
                        Wires.push_back(w);
                        if (elem == "input" || wirereading == "input")
                        {
                            InputWires.push_back(Wires.size() - 1);
                        }
                    }
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
            {
                Wires.push_back(w);
                if (wirereading == "input")
                {
                    InputWires.push_back(Wires.size() - 1);
                }
            }
            w.set_name("");
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
    size_t k = 0;
    size_t k_new = 1;
    while (k_new != k)
    {
        k = k_new;
        for (size_t i{}; i < Gates.size(); i++)
        {
            Gates[i].setlevel();
            if (Gates[i].getlevel() > k_new)
                k_new = Gates[i].getlevel();
        }
        // std::cout << k << " ";
    }
}
void VerilogtoCPP::print()
{
    std::string myText;
    std::ofstream MyFile("filename.txt", std::ios_base::app);
    for (size_t i{}; i < Gates.size(); i++)
    {
        MyFile << Gates[i];
    }
    MyFile << "\nendmodule";
    MyFile.close();
    // std::cout << Gates.size() << std::endl;
}
void VerilogtoCPP::sort()
{
    std::sort(Gates.begin(), Gates.end());
}

void VerilogtoCPP::setinput(std::vector<char> v)
{
    for (size_t i{}; i < InputWires.size(); i++)
    {
        Wires[InputWires[i]].setvalue(v[i]);
        //     Wires[i].disp();
    }
    for (auto x : Gates)
        x.solve();
}