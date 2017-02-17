#pragma once

#include "bitset.h"
#include <vector>
#include <string>

int factorial(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

template <typename GroupType>
class OrbitCalculator
{
public:
    OrbitCalculator(int n)
        : m_n(n)
        , m_bitset(1ll << (1 << n))
        , m_orbitCount(factorial(n) + 1)
        , m_function(0)
        , m_fileName("data.txt")
        , m_group(n)
    {}

    void save()
    {
        std::cout << "saving ..." << std::endl;
        std::ofstream fout;
        fout.open(m_fileName.c_str());
        assert(fout.is_open());
        fout << m_n << std::endl;
        fout << m_function << std::endl;
        fout << m_bitset.size() << std::endl;
        for (int i = 0; i < m_orbitCount.size(); ++i)
        {
            fout << m_orbitCount[i] << ' ';
        }
        fout << std::endl;
        m_bitset.serialize(fout);
        fout.close();
    }

    void load()
    {
        std::cout << "loading ..." << std::endl;
        std::ifstream fin;
        fin.open(m_fileName.c_str());
        assert(fin.is_open());
        fin >> m_n;
        fin >> m_function;
        uint64_t dummy;
        fin >> dummy;
        for (int i = 0; i < m_orbitCount.size(); ++i)
        {
            fin >> m_orbitCount[i];
        }
        m_bitset.deserialize(fin);
        fin.close();
    }

    void doIterations(uint64_t itarationCount)
    {

        uint64_t iterations = 0;
        while (m_function < m_bitset.size() && iterations < itarationCount)
        {
            if (m_bitset.getBit(m_function))
            {
                m_function++;
                continue;
            }
            m_bitset.setBit(m_function);
            int count = 1;

            m_group.begin();
            do {
                Function nextFunction = m_group.applyElemToFunction(m_function);
                if (!m_bitset.getBit(nextFunction))
                {
                    m_bitset.setBit(nextFunction);
                    count++;
                } 

            } while (m_group.nextElem());

            m_orbitCount[count]++;
            if (iterations % 1000000 == 0)
            {
                std::cout << "calculating ... m_fuction == " << m_function << std::endl;
            }
            iterations++;
        }
    }

private:
    int m_n;
    Bitset m_bitset;
    std::vector<int> m_orbitCount;
    uint64_t m_function;
    const std::string m_fileName;
    GroupType m_group;
};