// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector {
protected:
    size_t sz;
    T* pMem;

public:
    TDynamicVector(size_t size = 1) {
        if (size == 0 || size > MAX_VECTOR_SIZE) throw out_of_range("Vector size should be greater than zero");

        sz = size;
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }

    TDynamicVector(T* arr, size_t s) {
        if (arr == nullptr) throw invalid_argument("Array == nullptr!");
        if (s == 0 || s > MAX_VECTOR_SIZE) throw out_of_range("Vector size should be greater than zero");

        sz = s;
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v) : sz(v.sz), pMem(new T[v.sz]) {
        std::copy(v.pMem, v.pMem + sz, pMem);
    }

    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem) {
        v.sz = 0;
        v.pMem = nullptr;
    }

    ~TDynamicVector() {
        delete[] pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v) {
        if (&v == this) return *this;

        sz = v.sz;
        delete[] pMem;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (&v == this) return *this;

        sz = v.sz;
        delete[] pMem;
        pMem = v.pMem;
        v.sz = 0;
        v.pMem = nullptr;
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind) {
        assert(ind < sz);
        return pMem[ind];
    }

    const T& operator[](size_t ind) const {
        assert(ind < sz);
        return pMem[ind];
    }

    // индексация с контролем
    T& at(size_t ind) {
        if (ind >= sz) throw out_of_range("index out of range");
        return pMem[ind];
    }

    const T& at(size_t ind) const {
        if (ind >= sz) throw out_of_range("index out of range");
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept {
        if (sz != v.sz) return false;
        for (size_t i = 0; i < sz; i++) if (pMem[i] != v.pMem[i]) return false;
        return true;
    }

    bool operator!=(const TDynamicVector& v) const noexcept {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val) const {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) res.pMem[i] = pMem[i] + val;
        return res;
    }

    TDynamicVector operator-(T val) const {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) res.pMem[i] = pMem[i] - val;
        return res;
    }

    TDynamicVector operator*(T val) const {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) res.pMem[i] = pMem[i] * val;
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v) const {
        if (sz != v.sz) throw invalid_argument("unacceptable vector size");

        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) res.pMem[i] = pMem[i] + v.pMem[i];
        return res;
    }

    TDynamicVector operator-(const TDynamicVector& v) const {
        if (sz != v.sz) throw invalid_argument("unacceptable vector size");

        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) res.pMem[i] = pMem[i] - v.pMem[i];
        return res;
    }

    T operator*(const TDynamicVector& v) const {
        if (sz != v.sz) throw invalid_argument("unacceptable vector size");

        T res = T();
        for (size_t i = 0; i < sz; i++) res += pMem[i] * v.pMem[i];
        return res;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
    }

    // матрично-скалярные операции
    TDynamicVector<T> operator*(const T& val)
    {
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
    }
};

#endif
