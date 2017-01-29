#include "algo.h"

#include <cassert>

void testPermutations1()
{
    Permutations permutations = getAllPermutations(1);

    assert(permutations.size() == 1);
    assert(permutations[0].size() == 1);
    assert(permutations[0][0] == 0);
}

void testPermutations2()
{
    Permutations permutations = getAllPermutations(2);

    assert(permutations.size() == 2);
    assert(permutations[0].size() == 2);
    assert(permutations[0][0] == 0);
    assert(permutations[0][1] == 1);

    assert(permutations[1][0] == 1);
    assert(permutations[1][1] == 0);
}

void testPermutations3()
{
    Permutations permutations = getAllPermutations(3);

    assert(permutations.size() == 6);
}

void testStringToFunction1()
{
    Function func1 = stringToFunction("01", 1);
    assert((func1 & (1 << 0)) == 0);
    assert((func1 & (1 << 1)) != 1);

    Function func2 = stringToFunction("11", 1);
    assert((func2 & (1 << 0)) != 0);
    assert((func2 & (1 << 1)) != 0);

    Function func3 = stringToFunction("10", 1);
    assert((func3 & (1 << 0)) != 0);
    assert((func3 & (1 << 1)) == 0);
}


void testStringToFunction2()
{
    Function func1 = stringToFunction("0001", 2);
    assert((func1 & (1 << 0)) == 0);
    assert((func1 & (1 << 1)) == 0);
    assert((func1 & (1 << 2)) == 0);
    assert((func1 & (1 << 3)) != 0);

    Function func2 = stringToFunction("0110", 2);
    assert((func2 & (1 << 0)) == 0);
    assert((func2 & (1 << 1)) != 0);
    assert((func2 & (1 << 2)) != 0);
    assert((func2 & (1 << 3)) == 0);

    Function func3 = stringToFunction("1011", 2);
    assert((func3 & (1 << 0)) != 0);
    assert((func3 & (1 << 1)) == 0);
    assert((func3 & (1 << 2)) != 0);
    assert((func3 & (1 << 3)) != 0);

    Function func4 = stringToFunction("1100", 2);
    assert((func4 & (1 << 0)) != 0);
    assert((func4 & (1 << 1)) != 0);
    assert((func4 & (1 << 2)) == 0);
    assert((func4 & (1 << 3)) == 0);

}

void testFunctionToString1()
{
    std::string str = "00";
    Function func = stringToFunction(str, 1);
    assert(functionToString(func, 1) == str);
}

void testFunctionToString2()
{
    std::string str = "10";
    Function func = stringToFunction(str, 1);
    assert(functionToString(func, 1) == str);
}

void testFunctionToString3()
{
    std::string str = "1010";
    const int n = 2;
    Function func = stringToFunction(str, n);
    assert(functionToString(func, n) == str);
}

void testFunctionToString4()
{
    std::string str = "0111";
    const int n = 2;
    Function func = stringToFunction(str, n);
    assert(functionToString(func, n) == str);
}

void testFunctionToString5()
{
    std::string str = "01110010";
    const int n = 3;
    Function func = stringToFunction(str, n);
    assert(functionToString(func, n) == str);
}

void testFunctionToString6()
{
    std::string str = "01010110";
    const int n = 3;
    Function func = stringToFunction(str, n);
    assert(functionToString(func, n) == str);
}

void testFunctionToString7()
{
    std::string str = "11111111";
    const int n = 3;
    Function func = stringToFunction(str, n);
    assert(functionToString(func, n) == str);
}

void testFunctionToString8()
{
    std::string str = "00000000";
    const int n = 3;
    Function func = stringToFunction(str, n);
    assert(functionToString(func, n) == str);
}

void testApplyPermutation1()
{
    const int n = 1;
    Function func = stringToFunction("01", n);
    Permutation p = {0};
    Function res = applyPermutation(func, p, n);
    assert(res == func);
}

void testApplyPermutation2()
{
    const int n = 1;
    Function func = stringToFunction("11", n);
    Permutation p = {0};
    Function res = applyPermutation(func, p, n);
    assert(res == func);
}

void testApplyPermutation2()
{
    const int n = 2;
    Function func = stringToFunction("11", n);
    Permutation p = {0};
    Function res = applyPermutation(func, p, n);
    assert(res == func);
}

void test()
{
    testPermutations1();
    testPermutations2();
    testPermutations3();
    testStringToFunction1();
    testStringToFunction2();
    testFunctionToString1();
    testFunctionToString2();
    testFunctionToString3();
    testFunctionToString4();
    testFunctionToString5();
    testFunctionToString6();
    testFunctionToString7();
    testFunctionToString8();
    testApplyPermutation1();
    testApplyPermutation2();
    testApplyPermutation3();
}