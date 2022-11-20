#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>

template <class T>
class Vector {
 private:

    // Текущий размер массива
    int curr = 0;
    // Резервируемый размер массива
    int alloc = 10;
    // Указатель на массив
    T *val_ = nullptr;

 protected:

    int standart = 10;

 public:

    explicit Vector(int n = 0) : curr(n) {
        if (n >= alloc) {
            alloc = n * 2;
        }
        val_ = new T[alloc] {};
    }

    Vector(const Vector &arg) : Vector(arg.curr) {
        curr = arg.curr;
        std::copy(arg.val_, arg.val_ + curr, val_);
    }

    Vector &operator=(const Vector &arg){
        Vector temp(arg);
        swap(*this, temp);
        return *this;
    }

    Vector(Vector &&arg) {
        curr = arg.curr, alloc = arg.alloc, val_ = arg.val_, standart = arg.standart;
        arg.curr = 0, arg.alloc = 0, arg.val_ = nullptr;
    }

    Vector &operator=(Vector &&arg) {
        if (this != &arg) {
            swap(*this, arg);
            delete[] arg.val_, arg.val_ = nullptr;
            arg.curr = 0, arg.alloc = 0;
        }
        return *this;
    }

    virtual ~Vector() {
        delete[] val_;
    }


    //warning: control reaches of non-void functions
    T &operator[](int i)  {
        return val_[i];
    }

    static int size(const Vector &arg) {
        return arg.curr;
    }

    void add(const Vector &arg, const int &k) {
        int mn = std::min(Vector::size(arg), k);
        for (int i = 0; i < mn; ++i) {
            push_back(arg.val_[i]);
        }
    }

    void insert(const T &d, const int &k) {
        if (k == 0) {
            push_front(d);
            return;
        } else if (k == curr) {
            push_back(d);
            return;
        } else if (k > 0 && k < curr) {
            push_back(d);
            T t = val_[k], p;
            for (int i = k; i < curr; ++i) {
                p = val_[i], val_[i] = t, t = p;
            }
            val_[k] = d;
            return;
        }
    }

    void push_back(const T &d) {
        if (curr < alloc) {
            val_[curr] = d, ++curr;
            return;
        }
        T *b = val_;
        val_ = new T[alloc * 2] {};
        std::copy(b, b + curr, val_);
        delete[] b;
        alloc *= 2;
    }

    void push_front(const T &d) {
        push_back(d);
        T t = val_[0], p;
        for (int i = 1; i < curr; ++i) {
            p = val_[i], val_[i] = t, t = p;
        }
        val_[0] = d;
    }

    void clear() {
        delete[] val_;
        val_ = new T[standart] {};
        curr = 0, alloc = standart;
    }

    int size() const { return curr; }

    bool empty() const { return curr == 0; }

    T erase(int i) noexcept(false) {
        if (curr > 0 && i < curr) {
            T d = val_[i];
            std::copy(val_ + i + 1, val_ + curr, val_ + i);
            --curr;
            return d;
        }
        throw std::out_of_range("Out of range");
    }

    T pop_front() {
        return erase(0);
    }

    T pop_back() {
        T d = T();
        if (curr > 0) {
            d = val_[curr - 1], --curr;
        }
        return d;
    }

    explicit operator bool() {
        return curr != 0;
    }

    friend void swap(Vector &first, Vector &second) {
        std::swap(first.standart, second.standart);
        std::swap(first.val_, second.val_);
        std::swap(first.alloc, second.alloc);
        std::swap(first.curr, second.curr);
    }

    class iterator {
    public:
        T *i; //указатель на тип данных
        iterator() : i(0) {}
        explicit iterator(T *n) : i(n) {}
        iterator(const iterator &o): i(o.i){}
        T &operator*() const { return *i; }
        T *operator->() const { return i; }
        T &operator[](int j) const { return i[j]; }
        bool operator==(const iterator &o) const { return i == o.i; }
        bool operator!=(const iterator &o) const { return i != o.i; }
        iterator &operator++() { ++i; return *this; }
    };

    typename Vector<T>::iterator begin() { return iterator(&val_[0]); }
    typename Vector<T>::iterator end() { return iterator(&val_[curr]); }

};

#endif // VECTOR_H
