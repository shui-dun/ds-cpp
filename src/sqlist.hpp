#pragma once
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <ostream>
#include <vector>

namespace ds {
template <class T>
class SqList {
private:
    int len_;

    T* base_;

    int capacity_;

    T kmin_(T* data, int low, int high, int k) {
        if (high >= low) {
            std::swap(data[low], data[(low + high) / 2]);
            int i = low, j = high;
            T pivot = data[i];
            while (i < j) {
                while (i < j && data[j] >= pivot)
                    j--;
                data[i] = data[j];
                while (i < j && data[i] <= pivot)
                    i++;
                data[j] = data[i];
            }
            data[i] = pivot;
            if (i - low == k - 1) {
                return pivot;
            } else if (i - low > k - 1) {
                return kmin_(data, low, i - 1, k);
            } else {
                return kmin_(data, i + 1, high, k - i + low - 1);
            }
        }
    }

    void quick_sort_(int low, int high) {
        if (high > low) {
            int mid = (low + high) / 2;
            if (base_[mid] > base_[low])
                std::swap(base_[mid], base_[low]);
            if (base_[mid] > base_[high])
                std::swap(base_[mid], base_[high]);
            if (base_[low] > base_[high])
                std::swap(base_[low], base_[high]);
            int i = low, j = high;
            T pivot = base_[i];
            while (i < j) {
                while (i < j && base_[j] >= pivot)
                    j--;
                base_[i] = base_[j];
                while (i < j && base_[i] <= pivot)
                    i++;
                base_[j] = base_[i];
            }
            base_[i] = pivot;
            quick_sort_(low, i - 1);
            quick_sort_(i + 1, high);
        }
    }

    void sort_(T* low, T* high) {
        if (high - low <= 64) {
            for (T* i = low + 1; i <= high; i++) {
                T temp = *i;
                T* j = i - 1;
                for (; j >= low; j--) {
                    if (*j <= temp) {
                        break;
                    } else {
                        *(j + 1) = *j;
                    }
                }
                *(j + 1) = temp;
            }
        } else {
            auto pivot = *(low + (high - low) / 2);
            T* i = low - 1, * j = high + 1;
            while (true) {
                while (*(++i) < pivot)
                    ;
                while (*(--j) > pivot)
                    ;
                if (i >= j) break;
                std::swap(*i, *j);
            }
            sort_(low, i - 1);
            sort_(i, high);
        }
    }

    void heap_adjust_(int low, int high) {
        for (int max = 2 * low + 1; max <= high; max = 2 * max + 1) {
            if (max < high && base_[max + 1] > base_[max])
                max++;
            if (base_[low] > base_[max])
                break;
            std::swap(base_[low], base_[max]);
            low = max;
        }
    }

    void merge_sort_(int low, int high) {
        if (low >= high)
            return;
        int mid = (low + high) / 2;
        merge_sort_(low, mid);
        merge_sort_(mid + 1, high);
        int ind = 0, ind1 = 0, ind2 = 0;
        int len = high - low + 1, len1 = mid - low + 1, len2 = high - mid;
        T* temp = new T[len];
        while (ind1 < len1 && ind2 < len2) {
            if (base_[low + ind1] < base_[mid + 1 + ind2])
                temp[ind++] = base_[low + ind1++];
            else
                temp[ind++] = base_[mid + 1 + ind2++];
        }
        while (ind1 < len1)
            temp[ind++] = base_[low + ind1++];
        while (ind2 < len2)
            temp[ind++] = base_[mid + 1 + ind2++];
        memcpy(base_ + low, temp, sizeof(T) * len);
        delete[] temp;
    }

public:
    SqList(T* array, int len) : len_(len), base_(new T[len + 10]), capacity_(len + 10) {
        for (int i = 0; i < len; i++)
            base_[i] = array[i];
    }

    SqList(T* array, int len, int capacity) : len_(len), base_(new T[capacity]), capacity_(capacity) {
        assert(len_ <= capacity);
        for (int i = 0; i < len; i++)
            base_[i] = array[i];
    }

    SqList(int capacity = 20) : len_(capacity), base_(new T[capacity]), capacity_(capacity) {}

    ~SqList() {
        delete[] base_;
    }

    int find(const T& data) const {
        for (int i = 0; i < len_; i++)
            if (base_[i] == data)
                return i;
        return -1;
    }

    int bisearch(const T& data) const {
        int low = 0, high = len_ - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (base_[mid] == data)
                return mid;
            else if (base_[mid] < data)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return -1;
    }

    int bisearch2(const T& data, int low, int high) const {
        if (low <= high) {
            int mid = (low + high) / 2;
            if (base_[mid] == data)
                return mid;
            else if (base_[mid] < data)
                low = mid + 1;
            else
                high = mid - 1;
            return bisearch2(data, low, high);
        }
        return -1;
    }

    int len() const {
        return len_;
    }

    T& operator[](size_t i) {
        return base_[i];
    }

    int capacity() const {
        return capacity_;
    }

    void sort() {
        sort_(base_, base_ + len_ - 1);
    }

    void insert(int pos, const T& data) {
        if (pos < 0 || pos > len_)
            throw std::runtime_error("SqList::insert");
        if (len_ == capacity_) {
            base_ = (T*)realloc(base_, sizeof(T) * capacity_ * 2);
            capacity_ *= 2;
        }
        for (int i = len_; i >= pos; i--)
            base_[i + 1] = base_[i];
        base_[pos] = data;
        len_++;
    }

