#pragma once

#include <iostream>
#include <fstream>

class Bitset
{
public:
    Bitset(uint64_t size)
    {
        m_blockCount = (size + BITS_IN_BLOCK - 1) / BITS_IN_BLOCK;
        m_data = new uint64_t[m_blockCount]();
    }

    void resize(uint64_t size)
    {
        delete m_data;
        m_blockCount = (size + BITS_IN_BLOCK - 1) / BITS_IN_BLOCK;
        m_data = new uint64_t[m_blockCount]();
    }

    Bitset()
        : m_data(nullptr)
        , m_blockCount(0)
    {
    }

    void clearBit(uint64_t index)
    {
        uint64_t& ref = m_data[index >> 6];
        const int MASK = (1 << 7) - 1;
        ref &= ~(1ll << (index & MASK));
    }

    void setBit(uint64_t index)
    {
        uint64_t& ref = m_data[index >> 6];
        const int MASK = (1 << 7) - 1;
        ref |= (1ll << (index & MASK));
    }

    bool getBit(uint64_t index)
    {
        const int MASK = (1 << 7) - 1;
        return !!(m_data[index >> 6] & (1ll << (index & MASK)));
    }

    ~Bitset()
    {
        delete m_data;
    }

    void serialize(std::ostream& out)
    {
        out << m_blockCount << std::endl;
        for (int i = 0; i < m_blockCount; ++i)
        {
            out << m_data[i] << ' ';
        }
    }

    void serialize(const std::string& fileName)
    {
        std::fstream fout;
        fout.open(fileName.c_str());
        serialize(fout);
    }

    void deserialize(std::istream& fin)
    {
        fin >> m_blockCount;
        m_data = new uint64_t[m_blockCount];
        for (int i = 0; i < m_blockCount; ++i)
        {
            fin >> m_data[i];
        }
    }

    void deserialize(const std::string& fileName)
    {
        std::fstream fin;
        fin.open(fileName.c_str());
        deserialize(fin);
    }

    uint64_t size() const
    {
        return m_blockCount * 64;
    }

private:
    uint64_t* m_data;
    uint64_t m_blockCount;
    const int BITS_IN_BLOCK = 64;
};