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
        if (size == 0 || s > MAX_VECTOR_SIZE) throw out_of_range("Vector size should be greater than zero");

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
    using TDynamicVector<TDynamicVector<T>>::size;
    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::at;

    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s == 0 || s > MAX_MATRIX_SIZE) throw out_of_range("invalid matrix size");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; i++) if (pMem[i] != m.pMem[i]) return false;
        return true;
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept {
        return !(*this == m);
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val) {
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            for (size_t j = 0; j < sz; j++)
                res[i][j] = pMem[i][j] * val;
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
        if (v.sz != sz) throw std::invalid_argument("matrix size != vector size");

        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++)
            for (size_t j = 0; j < sz; j++)
                res[i] += pMem[i][j] * v[j];
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m) {
        if (m.sz != sz) throw std::invalid_argument("matrix size != this matrix size");

        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            for (size_t j = 0; j < sz; j++)
                res[i][j] = pMem[i][j] + m[i][j];
        return res;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m) {
        if (m.sz != sz) throw std::invalid_argument("matrix size != this matrix size");

        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            for (size_t j = 0; j < sz; j++)
                res[i][j] = pMem[i][j] - m[i][j];
        return res;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m) {
        if (m.sz != sz) throw std::invalid_argument("matrix size != this matrix size");

        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            for (size_t j = 0; j < sz; j++)
                for (size_t k = 0; k < sz; ++k)
                    res[i][j] += pMem[i][k] * m.pMem[k][j];
        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v) {
        for (size_t i = 0; i < v.sz; i++)
            for (size_t j = 0; j < v.sz; j++)
                istr >> v.pMem[i][j];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v) {
        for (size_t i = 0; i < v.sz; i++) {
            for (size_t j = 0; j < v.sz; j++)
                ostr << v.pMem[i][j] << ' ';
            ostr << '\n';
        }
        return ostr;
    }
};

//нормальный вектор:
template<typename T>
class TDynamicArray {
private:
    T* pMem;
    size_t sz;
    size_t capacity;

public:
    TDynamicArray() : pMem(nullptr), sz(0), capacity(0) {}

    TDynamicArray(size_t size) : pMem(size > 0 ? new T[size * 2]() : nullptr), sz(size), capacity(size * 2) {}

    TDynamicArray(const TDynamicArray& v) : pMem(v.capacity > 0 ? new T[v.capacity]() : nullptr), sz(v.sz), capacity(v.capacity) {
        if (sz > 0) std::copy(v.pMem, v.pMem + sz, pMem);
    }

    TDynamicArray(TDynamicArray&& v) : pMem(v.pMem), sz(v.sz), capacity(v.capacity) { v.pMem = nullptr; v.sz = 0; v.capacity = 0; }

    ~TDynamicArray() { delete[] pMem; }

    TDynamicArray& operator=(const TDynamicArray& v) {
        if (this == &v) return *this;

        sz = v.sz;
        capacity = v.capacity;
        delete[] pMem;
        pMem = new T[capacity]();
        std::copy(v.pMem, v.pMem + capacity, pMem);
        return *this;
    }

    TDynamicArray& operator=(TDynamicArray&& v) {
        if (this == &v) return *this;

        sz = v.sz;
        capacity = v.capacity;
        delete[] pMem;
        pMem = v.pMem;
        v.pMem = nullptr;
        v.sz = 0;
        v.capacity = 0;
        return *this;
    }

    size_t size() const { return sz; }

    size_t get_capacity() const { return capacity; }

    bool empty() const { return sz == 0; }

    void clear() { for (size_t i = 0; i < sz; i++) pMem[i] = T(); sz = 0; }

    void swap(TDynamicArray& v) {
        std::swap(pMem, v.pMem);
        std::swap(sz, v.sz);
        std::swap(capacity, v.capacity);
    }

    T& operator[](size_t i) { return pMem[i]; }

    const T& operator[](size_t i) const { return pMem[i]; }

