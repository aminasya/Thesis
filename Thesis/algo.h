#pragma once

#include <vector>
#include <set>
#include <cassert>

typedef std::vector<uint8_t> Permutation;
typedef std::vector<Permutation> Permutations;

Permutations getAllPermutations(int n);

typedef uint64_t UnderlyingType;
typedef UnderlyingType Function;


Function stringToFunction(const std::string& str, int n);
std::string functionToString(Function func, int n);

inline Function applyPermutation(Function func, const Permutation& per, int n){    Function newFunc = 0;    for (UnderlyingType mask = 0; mask < (1ull << n); ++mask)    {        if (!(func & (1ll << mask)))        {            continue;        }        UnderlyingType newMask = 0;        for (int i = 0; i < n; ++i)        {            if (mask & (1ll << i))            {                newMask |= (1ll << (n - per[n - i - 1] - 1));            }        }        newFunc |= (1ll << newMask);    }    return newFunc;}

template <typename GroupType>
inline std::set<Function> getEquivalentFunctions(Function func, int n)
{
    std::set<Function> result;
    GroupType group(n);

    for (group.begin(); group.nextElem(); )
    {
        Function nextFunction = group.applyElemToFunction(func);
        result.insert(nextFunction);
    }
    return result;
}



