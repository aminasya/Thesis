#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <cstdlib>

#include "algo.h"
#include "bitset.h"
#include "orbit_calculator.h"

void test();

int main()
{

#ifndef NDEBUG
    test();
#endif // 


    OrbitCalculator calculator(5);

    //calculator.load();
    // 5 rope * 100
    calculator.doIterations(100);
    calculator.save();
}