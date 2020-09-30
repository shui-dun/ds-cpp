#pragma once
#include <string>
#include <iterator>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

namespace ds {
struct Hash {
    static unsigned code(std::string key) {
        unsigned int hash = 1315423911;
        for (auto ch : key)
            hash ^= ((hash << 5) + (hash >> 2) + ch);
        return hash;
    }

    static unsigned code(unsigned key) {
        key = ~key + (key << 15);
        key = key ^ (key >> 12);
        key = key + (key << 2);
        key = key ^ (key >> 4);
        key = key * 2057;
        key = key ^ (key >> 16);
        return key;
    }

    static unsigned code(double key) {
        double tmp = key;
        if (key < 0)
            tmp = -key;
        double e = ceil(log(key));
        return (unsigned)((INT64_MAX + 1.0) * tmp * exp(-e));
    }
};

template <class T>
class CHTbl {
private:
    int len_;

    std::vector<T>* base_;

    int hash_code_(const T& key) const {
        return Hash::code(key) % len_;
    }

public:
    CHTbl(int len) : len_(len), base_(new std::vector<T>[len]) {}

    CHTbl(std::vector<T> vec, int len) : len_(len), base_(new std::vector<T>[len]) {
        for (auto e : vec)
            insert(e);
    }

    ~CHTbl() {
        delete[] base_;
    }

    bool find(const T& data) const {
        int bucket = hash_code_(data);
        for (auto e : base_[bucket])
            if (data == e)
                return true;
        return false;
    }

    bool insert(const T& data) {
        int bucket = hash_code_(data);
        for (auto e : base_[bucket])
            if (data == e)
                return false;
        base_[bucket].push_back(data);
        return true;
    }

    bool remove(const T& data) {
        int bucket = hash_code_(data);
        auto& vec = base_[bucket];
        auto iter = std::find(vec.begin(), vec.end(), data);
        if (iter != vec.end()) {
            vec.erase(iter);
            return true;
        } else {
            return false;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const CHTbl<T>& tbl) {
        for (int i = 0; i < tbl.len_; i++) {
            for (auto e : tbl.base_[i])
                out << e << ' ';
            out << '\n';
        }
        return out;
    }
};
}  // namespace ds