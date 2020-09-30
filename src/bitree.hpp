#pragma once
#include <iostream>
#include <algorithm>
#include "queue.hpp"
#include "stack.hpp"

namespace ds {
template <class T>
struct TNode {
    T data;

    TNode* lchild;

    TNode* rchild;

    TNode(const T& data, TNode* l = nullptr, TNode* r = nullptr)
        : data(data), lchild(l), rchild(r) {
    }
};

template <class T>
class BiTree {
protected:
    TNode<T>* root_;

    TNode<T>* copy_(TNode<T>* origin) {
        if (!origin)
            return nullptr;
        return new TNode<T>(origin->data, copy_(origin->lchild), copy_(origin->rchild));
    }

    TNode<T>* from_post_in_(T* post, T* in, int len) {
        if (len < 1) return nullptr;
        auto node = new TNode<T>(post[len - 1]);
        int ind = std::find(in, in + len, post[len - 1]) - in;
        node->lchild = from_post_in_(post, in, ind);
        node->rchild = from_post_in_(post + ind, in + ind + 1, len - ind - 1);
        return node;
    }

    TNode<T>* from_pre_(T* pre, int& pos, const T& nul) {
        if (pre[++pos] == nul) {
            return nullptr;
        } else {
            auto node = new TNode<T>(pre[pos]);
            node->lchild = from_pre_(pre, pos, nul);
            node->rchild = from_pre_(pre, pos, nul);
            return node;
        }
    }

    void destroy_(TNode<T>* root) {
        if (!root) return;
        destroy_(root->lchild);
        destroy_(root->rchild);
        delete root;
    }

    void post_traverse_(TNode<T>* node, std::ostream& out) const {
        if (!node) return;
        post_traverse_(node->lchild, out);
        post_traverse_(node->rchild, out);
        out << node->data << ' ';
    }

    void dbl_traverse_(TNode<T>* node, std::ostream& out) const {
        if (!node) return;
        out << node->data << ' ';
        dbl_traverse_(node->lchild, out);
        out << node->data << ' ';
        dbl_traverse_(node->rchild, out);
    }

    int depth_(TNode<T>* node) const {
        if (!node) return 0;
        int len1 = depth_(node->lchild);
        int len2 = depth_(node->rchild);
        return 1 + (len1 > len2 ? len1 : len2);
    }

    int n_node_(TNode<T>* node) const {
        if (!node) return 0;
        int count1 = n_node_(node->lchild);
        int count2 = n_node_(node->rchild);
        return 1 + count1 + count2;
    }

    int n_leaf_(TNode<T>* node) const {
        if (!node->lchild && !node->rchild)
            return 1;
        int count1 = n_leaf_(node->lchild);
        int count2 = n_leaf_(node->rchild);
        return count1 + count2;
    }

public:
    BiTree() : root_(nullptr) {}

    BiTree(const BiTree& tree) : root_(copy_(tree.root_)) {}

    BiTree(BiTree&& tree) {
        root_ = tree.root_;
        tree.root_ = nullptr;
    }

    BiTree(T* post, T* in, int len) {
        root_ = from_post_in_(post, in, len);
    }

    BiTree(T* pre, const T& nul) {
        int pos = -1;
        root_ = from_pre_(pre, pos, nul);
    }

    ~BiTree() {
        destroy_(root_);
    }

    void post_traverse(std::ostream& out = std::cout) const {
        post_traverse_(root_, out);
    }

    void pre_traverse(std::ostream& out = std::cout) const {
        Stack<TNode<T>*> stack;
        auto node = root_;
        while (node || !stack.empty()) {
            if (node) {
                stack.push(node);
                out << node->data << ' ';
                node = node->lchild;
            } else {
                node = stack.pop();
                node = node->rchild;
            }
        }
        out << '\n';
    }

    void in_traverse(std::ostream& out = std::cout) const {
        Stack<TNode<T>*> stack;
        auto node = root_;
        while (node || !stack.empty()) {
            if (node) {
                stack.push(node);
                node = node->lchild;
            } else {
                node = stack.pop();
                out << node->data << ' ';
                node = node->rchild;
            }
        }
        out << '\n';
    }

    void level_traverse(std::ostream& out = std::cout) const {
        Queue<TNode<T>*> queue;
        auto node = root_;
        queue.offer(node);
        while (!queue.empty()) {
            node = queue.poll();
            out << node->data << ' ';
            if (node->lchild)
                queue.offer(node->lchild);
            if (node->rchild)
                queue.offer(node->rchild);
        }
        out << '\n';
    }

    void dbl_traverse(std::ostream& out = std::cout) const {
        dbl_traverse_(root_, out);
    }

    int depth() const {
        return depth_(root_);
    }

    int n_node() const {
        return n_node_(root_);
    }

    int n_leaf() const {
        return n_leaf_(root_);
    }

    bool is_sorted() const {
        Stack<TNode<T>*> stack;
        auto node = root_;
        while (node->lchild) {
            stack.push(node);
            node = node->lchild;
        }
        T pre = node->data, cur;
        while (!stack.empty()) {
            if (node) {
                stack.push(node);
                node = node->lchild;
            } else {
                node = stack.pop();
                cur = node->data;
                if (cur < pre)
                    return false;
                pre = cur;
                node = node->rchild;
            }
        }
        return true;
    }

    BiTree& operator=(const BiTree& tree) {
        if (root_)
            destroy_(root_);
        root_ = copy_(tree.root_);
        return *this;
    }

    BiTree& operator=(BiTree&& tree) {
        if (root_)
            destroy_(root_);
        root_ = tree.root_;
        tree.root_ = nullptr;
        return *this;
    }
};
}  // namespace ds