    T& at(size_t i) {
        if (i >= sz) throw std::out_of_range("index out of range");
        return pMem[i];
    }

    const T& at(size_t i) const {
        if (i >= sz) throw std::out_of_range("index out of range");
        return pMem[i];
    }

    void reserve(size_t newCapacity) {
        if (newCapacity <= capacity) return;

        T* tmp = new T[newCapacity]();
        std::copy(pMem, pMem + sz, tmp);
        delete[] pMem;
        pMem = tmp;
        capacity = newCapacity;
    }

    void resize(size_t count) {
        if (count < capacity) { sz = count; return; }
        reserve(count * 2);
        sz = count;
    }

    void push_back(const T& a) {
        resize(sz + 1);
        pMem[sz - 1] = a;
    }

    void pop_back() { 
        if ((*this).empty()) throw std::out_of_range("pop_back + empty array!");
        resize(sz - 1); 
    }

    void insert(size_t pos, const T& a) {
        resize(sz + 1);
        for (size_t i = sz - 1; i > pos; i--)
            pMem[i] = pMem[i - 1];
        pMem[pos] = a;
    }

    void erase(size_t pos) {
        for (size_t i = pos + 1; i < sz; i++)
            pMem[i - 1] = pMem[i];
        resize(sz - 1);
    }
};

//CRS матрица
template <typename T>
class TCRSMatrix {
private:
    size_t rows;
    size_t cols;
    TDynamicArray<T> data;
    TDynamicArray<size_t> col;
    TDynamicArray<size_t> row;

public:
    TCRSMatrix(size_t _rows = 1, size_t _cols = 1) : rows(_rows), cols(_cols), row(rows + 1) { }

    size_t get_rows() const { return rows; }

    size_t get_cols() const { return cols; }

    size_t get_DataSize() const { return data.size(); }

    T get(size_t _row, size_t _col) const {
        if (_row >= rows || _col >= cols) throw std::out_of_range("index out of range");

        for (size_t i = row[_row]; i < row[_row + 1]; i++) if (col[i] == _col) return data[i];
        return T();
    }

    void set(size_t _row, size_t _col, T val) {
        if (_row >= rows || _col >= cols) throw std::out_of_range("index out of range");

        for (size_t i = row[_row]; i < row[_row + 1]; i++) {
            if (col[i] == _col) {
                if (val == T()) {
                    data.erase(i);
                    col.erase(i);
                    for (size_t k = _row + 1; k <= rows; k++) row[k] -= 1;
                }
                else data[i] = val;
                return;
            }
        }
        //если место не было занято:
        if (val == T()) return;
        size_t pos = row[_row];
        while (pos < row[_row + 1] && col[pos] < _col) pos++; //ищем правильное место, потому что col должен быть отсортирован для последующих алгоритмов
        for (size_t i = _row + 1; i <= rows; i++) row[i] += 1;
        col.insert(pos, _col);
        data.insert(pos, val);
    }

    //матрица на скаляр
    TCRSMatrix<T> operator*(const T& val) const {
        TCRSMatrix<T> res = *this;
        if (val == T()) {
            res.col.clear();
            for (size_t i = 0; i <= res.rows; i++) res.row[i] = 0;
            res.data.clear();
        }
        else for (size_t i = 0; i < res.data.size(); i++) res.data[i] *= val;
        return res;
    }

