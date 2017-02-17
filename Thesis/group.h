#pragma once

#include "algo.h"

class Group
{
public:
    virtual void begin() = 0;
    virtual bool nextElem() = 0;
    virtual Function applyElemToFunction(Function function) = 0;
};


class PermutationGroup : public Group
{
public:
    PermutationGroup(int n)
        : m_permuations(getAllPermutations(n))
        , m_idx(0)
        , m_n(n)
    {
    }

    void begin()
    {
        m_idx = 0;
    }

    bool nextElem()
    {
        m_idx++;
        return m_idx != m_permuations.size();
    }

    Function applyElemToFunction(Function function)
    {
        return applyPermutation(function, m_permuations[m_idx], m_n);
    }

private:
    Permutations m_permuations;
    int m_idx;
    int m_n;
};

class AdditionGroup : public Group
{
public:
    AdditionGroup(int n)
        : m_currentVector(0)
        , m_n(n)
    {}

    void begin()
    {
        m_currentVector = 0;
    }

    bool nextElem()
    {
        m_currentVector++;
        return m_currentVector != (1 << m_n);
    }

    Function applyElemToFunction(Function function)
    {
        return function ^ m_currentVector;
    }

private:
    UnderlyingType m_currentVector;
    int m_n;
};




