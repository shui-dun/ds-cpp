#pragma once
#include <iostream>
#include <stdexcept>

namespace ds {
template <typename T>
class Stack {
private:
    int capacity_;

    int len_;

    T* base_;

public:
    Stack(int size = 10) : capacity_(size), len_(0), base_(new T[size]) {}

    Stack(const T* array, int len) : capacity_(2 * len), len_(len), base_(new T[2 * len]) {
        for (int i = 0; i < len; i++)
            base_[i] = array[i];
    }

    ~Stack() {
        delete[] base_;
    }

    void push(const T& data) {
        if (len_ == capacity_) {
            base_ = (T*)realloc(base_, sizeof(T) * (2 * len_));
            capacity_ *= 2;
        }
        base_[len_++] = data;
    }

    T pop() {
        if (len_ == 0)
            throw std::underflow_error("stack::pop");
        len_--;
        return base_[len_];
    }

    T& peek() const {
        if (len_ == 0)
            throw std::underflow_error("Stack::pop");
        return base_[len_ - 1];
    }

    bool empty() const {
        return len_ == 0;
    }

    bool full() const {
        return len_ == capacity_;
    }

    int capacity() const {
        return capacity_;
    }
};
}  // namespace ds
