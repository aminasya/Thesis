
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm>

/*
Coset getRandomDim3Coset()
{
    Coset res;

    res.insert(0);

    int a;
    do {
        a = rand() % (1 << N);
    } while (res.find(a) != res.end());
    res.insert(a);

    int b;
    do {
        b = rand() % (1 << N);
    } while (res.find(b) != res.end());
    res.insert(b);
    res.insert(a ^ b);

    int c;
    do {
        c = rand() % (1 << N);
    } while (res.find(c) != res.end());
    res.insert(c);
    res.insert(a ^ c);
    res.insert(b ^ c);
    res.insert(a ^ b ^ c);


    Coset res2;
    int shift = rand() % (1 << N);
    for (int v : res) {
        res2.insert(v ^ shift);
    }

    return res2;
}


Cosets getCosetsDim3()
{
    Cosets res;

    while (res.size() < numberOf3DimCosets) {
        res.insert(getRandomDim3Coset());
    }
    return res;
}

Cosets getCosets()
{
    Cosets res;
    insertIntoSet(getCosetsDim0(), res);
    insertIntoSet(getCosetsDim1(), res);
    insertIntoSet(getCosetsDim2(), res);
    insertIntoSet(getCosetsDim3(), res);

    return res;
}

Set getRandomSet(int count)
{
    Set res;
    while (count--) {
        int oldSize = res.size();
        do {
            int elem = rand() % (1 << N);
            res.insert(elem);
        } while (oldSize == res.size());
    }
    return res;
}

void printVector(int vec)
{
    for (int i = 0; i < N; ++i) {
        std::cout << !!(vec & (1 << i));
    }
    std::cout << std::endl;
}

void printSet(const Set& set)
{
    for (int elem : set) {
        printVector(elem);
    }
    std::cout << "-------------------------" << std::endl;
}

bool setInSet(const Set& first, const Set& second)
{
    for (int elem : first) {
        if (second.find(elem) == second.end()) {
            return false;
        }
    }
    return true;
}

void cover(const Set& set, const Cosets& allCosets)
{
    Cosets availableCosets;
    for (const Coset& cos : allCosets) {
        if (setInSet(cos, set)) {
            availableCosets.insert(cos);
        }
    }

    std::vector<Set> cosetsV(availableCosets.begin(), availableCosets.end());
    std::cout << "cosetV.size() = " << cosetsV.size() << std::endl;

    int count = set.size();

    while (true) {
        Set other;
        int countCopy = count;
        while (countCopy--) {
            insertIntoSet(cosetsV[rand() % cosetsV.size()], other);
        }
        if (other.size() == set.size()) {
            std::cout << count << std::endl;
            count--;
        }
    }
}

int main()
{
    srand(time(NULL));
    Cosets allCosets = getCosets();

    Set set = getRandomSet(8);
    printSet(set);

    cover(set, allCosets);

}
*/

typedef std::vector<int> Matrix;
typedef std::set<Matrix> Set;

