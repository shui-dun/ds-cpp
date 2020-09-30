#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include "chtbl.hpp"

namespace ds {
template <class T>
class OHTbl {
private:
    int len_;

    int amount_;

    T* base_;

    enum Status {
        NUL,
        NORMAL,
        REMOVED
    } *status_;

    int hash_code_(const T& key) const {
        return Hash::code(key) % len_;
    }

public:
    OHTbl(int len) : amount_(0), len_(len), base_(new T[len]), status_(new Status[len]) {}

    OHTbl(std::vector<T> vec, int len) : amount_(0), len_(len), base_(new T[len]), status_(new Status[len]) {
        for (auto e : vec)
            insert(e);
    }

    ~OHTbl() {
        delete[] base_;
        delete[] status_;
    }

    bool find(const T& data) const {
        int init_ind = hash_code_(data);
        int ind = init_ind;
        do {
            if (status_[ind] == NUL)
                return false;
            if (status_[ind] == NORMAL && base_[ind] == data)
                return true;
            ind = (ind + 1) % len_;
        } while (ind != init_ind);
        return false;
    }

    int amount() const {
        return amount_;
    }

    bool insert(const T& data) {
        if (amount_ == len_)
            throw std::overflow_error("OHTbl<T>::insert");
        int ind = hash_code_(data);
        while (true) {
            if (base_[ind] == data && status_[ind] == NORMAL) {
                return false;
            } else if (status_[ind] != NORMAL) {
                status_[ind] = NORMAL;
                amount_++;
                base_[ind] = data;
                return true;
            }
            ind = (ind + 1) % len_;
        }
    }

    bool remove(const T& data) {
        if (amount_ == 0)
            throw std::underflow_error("OHTbl::remove");
        int init_ind = hash_code_(data);
        int ind = init_ind;
        do {
            if (base_[ind] == data && status_[ind] == NORMAL) {
                amount_--;
                status_[ind] = REMOVED;
                return true;
            }
            if (status_[ind] == NUL)
                return false;
            ind = (ind + 1) % len_;
        } while (ind != init_ind);
        return false;
    }

    friend std::ostream& operator<<(std::ostream& out, const OHTbl<T>& tbl) {
        for (int i = 0; i < tbl.len_; i++)
            if (tbl.status_[i] == tbl.NORMAL)
                out << tbl.base_[i] << ' ';
            else if (tbl.status_[i] == tbl.REMOVED)
                out << "RM ";
            else
                out << "NUL ";
        out << '\n';
        return out;
    }
};
}  // namespace ds