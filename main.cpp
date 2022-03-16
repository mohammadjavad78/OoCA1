#include <iostream>
#include "VerilogtoCPP.h"
#include "Gate.h"
#include <vector>
#include <functional>
int main()
{
    VerilogtoCPP vv("c1908.v");
    // // std::cout<<
    vv.setlayyer();
    vv.sort();
    vv.setinput({'0', '0', '1'});
    vv.print();
    vv.disp();

    // vv.disp();
    // !w;
    // std::cout << w.getvalue();
    // w.disp();
    // std::cout << !w;
    // std::cout << vv;
    // vv.disp();
    return 0;
}