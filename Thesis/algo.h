#pragma once

#include <vector>
#include <set>

typedef std::vector<uint8_t> Permutation;
typedef std::vector<Permutation> Permutations;

Permutations getAllPermutations(int n);

typedef uint64_t UnderlyingType;
typedef UnderlyingType Function;

Function applyPermutation(Function func, const Permutation& per, int n);
Function stringToFunction(const std::string& str, int n);
std::string functionToString(Function func, int n);

inline std::set<Function> getEquivalentFunctions(Function func, int n)
{
    std::set<Function> result;
    for (Permutation perm : getAllPermutations(n))
    {
        Function nextFunction = applyPermutation(func, perm, n);
        result.insert(nextFunction);
    }
    return result;
}

