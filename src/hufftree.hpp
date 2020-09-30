#pragma once
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

namespace ds {
struct HuffNode {
    char value;

    double weight;

    int parent, lchild, rchild;

    HuffNode(char value = 0, double weight = 0.0)
        : value(value), weight(weight), parent(-1), lchild(-1), rchild(-1) {
    }
};

class HuffTree {
private:
    HuffNode* base_;

    int len_;

public:
    HuffTree(const double* weight, const char* s, int n) : base_(new HuffNode[2 * n - 1]), len_(n) {
        struct cmp {
            bool operator()(HuffNode* a, HuffNode* b) { return a->weight > b->weight; }
        };
        std::priority_queue<HuffNode*, std::vector<HuffNode*>, cmp> queue;
        for (int i = 0; i < n; i++) {
            base_[i].weight = weight[i];
            base_[i].value = s[i];
            queue.push(base_ + i);
        }
        for (int i = 0; i < n - 1; i++) {
            int min1 = queue.top() - base_;
            queue.pop();
            int min2 = queue.top() - base_;
            queue.pop();
            base_[n + i].weight = base_[min1].weight + base_[min2].weight;
            base_[n + i].lchild = min1;
            base_[n + i].rchild = min2;
            base_[min1].parent = base_[min2].parent = n + i;
            queue.push(base_ + n + i);
        }
    }

    ~HuffTree() {
        delete[] base_;
    }

    std::vector<std::string> encode() const {
        std::vector<std::string> vec(len_);
        for (int i = 0; i < len_; i++) {
            int pos = i, pre = i;
            while (pos != 2 * len_ - 2) {
                pos = base_[pos].parent;
                if (base_[pos].lchild == pre) {
                    vec[i].insert(0, "0");
                } else {
                    vec[i].insert(0, "1");
                }
                pre = pos;
            }
        }
        return vec;
    }

    std::string decode(const std::string& origin) const {
        std::string str;
        int pos = 2 * len_ - 2;
        for (auto value : origin) {
            if (value == '0') {
                pos = base_[pos].lchild;
            } else if (value == '1') {
                pos = base_[pos].rchild;
            } else {
                throw std::runtime_error("HuffTree::decode");
            }
            if (base_[pos].lchild == -1 && base_[pos].rchild == -1) {
                str.push_back(base_[pos].value);
                pos = 2 * len_ - 2;
            }
        }
        return str;
    }
};
}  // namespace ds