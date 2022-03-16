#include <iostream>
#include "VerilogtoCPP.h"
#include "Gate.h"
#include "Wire.h"
#include <vector>
#include <functional>
int main()
{
    VerilogtoCPP vv("c1908.v");
    vv.setlayyer();
    vv.sort();
    vv.setinput({'0', '0', '1'});
    vv.print();
    vv.disp();
    return 0;
}