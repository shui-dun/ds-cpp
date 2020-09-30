#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>

namespace ds {
template <class T>
class ComBiTree {
private:
    T* base_;

    int len_;

    static int parent_(int ind) {
        return (ind - 1) / 2;
    }

    static int lchild_(int ind) {
        return 2 * ind + 1;
    }

    static int rchild_(int ind) {
        return 2 * ind + 2;
    }

public:
    ComBiTree() {}

    ComBiTree(const std::vector<T>& vec) : len_(vec.size()), base_(new T[vec.size()]) {
        for (int i = 0; i < len_; i++)
            base_[i] = vec[i];
    }

    ~ComBiTree() {
        delete[] base_;
    }

    const T& get(int level, int order) const {
        if (level < 1 || order < 1 || order >(int)pow(2, level - 1))
            throw std::runtime_error("ComBiTree::get");
        return base_[(int)pow(2, level - 1) + order - 2];
    }

    void pre_traverse(int pos = 0, std::ostream& out = std::cout) const {
        if (pos >= len_) return;
        out << base_[pos] << ' ';
        pre_traverse(lchild_(pos), out);
        pre_traverse(rchild_(pos), out);
    }

    void in_traverse(int pos = 0, std::ostream& out = std::cout) const {
        if (pos >= len_) return;
        in_traverse(lchild_(pos), out);
        out << base_[pos] << ' ';
        in_traverse(rchild_(pos), out);
    }

    void post_traverse(int pos = 0, std::ostream& out = std::cout) const {
        if (pos >= len_) return;
        post_traverse(lchild_(pos), out);
        post_traverse(rchild_(pos), out);
        out << base_[pos] << ' ';
    }

    void dbl_traverse(int pos = 0, std::ostream& out = std::cout) const {
        if (pos >= len_) return;
        out << base_[pos] << ' ';
        dbl_traverse(lchild_(pos), out);
        out << base_[pos] << ' ';
        dbl_traverse(rchild_(pos), out);
    }

    void level_traverse(std::ostream& out = std::cout) const {
        for (int i = 0; i < len_; i++)
            out << base_[i] << ' ';
        out << '\n';
    }

    int depth() const {
        return (int)(log(len_) / log(2)) + 1;
    }

    int n_node() const {
        return len_;
    }

    int n_leaf() const {
        return (len_ + 1) / 2;
    }
};
}  // namespace ds