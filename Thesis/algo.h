#pragma once

#include <vector>

typedef std::vector<uint8_t> Permutation;
typedef std::vector<Permutation> Permutations;

Permutations getAllPermutations(int n);

typedef uint32_t Function;

Function applyPermutation(Function func, const Permutation& per, int n);
Function stringToFunction(const std::string& str, int n);
std::string functionToString(Function func, int n);


