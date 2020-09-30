#pragma once
#include <cassert>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include "queue.hpp"
#include "stack.hpp"
using std::vector;

namespace ds {
class Graph {
private:
    int n_arc_ = 0;

    void dfs_(int pos, bool* visit, std::ostream& out) const {
        visit[pos] = true;
        out << pos << ' ';
        for (int i = 0; i < (int)mat_.size(); i++)
            if (mat_[pos][i] != INF && !visit[i])
                dfs_(i, visit, out);
    }

public:
    vector<vector<double> > mat_;

    constexpr static double INF = 1e10;

    Graph(const vector<vector<double> >& mat) : mat_(mat) {
        int temp = 0;
        for (auto v : mat)
            temp += std::count(v.begin(), v.end(), INF);
        n_arc_ = (int)(mat_.size() * mat_.size()) - temp;
    }

    bool aov_topological_sort(std::ostream& out = std::cout) const {
        int* in = new int[mat_.size()]{ 0 };
        bool* vis = new bool[mat_.size()]{ false };
        Stack<int> stack;
        for (size_t i = 0; i < mat_.size(); i++) {
            in[i] = in_degree(i);
            if (in[i] == 0) {
                stack.push(i);
                vis[i] = true;
            }
        }
        size_t count = 0;
        while (!stack.empty()) {
            int pos = stack.pop();
            out << pos << ' ';
            count++;
            for (size_t i = 0; i < mat_.size(); i++)
                if (mat_[pos][i] != INF && !vis[i])
                    if (--in[i] == 0)
                        stack.push(i);
        }
        delete[] in;
        delete[] vis;
        out << '\n';
        if (count < mat_.size()) {
            return false;
        } else {
            return true;
        }
    }

    void dfs(std::ostream& out = std::cout) const {
        bool* visit = new bool[mat_.size()]{ false };
        for (int i = 0; i < (int)mat_.size(); i++)
            if (!visit[i]) {
                dfs_(i, visit, out);
                out << '\n';
            }
        delete[] visit;
    }

    void set_arc(size_t i, size_t j, double val) {
        assert(i >= 0 && i < mat_.size() && j >= 0 && j < mat_.size());
        double pre = mat_[i][j];
        mat_[i][j] = val;
        if (pre == INF && val != INF) {
            n_arc_++;
        } else if (pre != INF && val == INF) {
            n_arc_--;
        }
    }

    void rem_arc(size_t i, size_t j) {
        set_arc(i, j, INF);
    }

    double get_arc(size_t i, size_t j) const {
        assert(i >= 0 && i < mat_.size() && j >= 0 && j < mat_.size());
        return mat_[i][j];
    }

    void ins_vex(int num) {
        size_t size = mat_.size();
        mat_.resize(size + num);
        for (size_t i = 0; i < size; i++) {
            mat_[i].resize(size + num);
            for (size_t j = size; j < size + num; j++) {
                mat_[i][j] = INF;
            }
        }
        for (size_t i = size; i < size + num; i++) {
            mat_[i].resize(size + num);
            for (size_t j = 0; j < size + num; j++) {
                mat_[i][j] = INF;
            }
        }
    }

    int in_degree(size_t pos) const {
        assert(pos >= 0 && pos < mat_.size());
        int count = 0;
        for (size_t j = 0; j < mat_.size(); j++) {
            if (mat_[j][pos] != INF)
                count++;
        }
        return count;
    }

    int out_degree(size_t pos) const {
        assert(pos >= 0 && pos < mat_.size());
        int count = 0;
        for (size_t j = 0; j < mat_.size(); j++) {
            if (mat_[pos][j] != INF)
                count++;
        }
        return count;
    }

    void bfs(std::ostream& out = std::cout) const {
        bool* vis = new bool[mat_.size()]{ false };
        Queue<int> queue;
        for (int i = 0; i < (int)mat_.size(); i++) {
            if (!vis[i]) {
                queue.offer(i);
                while (!queue.empty()) {
                    int j = queue.poll();
                    if (!vis[j])
                        out << j << ' ';
                    vis[j] = true;
                    for (int x = 0; x < (int)mat_.size(); x++) {
                        if (mat_[j][x] != INF && !vis[x]) {
                            queue.offer(x);
                        }
                    }
                }
                out << '\n';
            }
        }
        delete[] vis;
    }

    void min_span_tree(int start, std::ostream& out = std::cout) const {
        struct Edge {
            int i, j;
            double weight;
        };
        struct cmp {
            bool operator()(Edge e1, Edge e2) {
                return e1.weight > e2.weight;
            }
        };
        std::priority_queue<Edge, vector<Edge>, cmp> queue;
        std::set<int> unvis;
        for (int i = 0; i < (int)mat_.size(); i++) {
            if (i != start) {
                queue.push(Edge{ start, i, mat_[start][i] });
                unvis.insert(i);
            }
        }
        for (int i = 1; i < (int)mat_.size(); i++) {
            int mini, minj;
            while (true) {
                mini = queue.top().i;
                minj = queue.top().j;
                queue.pop();
                if (unvis.find(minj) != unvis.end())
                    break;
            }
            if (mat_[mini][minj] == INF) return;
            unvis.erase(minj);
            out << '(' << mini << ',' << minj << ") ";
            for (auto e : unvis) {
                if (unvis.find(e) != unvis.end())
                    queue.push(Edge{ minj, e, mat_[minj][e] });
            }
        }
        out << '\n';
    }

    friend std::ostream& operator<<(std::ostream& out, const Graph& graph) {
        for (auto v : graph.mat_) {
            for (auto e : v) {
                if (e != INF) {
                    std::cout << e << '\t';
                } else {
                    std::cout << "INF\t";
                }
            }
            std::cout << '\n';
        }
        return out;
    }

    auto n_arc() const {
        return n_arc_;
    }
};
};  // namespace ds
