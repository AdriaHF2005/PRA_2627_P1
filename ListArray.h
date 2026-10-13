#ifndef LISTARRAY_H
#define LISTARRAY_H

#include "List.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class ListArray : public List<T> {
private:
    static const int MINSIZE = 2;

    T* arr;
    int max;
    int n;

    void resize(int new_size) {
        T* new_arr = new T[new_size];

        for (int i = 0; i < n; i++) {
            new_arr[i] = arr[i];
        }

        delete[] arr;
        arr = new_arr;
        max = new_size;
    }

public:
    ListArray() : arr(new T[MINSIZE]), max(MINSIZE), n(0) {}

    ~ListArray() override {
        delete[] arr;
    }

    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("Invalid list position");
        }

        if (n == max) {
            resize(max * 2);
        }

        for (int i = n; i > pos; i--) {
            arr[i] = arr[i - 1];
        }

        arr[pos] = e;
        n++;
    }

    void append(T e) override {
        insert(n, e);
    }

    void prepend(T e) override {
        insert(0, e);
    }

    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Invalid list position");
        }

        T removed = arr[pos];

        for (int i = pos; i < n - 1; i++) {
            arr[i] = arr[i + 1];
        }

        n--;

        if (max > MINSIZE && n <= max / 4) {
            int new_size = max / 2;

            if (new_size < MINSIZE) {
                new_size = MINSIZE;
            }

            resize(new_size);
        }

        return removed;
    }

    T get(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Invalid list position");
        }

        return arr[pos];
    }

    int search(T e) override {
        for (int i = 0; i < n; i++) {
            if (arr[i] == e) {
                return i;
            }
        }

        return -1;
    }

    bool empty() override {
        return n == 0;
    }

    int size() override {
        return n;
    }

    T operator[](int pos) {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Invalid list position");
        }

        return arr[pos];
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    ListArray<T>& list) {
        out << "[";

        for (int i = 0; i < list.n; i++) {
            if (i > 0) {
                out << ", ";
            }

            out << list.arr[i];
        }

        out << "]";
        return out;
    }
};

#endif
