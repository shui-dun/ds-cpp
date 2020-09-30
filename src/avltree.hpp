#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include "queue.hpp"

namespace ds {
template <class T>
class AVLNode {
public:
    int hei;

    T data;

    AVLNode<T>* lchild;

    AVLNode<T>* rchild;

    AVLNode(const T& data) : hei(1), data(data), lchild(nullptr), rchild(nullptr) {}
};

template <class T>
class AVLTree {
private:
    AVLNode<T>* root_;

    int height_(AVLNode<T>* node) {
        if (!node)
            return 0;
        return node->hei;
    }

    int height_factor_(AVLNode<T>* node) {
        if (!node)
            return 0;
        return height_(node->lchild) - height_(node->rchild);
    }

    void left_rotate_(AVLNode<T>*& node) {
        auto root = node->rchild;
        node->rchild = root->lchild;
        root->lchild = node;
        node->hei = std::max(height_(node->lchild), height_(node->rchild)) + 1;
        root->hei = std::max(height_(root->lchild), height_(root->rchild)) + 1;
        node = root;
    }

    void right_rotate_(AVLNode<T>*& node) {
        auto root = node->lchild;
        node->lchild = root->rchild;
        root->rchild = node;
        node->hei = std::max(height_(node->lchild), height_(node->lchild)) + 1;
        root->hei = std::max(height_(root->lchild), height_(root->rchild)) + 1;
        node = root;
    }

    void balance_(AVLNode<T>*& node) {
        int factor = height_factor_(node);
        if (factor > 1 && height_factor_(node->lchild) > 0) {
            right_rotate_(node);
        } else if (factor > 1 && height_factor_(node->lchild) <= 0) {
            left_rotate_(node->lchild);
            right_rotate_(node);
        } else if (factor < -1 && height_factor_(node->rchild) <= 0) {
            left_rotate_(node);
        } else if (factor < -1 && height_factor_(node->rchild) > 0) {
            right_rotate_(node->rchild);
            left_rotate_(node);
        }
    }

    bool insert_(AVLNode<T>*& node, const T& data) {
        if (!node) {
            node = new AVLNode<T>(data);
        } else if (node->data == data) {
            return false;
        } else if (node->data < data) {
            insert_(node->rchild, data);
        } else {
            insert_(node->lchild, data);
        }
        balance_(node);
        node->hei = std::max(height_(node->lchild), height_(node->rchild)) + 1;
        return true;
    }

    void destroy_(AVLNode<T>* root) {
        if (!root) return;
        destroy_(root->lchild);
        destroy_(root->rchild);
        delete root;
    }

    void pre_traverse_(AVLNode<T>* node, std::ostream& out) const {
        if (!node) return;
        out << node->data << ' ';
        pre_traverse_(node->lchild, out);
        pre_traverse_(node->rchild, out);
    }

    void in_traverse_(AVLNode<T>* node, std::ostream& out) const {
        if (!node) return;
        in_traverse_(node->lchild, out);
        out << node->data << ' ';
        in_traverse_(node->rchild, out);
    }

    void post_traverse_(AVLNode<T>* node, std::ostream& out) const {
        if (!node) return;
        post_traverse_(node->lchild, out);
        post_traverse_(node->rchild, out);
        out << node->data << ' ';
    }

    AVLNode<T>* find_(AVLNode<T>* node, const T& data) {
        if (!node)
            return nullptr;
        if (node->data == data)
            return node;
        if (node->data > data)
            return find_(node->lchild, data);
        if (node->data < data)
            return find_(node->rchild, data);
    }

public:
    AVLTree() : root_(nullptr) {}

    AVLTree(std::vector<T> vec) {
        for (auto e : vec)
            insert(e);
    }

    ~AVLTree() {
        destroy_(root_);
    }

    void pre_traverse(std::ostream& out = std::cout) const {
        pre_traverse_(root_, out);
    }

    void in_traverse(std::ostream& out = std::cout) const {
        in_traverse_(root_, out);
    }

    void post_traverse(std::ostream& out = std::cout) const {
        post_traverse_(root_, out);
    }

    void level_traverse(std::ostream& out = std::cout) const {
        Queue<AVLNode<T>*> queue;
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

    AVLNode<T>* find(const T& data) {
        return find_(root_, data);
    }

    bool insert(const T& data) {
        return insert_(root_, data);
    }
};
}  // namespace ds
