#include <iostream>
#include <vector>
#include <string>
#include <cassert>

#include "algo.h"

typedef std::vector<Function> Orbit;

void test();

int main()
{
#ifndef NDEBUG
    test();
#endif // 

    const int n = 4;

    int orbit = 0;
    std::vector<int> orbitOfFunction(1 << (1 << n), -1);

    std::vector<int> orbitCount(25);

    for (int func = 0; func < orbitOfFunction.size(); ++func)
    {
        if (orbitOfFunction[func] != -1)
            continue;
        orbit++;
        //std::cout << orbit << std::endl;
        //std::cout << functionToString(func, n);
        orbitOfFunction[func] = orbit;
        int count = 1;

        for (Permutation perm : getAllPermutations(n))
        {
            Function nextFunction = applyPermutation(func, perm, n);
            assert(orbitOfFunction[nextFunction] == -1 || orbitOfFunction[nextFunction] == orbit);
            if (orbitOfFunction[nextFunction] == -1)
            {
                orbitOfFunction[nextFunction] = orbit;
         //       std::cout << ", " << functionToString(nextFunction, n) ;
                count++;
            }
        }
        //std::cout << count << std::endl;
        orbitCount[count]++;
    }
    for (int i = 0; i < 25; ++i)
    {
        if (orbitCount[i] != 0)
        {
            std::cout << i << " " << orbitCount[i] << std::endl;
        }
    }

}