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

    const int n = 3;

    int orbit = 0;
    std::vector<int> orbitOfFunction(1ll << (1ll << n), -1);

    std::vector<int> orbitCount(121);

    for (int func = 0; func < orbitOfFunction.size(); ++func)
    {
        if (orbitOfFunction[func] != -1)
            continue;
        orbit++;
        //std::cout << orbit << std::endl;
        //std::cout << functionToString(func, n) << std::endl;
        orbitOfFunction[func] = orbit;
        int count = 1;

        for (Permutation perm : getAllPermutations(n))
        {
            Function nextFunction = applyPermutation(func, perm, n);
            assert(orbitOfFunction[nextFunction] == -1 || orbitOfFunction[nextFunction] == orbit);
            if (orbitOfFunction[nextFunction] == -1)
            {
                orbitOfFunction[nextFunction] = orbit;
            //    std::cout << functionToString(nextFunction, n) << std::endl;
                count++;
            }
        }
        orbitCount[count]++;
    }
    for (int i = 0; i < 121; ++i)
    {
        if (orbitCount[i] != 0)
        {
            std::cout << i << " " << orbitCount[i] << std::endl;
        }
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