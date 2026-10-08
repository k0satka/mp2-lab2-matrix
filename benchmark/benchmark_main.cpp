//тест производительности умножения

#include <iostream>
#include <chrono>
#include "tmatrix.h"

template<typename Tfunc>
double  workTime(Tfunc function) {
    auto start = std::chrono::high_resolution_clock::now();
    function();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void basicMult(size_t sz) {
    TDynamicMatrix<int> m1(sz), m2(sz);

    for (size_t i = 0; i < sz; i++) 
        for (size_t j = 0; j < sz; j++) {
            m1[i][j] = 1;
            m2[i][j] = 2;
        }

    double sum = 0.0;
    for (size_t i = 0; i < 5; i++) {
        TDynamicMatrix<int> res(sz);
        sum += workTime([&]() { res = m1 * m2; });
    }

    std::cout << "basic *: " << sum / 5.0 << "ms\n";
}
void optimizedMult(size_t sz) {
    TDynamicMatrix<int> m1(sz), m2(sz);

    for (size_t i = 0; i < sz; i++)
        for (size_t j = 0; j < sz; j++) {
            m1[i][j] = 1;
            m2[i][j] = 2;
        }

    double sum = 0.0;
    for (size_t i = 0; i < 5; i++) {
        TDynamicMatrix<int> res(sz);
        sum += workTime([&]() { res = m1.bestMult(m2); });
    }

    std::cout << "optimized *: " << sum / 5.0 << "ms\n";
}

void blockMult(size_t sz) {
    TDynamicMatrix<int> m1(sz), m2(sz);

    for (size_t i = 0; i < sz; i++)
        for (size_t j = 0; j < sz; j++) {
            m1[i][j] = 1;
            m2[i][j] = 2;
        }
    
    std::cout << "block + optimized*: \n";
    for (size_t szBlock = 8; szBlock <= 64; szBlock *= 2) {
        double sum = 0.0;
        for (size_t i = 0; i < 5; i++) {
            TDynamicMatrix<int> res(sz);
            sum += workTime([&]() { res = m1.blockMult(m2, szBlock); });
        }
        std::cout << "block size " << szBlock << ": " << sum / 5.0 << "ms\n";
    }
}

void crsMult(size_t sz, int p)
{
    TCRSMatrix<int> m1(sz, sz), m2(sz, sz);

    for (size_t i = 0; i < sz; i++)
        for (size_t j = 0; j < sz; j += p) {
            m1.set(i, j, 1);
            m2.set(i, j, 2);
        }

    double sum = 0.0;
    for (size_t i = 0; i < 5; i++) {
        TCRSMatrix<int> res;
        sum += workTime([&]() { res = m1 * m2; });
    }

    std::cout << "crs *: " << sum / 5.0 << "ms\n";
}

int main()
{
    std::cout << "------ size: 200 --------\n";
    basicMult(200);
    optimizedMult(200);
    blockMult(200);

    std::cout << "------ size: 400 --------\n";
    basicMult(400);
    optimizedMult(400);
    blockMult(400);

    std::cout << "------ size: 800 100% --------\n";
    crsMult(800, 1);
    basicMult(800);
    optimizedMult(800);
    blockMult(800);

    std::cout << "------ size: 800, 50% --------\n";
    crsMult(800, 2);

    std::cout << "------ size: 800, 25% --------\n";
    crsMult(800, 4);

    std::cout << "------ size: 800, 10% --------\n";
    crsMult(800, 10);
    //на всякий случай
    basicMult(800);
    optimizedMult(800);
    blockMult(800);

    return 0;
}