    //матрица на вектор
    TDynamicArray<T> operator*(const TDynamicArray<T>& v) const {
        if (v.size() != cols) throw std::invalid_argument("matrix size != vector size");

        TDynamicArray<T> res(rows);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = row[i]; j < row[i + 1]; j++) //для каждой строки по элементам
                res[i] += data[j] * v[col[j]];
        return res;
    }

    //матрично матричные операции
    TCRSMatrix<T> operator+(const TCRSMatrix<T>& m) const {
        if (rows != m.rows || cols != m.cols) throw std::invalid_argument("matrix size != this matrix size");

        TCRSMatrix<T> res(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            size_t thisRow = row[i], endThisRow = row[i + 1], 
                mRow = m.row[i], endMRow = m.row[i + 1];
            while (thisRow < endThisRow && mRow < endMRow) {
                if (col[thisRow] < m.col[mRow]) {
                    res.col.push_back(col[thisRow]);
                    res.data.push_back(data[thisRow]);
                    thisRow += 1;
                }
                else if (col[thisRow] > m.col[mRow]) {
                    res.col.push_back(m.col[mRow]);
                    res.data.push_back(m.data[mRow]);
                    mRow += 1;
                }
                else {
                    T sum = data[thisRow] + m.data[mRow];
                    if (sum != T()) { //0 не записываем
                        res.col.push_back(col[thisRow]);
                        res.data.push_back(sum);
                    }
                    thisRow += 1; mRow += 1;
                }
            }
            //обрабатываем концы
            while (thisRow < endThisRow) {
                res.col.push_back(col[thisRow]);
                res.data.push_back(data[thisRow]);
                thisRow += 1;
            }
            while (mRow < endMRow) {
                res.col.push_back(m.col[mRow]);
                res.data.push_back(m.data[mRow]);
                mRow += 1;
            }
            res.row[i + 1] = res.data.size(); //не забываем про row
        }
        return res;
    }

    TCRSMatrix<T> operator-(const TCRSMatrix<T>& m) const {
        if (rows != m.rows || cols != m.cols) throw std::invalid_argument("matrix size != this matrix size");

        TCRSMatrix<T> res(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            size_t thisRow = row[i], endThisRow = row[i + 1],
                mRow = m.row[i], endMRow = m.row[i + 1];
            while (thisRow < endThisRow && mRow < endMRow) {
                if (col[thisRow] < m.col[mRow]) {
                    res.col.push_back(col[thisRow]);
                    res.data.push_back(data[thisRow]);
                    thisRow += 1;
                }
                else if (col[thisRow] > m.col[mRow]) {
                    res.col.push_back(m.col[mRow]);
                    res.data.push_back(-m.data[mRow]); //тут - !
                    mRow += 1;
                }
                else {
                    T diff = data[thisRow] - m.data[mRow];
                    if (diff != T()) { //0 не записываем
                        res.col.push_back(col[thisRow]);
                        res.data.push_back(diff);
                    }
                    thisRow += 1; mRow += 1;
                }
            }
            //обрабатываем концы
            while (thisRow < endThisRow) {
                res.col.push_back(col[thisRow]);
                res.data.push_back(data[thisRow]);
                thisRow += 1;
            }
            while (mRow < endMRow) {
                res.col.push_back(m.col[mRow]);
                res.data.push_back(-m.data[mRow]); //тут - !
                mRow += 1;
            }
            res.row[i + 1] = res.data.size(); //не забываем про row
        }
        return res;
    }

    TCRSMatrix<T> operator*(const TCRSMatrix<T>& m) const {
        if (m.rows != cols) throw std::invalid_argument("matrix sizes bad");

        TCRSMatrix<T> res(rows, m.cols);
        TDynamicArray<T> sums(m.cols); //работаем со строками поэтому параллельно считаем несколько сумм
        for (size_t i = 0; i < rows; i++) { //по строкам нашей матрицы
            for (size_t j = 0; j < m.cols; j++) sums[j] = T();
            for (size_t thRow = row[i]; thRow < row[i + 1]; thRow++) { //по столбцам для i строки
                size_t k = col[thRow]; //достаём номер столбца, то есть рассматриваем элемент i,k
                for (size_t mRow = m.row[k]; mRow < m.row[k + 1]; mRow++) { //по столбцам k строки другой матрицв
                    sums[m.col[mRow]] += data[thRow] * m.data[mRow]; //для столбца другой матрицы записываем в сумму новое слагаемое
                }
            }
            for (size_t j = 0; j < m.cols; j++) if (sums[j] != T()) res.set(i, j, sums[j]); //записываем результат
        }
        return res;
    }
};

#endif
