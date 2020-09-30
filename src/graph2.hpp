#pragma once
#include <cassert>
#include <iostream>
#include <vector>
#include "queue.hpp"
using std::vector;

namespace ds {
struct ArcNode {
    int adjvex;
    double weight;
    ArcNode* next;
    ArcNode(int adjvex, double weight, ArcNode* next = nullptr)
        : adjvex(adjvex), weight(weight), next(next) {
    }
};

template <class T = char>
struct AdjList {
    T data;
    ArcNode* first;
};

template <class T = char>
class Graph2 {
private:
    int n_vex_;

    int n_arc_;

    AdjList<T>* base_;

    void dfs_(int pos, bool* vis, std::ostream& out) const {
        vis[pos] = true;
        out << pos << ':' << base_[pos].data << '\t';
        for (auto node = base_[pos].first; node; node = node->next) {
            if (!vis[node->adjvex]) dfs_(node->adjvex, vis, out);
        }
    }

public:
    Graph2(vector<T> vex)
        : n_vex_((int)vex.size()), n_arc_(0), base_(new AdjList<T>[vex.size()]) {
        for (int i = 0; i < n_vex_; i++) {
            base_[i].data = vex[i];
            base_[i].first = nullptr;
        }
    }

    ~Graph2() {
        for (int i = 0; i < n_vex_; i++) {
            auto node = base_[i].first;
            while (node) {
                auto temp = node->next;
                delete node;
                node = temp;
            }
        }
        delete base_;
    }

    void dfs(std::ostream& out = std::cout) const {
        bool* vis = new bool[n_vex_] {false};
        for (int i = 0; i < n_vex_; i++)
            if (!vis[i]) {
                dfs_(i, vis, out);
                std::cout << '\n';
            }
        delete[] vis;
    }

    void bfs(std::ostream& out = std::cout) const {
        bool* vis = new bool[n_vex_] {false};
        Queue<int> queue;
        for (int i = 0; i < n_vex_; i++) {
            if (!vis[i]) {
                queue.offer(i);
                while (!queue.empty()) {
                    int j = queue.poll();
                    if (!vis[j]) out << j << ':' << base_[j].data << '\t';
                    vis[j] = true;
                    for (auto node = base_[j].first; node; node = node->next) {
                        if (!vis[node->adjvex]) {
                            queue.offer(node->adjvex);
                        }
                    }
                }
                out << '\n';
            }
        }
        delete[] vis;
    }

    double weight(int start, int end) const {
        assert(start >= 0 && start < n_vex_ && end >= 0 && end < n_vex_);
        for (ArcNode* node = base_[start].first; node; node = node->next) {
            if (node->adjvex == end) return node->weight;
        }
        throw std::runtime_error("Graph2::weight");
    }

    void update(int start, int end, double val) {
        assert(start >= 0 && start < n_vex_ && end >= 0 && end < n_vex_);
        for (ArcNode* node = base_[start].first; node; node = node->next) {
            if (node->adjvex == end) {
                node->weight = val;
                return;
            }
            if (!node->next) {
                node->next = new ArcNode(end, val);
                n_arc_++;
                return;
            }
        }
        base_[start].first = new ArcNode(end, val);
        n_arc_++;
    }

    bool remove(int start, int end) {
        assert(start >= 0 && start < n_vex_ && end >= 0 && end < n_vex_);
        ArcNode* node = base_[start].first;
        if (!node) return false;
        if (node->adjvex == end) {
            base_[start].first = node->next;
            delete node;
            n_arc_--;
            return true;
        }
        for (; node->next; node = node->next) {
            if (node->next->adjvex == end) {
                auto temp = node->next;
                node->next = temp->next;
                delete temp;
                n_arc_--;
                return true;
            }
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& out, const Graph2& graph) {
        for (int i = 0; i < graph.n_vex_; i++) {
            out << graph.base_[i].data << '\t';
            for (auto node = graph.base_[i].first; node; node = node->next) {
                out << node->adjvex << ':' << node->weight << '\t';
            }
            out << '\n';
        }
        return out;
    }

    auto n_vex() const { return n_vex_; }

    auto n_arc() const { return n_arc_; }
};
};  // namespace ds