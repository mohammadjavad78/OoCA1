#include <iostream>
#include "VerilogtoCPP.h"
#include "Gate.h"
#include <vector>
#include <functional>
int main()
{
    VerilogtoCPP vv("c1908.v");
    std::cout << vv;
    return 0;
}