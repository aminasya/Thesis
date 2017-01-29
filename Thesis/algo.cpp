#include "algo.h"

#include <cassert>

void getAllPermutationsHelper(Permutation& per, int i, int n, std::vector<bool>& used, Permutations& all)
{
    if (i == n)
    {
        all.push_back(per);
        return;
    }
    for (int j = 0; j < n; ++j)
    {
        if (!used[j])
        {
            used[j] = true;
            per[i] = j;
            getAllPermutationsHelper(per, i + 1, n, used, all);
            used[j] = false;
        }
    }
}

Permutations getAllPermutations(int n)
{
    Permutations result;
    Permutation per(n);
    std::vector<bool> used(n, false);

    getAllPermutationsHelper(per, 0, n, used, result);

    return result;
}


Function applyPermutation(Function func, const Permutation& per, int n)
{
    assert(per.size() == n);
    Function newFunc = 0;
    for (int mask = 0; mask < (1 << n); ++mask)
    {
        if (!(func & (1 << mask)))
        {
            continue;
        }
        int newMask = 0;
        for (int i = 0; i < n; ++i)
        {
            if (mask & (1 << i))
            {
                newMask |= (1 << per[i]);
            }
        }
        newFunc |= (1 << newMask);
    }
    return newFunc;
}

Function stringToFunction(const std::string& str, int n)
{
    assert(str.size() == (1 << n));
    Function func = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        assert(str[i] == '0' || str[i] == '1');
        func |= ((str[i] - '0') << i);
    }
    return func;
}

std::string functionToString(Function func, int n)
{
    std::string res(1 << n, '0');
    for (int i = 0; i < (1 << n); ++i)
    {
        res[i] += !!(func & (1 << i));
    }
    return res;
}

