#include "algo.h"
#include "bitset.h"

#include <cassert>
#include <sstream>

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

void testApplyPermutation3()
{
    const int n = 2;
    Function func = stringToFunction("0101", n);
    Permutation p = {1, 0};
    Function res = applyPermutation(func, p, n);
    assert(functionToString(res, n) == "0011");
}

void testApplyPermutation4()
{
    const int n = 2;
    Function func = stringToFunction("0101", n);
    Permutation p = {0, 1};
    Function res = applyPermutation(func, p, n);
    assert(functionToString(res, n) == "0101");
}

void testApplyPermutation5()
{
    const int n = 2;
    Function func = stringToFunction("1110", n);
    Permutation p = {1, 0};
    Function res = applyPermutation(func, p, n);
    assert(functionToString(res, n) == "1110");
}

void testApplyPermutation6()
{
    const int n = 2;
    Function func = stringToFunction("1100", n);
    Permutation p = {1, 0};
    Function res = applyPermutation(func, p, n);
    assert(functionToString(res, n) == "1010");
}

void testApplyPermutation31()
{
    const int n = 3;
    Function func = stringToFunction("01010101", n);
    Permutation p = {0, 1, 2};
    Function res = applyPermutation(func, p, n);
    assert(res == func);
}

void testApplyPermutation32()
{
    const int n = 3;
    Function func = stringToFunction("01010101", n);
    Permutation p = {0, 2, 1};
    Function res = applyPermutation(func, p, n);
    assert(functionToString(res, n) == "00110011");
}

void testApplyPermutation33()
{
    const int n = 3;
    Function func = stringToFunction("01010101", n);
    Permutation p = {1, 2, 0};
    Function res = applyPermutation(func, p, n);
    assert(functionToString(res, n) == "00001111");
}

void testApplyPermutation34()
{
    const int n = 3;
    Function func = stringToFunction("01110111", n);
    Permutation p = {2, 1, 0};
    Function res = applyPermutation(func, p, n);
    assert(functionToString(res, n) == "00111111");
}

void testApplyPermutation35()
{
    const int n = 3;
    Function func = stringToFunction("01110111", n);
    Permutation p = {1, 0, 2};
    Function res = applyPermutation(func, p, n);
    assert(functionToString(res, n) == "01011111");
}

void testBitset1()
{
    const int size = 100;
    Bitset bitset(size);

    for (int i = 0; i < size; ++i)
    {
        assert(!bitset.getBit(i));
    }

    assert(!bitset.getBit(74));
    bitset.setBit(74);
    assert(bitset.getBit(74));

    assert(!bitset.getBit(41));
    bitset.setBit(41);
    assert(bitset.getBit(41));

    assert(!bitset.getBit(0));
    bitset.setBit(0);
    assert(bitset.getBit(0));
    bitset.clearBit(0);
    assert(!bitset.getBit(0));
}

void testBitsetSerializeDeserialize()
{
    std::vector<uint64_t> numbers{ 5, 6, 7, 14, 85, 124, 160, 165, 168, 170, 171, 186, 195 };
    Bitset bitset(200);

    for (int i = 0; i < numbers.size(); ++i)
    {
        bitset.setBit(numbers[i]);
    }

    std::ostringstream ostream;
    bitset.serialize(ostream);

    std::istringstream istream(ostream.str());

    Bitset bitset2;
    bitset2.deserialize(istream);

    for (int i = 0; i < 200; ++i)
    {
        if (std::find(numbers.begin(), numbers.end(), i) == numbers.end())
        {
            assert(!bitset2.getBit(i));
        }
        else
        {
            assert(bitset2.getBit(i));
        }
    }
}

void testBitset()
{
    testBitset1();
    testBitsetSerializeDeserialize();
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
    testApplyPermutation4();
    testApplyPermutation5();
    testApplyPermutation6();
    testApplyPermutation31();
    testApplyPermutation32();
    testApplyPermutation33();
    testApplyPermutation34();
    testApplyPermutation35();

    testBitset();
}