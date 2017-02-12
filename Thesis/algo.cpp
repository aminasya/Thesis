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

Function stringToFunction(const std::string& str, int n)
{
    assert(str.size() == (1ull << n));
    Function func = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        assert(str[i] == '0' || str[i] == '1');
        func |= (static_cast<UnderlyingType>(str[i] - '0') << i);
    }
    return func;
}

std::string functionToString(Function func, int n)
{
    std::string res(1ull << n, '0');
    for (int i = 0; i < (1ll << n); ++i)
    {
        res[i] += !!(func & (1ll << i));
    }
    return res;
}

