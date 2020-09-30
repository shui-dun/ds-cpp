#pragma once
#include <iostream>
#include <stdexcept>

namespace ds {
template <class T>
class QNode {
public:
    QNode<T>* next;

    T data;

    QNode() : next(nullptr), data() {}

    QNode(const T& data) : next(nullptr), data(data) {}
};

template <class T>
class Queue {
private:
    QNode<T>* front_;

    QNode<T>* rear_;

public:
    Queue() : front_(new QNode<T>), rear_(front_) {
        front_->next = nullptr;
    }

    Queue(const T* array, int len) : front_(new QNode<T>) {
        QNode<T>* pre = front_;
        for (int i = 0; i < len; i++) {
            auto node = new QNode<T>(array[i]);
            pre->next = node;
            pre = node;
        }
        rear_ = pre;
    }

    ~Queue() {
        auto node = front_;
        auto pre = node;
        while (node) {
            node = node->next;
            delete pre;
            pre = node;
        }
    }

    void offer(const T& data) {
        auto node = new QNode<T>(data);
        rear_->next = node;
        rear_ = node;
    }

    T poll() {
        if (front_ == rear_)
            throw std::underflow_error("queue::poll");
        QNode<T>* node = front_->next;
        T data = node->data;
        front_->next = node->next;
        if (front_->next == nullptr)
            rear_ = front_;
        delete node;
        return data;
    }

    T& peek() const {
        if (front_ == rear_)
            throw std::underflow_error("queue::data");
        return front_->next->data;
    }

    int len() const {
        int len = 0;
        QNode<T>* node = front_->next;
        while (node) {
            len++;
            node = node->next;
        }
        return len;
    }

    bool empty() const {
        return len() == 0;
    }
};
}  // namespace ds