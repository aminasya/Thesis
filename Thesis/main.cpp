#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <cstdlib>

#include "algo.h"
#include "bitset.h"
#include "orbit_calculator.h"
#include "group.h"

void test();

int main()
{

#ifndef NDEBUG
    test();
#endif // 


    OrbitCalculator<PermutationGroup> calculator(4);

    //calculator.load();
    calculator.doIterations(50000);
    calculator.save();
}