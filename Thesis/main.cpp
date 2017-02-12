#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <cstdlib>

#include "algo.h"

typedef std::vector<Function> Orbit;

void test();

int main()
{

#ifndef NDEBUG
    test();
#endif // 

    const int n = 5;
    
    int orbit = 0;
    std::vector<bool> orbitOfFunction(1ll << (1ll << n), false);

    //std::vector<int> orbitCount(121);

    Permutations permutations = getAllPermutations(n);
    for (Function func = 0; func < orbitOfFunction.size(); ++func)
    {
        if (orbitOfFunction[func])
            continue;
        orbit++;
        //std::cout << orbit << std::endl;
        //std::cout << functionToString(func, n) << std::endl;
        orbitOfFunction[func] = true;
        //int count = 1;

        for (const Permutation& perm : permutations)
        {
            Function nextFunction = applyPermutation(func, perm, n);
            assert(orbitOfFunction[nextFunction] == -1 || orbitOfFunction[nextFunction] == orbit);
            orbitOfFunction[nextFunction] = true;
        }
        //orbitCount[count]++;
        std::cout << func << std::endl;
    }

    std::cout << orbit << std::endl;
    for (int i = 0; i < 121; ++i)
    {
    //    if (orbitCount[i] != 0)
    //    {
    //        std::cout << i << " " << orbitCount[i] << std::endl;
    //    }
    }


    //std::string func = "0100010001000100";
    ////std::string func = "0100010000100100";
    //std::set<Function> funcs = getEquivalentFunctions(stringToFunction(func, n), n);

    //for (Function func : funcs)
    //{
    //    std::cout << functionToString(func, n) << std::endl;
    //}
    //std::cout << funcs.size() << std::endl;
    //

}