void printMatix(const Matrix& m)
{
    for (uint32_t i = 0; i < m.size(); ++i)
    {
        for (uint32_t j = 0; j < m.size(); ++j)
            std::cout << !!(m[i] & (1 << j));
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void insertIntoSet(const Set& first, Set& second)
{
    for (auto elem : first) {
        second.insert(elem);
    }
}

Set getAllMaticesHelper(Matrix& cur, int row = 0)
{
    const int n = cur.size();
    Set result;
    if (row == n)
    {
        result.insert(cur);
        return result;
    }

    for (int mask = 0; mask < (1 << n); ++mask)
    {
        cur[row] = mask;
        auto matrices = getAllMaticesHelper(cur, row + 1);
        insertIntoSet(matrices, result);
    }
    return result;
}

Set getAllMatrices(int n)
{
    Matrix m(n);
    return getAllMaticesHelper(m, 0);
}

bool determinantHelper(const Matrix& matrix, std::vector<bool>& rows, std::vector<bool>& columns, int count)
{
    auto rowIt = std::find(rows.begin(), rows.end(), true);
    assert(rowIt != rows.end());
    int rowIndex = rowIt - rows.begin();

    auto columnIt = std::find(columns.begin(), columns.end(), true);
    assert(columnIt != columns.end());
    int columnIndex = columnIt - columns.begin();

    if (count == 1)
    {
        bool value = static_cast<bool>(matrix[rowIndex] & (1 << columnIndex));
        return value;
    }

    bool res = 0;
    for (uint32_t i = 0; i < columns.size(); ++i)
    {
        if (!columns[i] || !(matrix[rowIndex] & (1 << i)))
            continue;

        rows[rowIndex] = false;
        columns[i] = false;
        res ^= determinantHelper(matrix, rows, columns, count - 1);

        rows[rowIndex] = true;
        columns[i]  = true;
    }
    return res;
}

bool determinant(const Matrix& matrix)
{
    int n = matrix.size();
    std::vector<bool> rows(n, 1);
    std::vector<bool> columns(n, 1);
    return determinantHelper(matrix, rows, columns, matrix.size());
}

void sumAsign(Matrix& lhs, const Matrix& rhs)
{
    for (uint32_t i = 0; i < lhs.size(); ++i)
    {
        lhs[i] ^= rhs[i];
    }
}

Matrix sum(const Matrix& lhs, const Matrix& rhs)
{
    Matrix res = lhs;
    sumAsign(res, rhs);
    return res;
}

Matrix sum(const Matrix& A, const Matrix& B, const Matrix& C)
{
    Matrix res = A;
    sumAsign(res, B);
    sumAsign(res, C);
    return res;
}

Set getAllNonDegenerateMatrices(int n)
{
    auto allMatices = getAllMatrices(n);
    Set nondegenerateMatices;
    for (auto& m : allMatices)
    {
        if (determinant(m))
        {
            nondegenerateMatices.insert(m);
        }
    }
    return nondegenerateMatices;
}

Set getAllTranspositions(int n)
{
    Set res;

    for (uint16_t i = 0; i < n; ++i)
        for (uint16_t j = i; j < n; ++j)
        {
            Matrix m(n);

            for (uint16_t k = 0; k < n; ++k)
            {
                if (k == i || k == j)
                    continue;
                m[k] = (1 << k);
            }
            m[i] = (1 << j);
            m[j] = (1 << i);

            res.insert(m);
        }
    return res;
}

typedef std::set<Matrix> Coset;
typedef std::set<Coset> Cosets;

template<typename SetType>
void insertIntoSet(const SetType& first, SetType& second)
{
    for (auto elem : first) {
        second.insert(elem);
    }
}

void printCoset(const Coset& coset)
{
    for (auto m : coset)
    {
        printMatix(m);
    }
    std::cout << "--------------------------------------------" << std::endl;
}

Cosets getCosetsDim0(const Set& allToCover)
{
    Cosets res;
    for (auto& m : allToCover)
    {
        res.insert(Coset{ m });
    }
    return res;
}

Cosets getCosetsDim1(const Set& allToCover)
{
    Cosets res;
    for (auto& m1 : allToCover)
    {
        for (auto& m2 : allToCover)
        {
            if (m1 != m2)
            {
                res.insert(Coset{m1, m2});
            }
        }
    }
    return res;
}

Cosets getCosetsDim2(const Set& allToCover)
{
    Cosets res;

    std::vector<Matrix> allVec(allToCover.begin(), allToCover.end());

    for (uint16_t i = 0; i < allVec.size(); ++i) {
        for (uint16_t j = i + 1; j < allVec.size(); ++j) {
            for (uint16_t k = j + 1; k < allVec.size(); ++k) {

                Matrix f = allVec[i];
                sumAsign(f, allVec[j]);
                sumAsign(f, allVec[k]);
 
                /*
                if (determinant(f))
                {
                    res.insert(Coset{ allVec[i], allVec[j], allVec[k], f });
                    std::cout << res.size() << std::endl;
                }
                */
                if (allToCover.find(f) != allToCover.end())
                    res.insert(Coset{ allVec[i], allVec[j], allVec[k], f });
            }
        }
    }
    return res;
}

Coset getRandomDim3Coset(const Set& allToCover)
{
    std::vector<Matrix> allVec(allToCover.begin(), allToCover.end());

    while (true)
    {
        int idx1 = std::rand() % allVec.size();
        int idx2 = std::rand() % allVec.size();
        if (idx2 == idx1)
            continue;
        int idx3 = std::rand() % allVec.size();
        if (idx3 == idx1 || idx3 == idx2)
            continue;

        int idx4 = std::rand() % allVec.size();
        if (idx4 == idx1 || idx4 == idx2 || idx4 == idx3)
            continue;


        Matrix a = allVec[idx1];
        Matrix b = allVec[idx2];
        Matrix c = allVec[idx3];
        Matrix d = allVec[idx4];

        Matrix abc = sum(a, b, c);
        if (abc == d || allToCover.find(abc) == allToCover.end())
            continue;

        Matrix abd = sum(a, b, d);
        if (abd == c || allToCover.find(abd) == allToCover.end())
            continue;

        Matrix acd = sum(a, c, d);
        if (acd == b || allToCover.find(acd) == allToCover.end())
            continue;

        Matrix bcd = sum(b, c, d);
        if (bcd == a ||allToCover.find(bcd) == allToCover.end())
            continue;

        return Coset{ a, b, c, d, abc, abd, acd, bcd };
    }
}

Coset getRandomDim4Coset(const Set& allToCover)
{
    std::vector<Matrix> allVec(allToCover.begin(), allToCover.end());

    while (true)
    {
        static int checked;
        std::cout << checked++ << std::endl;

        int idx1 = std::rand() % allVec.size();
        int idx2 = std::rand() % allVec.size();
        if (idx2 == idx1)
            continue;
        int idx3 = std::rand() % allVec.size();
        if (idx3 == idx1 || idx3 == idx2)
            continue;

        int idx4 = std::rand() % allVec.size();
        if (idx4 == idx1 || idx4 == idx2 || idx4 == idx3)
            continue;

        int idx5 = std::rand() % allVec.size();
        if (idx5 == idx1 || idx5 == idx2 || idx5 == idx3 || idx5 == idx4)
            continue;

        Matrix a = allVec[idx1];
        Matrix b = allVec[idx2];
        Matrix c = allVec[idx3];
        Matrix d = allVec[idx4];
        Matrix e = allVec[idx5];

        Matrix ar[5] = { a, b, c, d, e };

        Coset res{ a, b, c, d, e };

        bool ok = true;
        for (uint16_t i = 0; i < 5; ++i)
            for (uint16_t j = i + 1; j < 5; ++j)
                for (uint16_t k = j + 1; k < 5; ++k)
                {
                    Matrix m = sum(ar[i], ar[j], ar[k]);

                    if (res.find(m) != res.end() || allToCover.find(m) == allToCover.end())
                    {
                        i = 5;
                        j = 5;
                        ok = false;
                        break;
                    }
                    res.insert(m);
                }

        if (!ok)
            continue;

        Matrix mm = sum(a, b, c);
        Matrix mmm = sum(mm, d, e);

        if (res.find(mmm) != res.end() || allToCover.find(mmm) == allToCover.end())
            continue;

        res.insert(mmm);
        return res;
    }
}

int main()
{
    srand(time(0));
    int n = 3;
    auto toCover = getAllNonDegenerateMatrices(n);
    //auto toCover = getAllTranspositions(n);
    printCoset(toCover);


    //auto cosets2 = getCosetsDim2(toCover);
    //std::cout << cosets2.size() << std::endl;
    //for (const Coset& c : getCosetsDim2(toCover))
    //{
    //    printCoset(c);
    //}

    Coset cos4 = getRandomDim4Coset(toCover);
    printCoset(cos4);

}


