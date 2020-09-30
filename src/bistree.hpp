#pragma once
#include <vector>
#include "bitree.hpp"

namespace ds {
template <class T>
class BiSTree : public BiTree<T> {
private:
    TNode<T>* find_(TNode<T>* node, const T& data) const {
        if (!node)
            return nullptr;
        if (node->data == data)
            return node;
        if (node->data > data)
            return find_(node->lchild, data);
        if (node->data < data)
            return find_(node->rchild, data);
    }

    void print_bigger_(TNode<T>* node, const T& data, std::ostream& out) const {
        if (!node) return;
        print_bigger_(node->rchild, data, out);
        if (node->data >= data)
            out << node->data << ' ';
        else
            return;
        print_bigger_(node->lchild, data, out);
    }

    virtual bool remove_(TNode<T>*& node, const T& data) {
        if (!node) return false;
        if (node->data > data) {
            return remove_(node->lchild, data);
        } else if (node->data < data) {
            return remove_(node->rchild, data);
        } else {
            if (!node->rchild) {
                auto temp = node;
                node = node->lchild;
                delete temp;
            } else if (!node->lchild) {
                auto temp = node;
                node = node->rchild;
                delete temp;
            } else {
                auto pre = node;
                auto cur = node->lchild;
                while (cur->rchild) {
                    pre = cur;
                    cur = cur->rchild;
                }
                node->data = cur->data;
                if (pre == node)
                    pre->lchild = cur->lchild;
                else
                    pre->rchild = cur->lchild;
                delete cur;
            }
            return true;
        }
    }

public:
    BiSTree() {}

    BiSTree(T* post, T* in, int len) : BiTree<T>(post, in, len) {}

    BiSTree(T* pre, const T& nul) : BiTree<T>(pre, nul) {}

    BiSTree(std::vector<T> vec) {
        for (auto e : vec)
            insert(e);
    }

    virtual bool insert(const T& data) {
        TNode<T>* cur = this->root;
        TNode<T>* pre = nullptr;
        while (cur && cur->data != data) {
            pre = cur;
            if (cur->data > data)
                cur = cur->lchild;
            else
                cur = cur->rchild;
        }
        if (cur) return false;
        auto ins = new TNode<T>(data);
        if (!pre) {
            this->root = ins;
        } else if (pre->data > data) {
            pre->lchild = ins;
        } else {
            pre->rchild = ins;
        }
        return true;
    }

    virtual bool remove(const T& data) {
        return remove_(this->root, data);
    }

    TNode<T>* find(const T& data) const {
        return find_(this->root, data);
    }

    void print_bigger(const T& data, std::ostream& out = std::cout) const {
        print_bigger_(this->root, data, out);
    }
};
}  // namespace ds