    void append(const T& data) {
        insert(len_, data);
    }

    T remove(int pos) {
        if (pos < 0 || pos > len_ - 1)
            throw std::runtime_error("remove");
        T data = base_[pos];
        for (int i = pos; i < len_ - 1; i++)
            base_[i] = base_[i + 1];
        len_--;
        return data;
    }

    void insert_sort() {
        for (int i = 1; i < len_; i++) {
            T temp = base_[i];
            int pos = i - 1;
            for (; pos >= 0; pos--) {
                if (base_[pos] < temp)
                    break;
                base_[pos + 1] = base_[pos];
            }
            base_[pos + 1] = temp;
        }
    }

    void bubble_sort() {
        for (int x = 0; x < len_ - 1; x++) {
            bool sorted = true;
            for (int y = 0; y < len_ - x - 1; y++)
                if (base_[y] > base_[y + 1]) {
                    std::swap(base_[y + 1], base_[y]);
                    sorted = false;
                }
            if (sorted)
                return;
        }
    }

    void oddeven_sort() {
        bool sorted;
        int init = 0;
        do {
            sorted = true;
            for (int i = init; i < len_ - 1; i += 2) {
                if (base_[i] > base_[i + 1]) {
                    std::swap(base_[i], base_[i + 1]);
                    sorted = false;
                }
            }
            init = !init;
        } while (!sorted);
    }

    void shell_sort() {
        int t = (int)(log(len_ + 1) / log(2));
        for (int i = 1; i <= t; i++) {
            int gap = (int)pow(2, t - i + 1) - 1;
            for (int x = 0; x < gap; x++) {
                for (int y = gap + x; y < len_; y += gap) {
                    T temp = base_[y];
                    int pos = y - gap;
                    for (; pos >= 0; pos -= gap) {
                        if (base_[pos] < temp)
                            break;
                        base_[pos + gap] = base_[pos];
                    }
                    base_[pos + gap] = temp;
                }
            }
        }
    }

    T median() {
        return kmin(len_ / 2 + 1);
    }

    T kmin(int k) {
        assert(k >= 1 && k <= len_);
        T* data = new T[len_];
        memcpy(data, base_, sizeof(T) * len_);
        T val = kmin_(data, 0, len_ - 1, k);
        delete[] data;
        return val;
    }

    void quick_sort() {
        return quick_sort_(0, len_ - 1);
    }

    void select_sort() {
        for (int i = 0; i < len_ - 1; i++) {
            int min = i;
            for (int x = i + 1; x < len_; x++)
                if (base_[x] < base_[min])
                    min = x;
            std::swap(base_[min], base_[i]);
        }
    }

    void heap_sort() {
        for (int i = (len_ - 2) / 2; i >= 0; i--)
            heap_adjust_(i, len_ - 1);
        for (int i = len_ - 1; i > 0; i--) {
            std::swap(base_[i], base_[0]);
            heap_adjust_(0, i - 1);
        }
    }

    void merge_sort() {
        return merge_sort_(0, len_ - 1);
    }

    void radix_sort() {
        int digit = 1, pow = 1;
        int max = *std::max_element(base_, base_ + len_);
        while (max /= 10) digit++;
        std::vector<T> array[10];
        for (int i = 0; i < digit; i++, pow *= 10) {
            for (int x = 0; x < len_; x++) {
                int pos = (base_[x] / pow) % 10;
                array[pos].push_back(base_[x]);
            }
            for (int x = 0, pos = 0; x < 10; x++) {
                for (auto e : array[x]) {
                    base_[pos++] = e;
                }
                array[x].clear();
            }
        }
    }

    void count_sort() {
        auto iter = std::minmax_element(base_, base_ + len_);
        int min = *iter.first, max = *iter.second;
        int* array = new int[max - min + 1];
        memset(array, 0, sizeof(int) * (max - min + 1));
        for (int i = 0; i < len_; i++)
            array[base_[i] - min]++;
        int pos = 0;
        for (int e = 0; e <= max - min; e++)
            for (int x = 0; x < array[e]; x++)
                base_[pos++] = e + min;
        delete[] array;
    }

    void bucket_sort() {
        auto iter = std::minmax_element(base_, base_ + len_);
        int min = *iter.first, max = *iter.second;
        int k = 10;
        int num = (max - min) / k + 1;
        std::vector<std::vector<T> > vec(num);
        for (int i = 0; i < len_; i++) {
            vec[(base_[i] - min) / k].push_back(base_[i]);
        }
        int ind = 0;
        for (auto& v : vec) {
            for (int i = 1; i < (int)v.size(); i++) {
                T temp = v[i];
                int pos = i - 1;
                for (; pos >= 0; pos--) {
                    if (v[pos] < temp)
                        break;
                    v[pos + 1] = v[pos];
                }
                v[pos + 1] = temp;
            }
            for (auto e : v)
                base_[ind++] = e;
        }
    }

    auto begin() {
        return base_;
    }

    auto end() {
        return base_ + len_;
    }

    bool operator==(const SqList<T>& list) {
        if (len_ != list.len_)
            return false;
        for (int i = 0; i < len_; i++)
            if (base_[i] != list.base_[i])
                return false;
        return true;
    }
};
}  // namespace ds
