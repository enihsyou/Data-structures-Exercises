//
// Created by Shane on 2017/3/8.
//

#ifndef NO1_LINKED_LIST_H
#define NO1_LINKED_LIST_H
#include "node.h"
#include <iostream>


template<class T>
class LinkedList {
public:
    LinkedList() : size_(0),
                   start_(nullptr) { }

    virtual ~LinkedList();
    void insert(const T data);
    void insert(const T data, const int where);
    void remove(const int where);
    int where(const T key) const;
    void print() const;

    bool emptyQ() const { return size_ == 0; }

    int size() const { return size_; }

    Node<T> *start() const { return start_; }

    void set_start(Node<T> *start) { start_ = start; }

    Node<T> *operator[](const int index);
    void insert_sort();
    void select_sort();
private:
    void print_content() const;

    int size_;
    Node<T> *start_;
};

/**
 * \brief 在第i个位置插入数据，从零开始计数，递增排序
 *  |o|o|o|o|
 *  ^ ^ ^ ^ ^
 *  0 1 2 3 4
 * \param data 要插入的数据
 * \return 插入的位置
 */
template<class T>
void LinkedList<T>::insert(const T data) {
    Node<T> *ptr = start_;
    while (ptr) {
        if (!ptr->next_node()) break;
        ptr = ptr->next_node();
    }
    Node<T> *new_node = new Node<T>(data, nullptr);
    if (ptr) new_node->set_next_node(ptr->next_node());
    if (!start_) start_ = new_node;
    else ptr->set_next_node(new_node);

    size_++;
}

template<class T>
void LinkedList<T>::insert(const T data, const int where) {
    if (where >= size_ || where < 0) return;
    Node<T> *new_node = new Node<T>(data, nullptr);
    if (where == 0) {
        new_node->set_next_node(start_);
        start_ = new_node;
    } else {
        int count = 1;
        Node<T> *ptr = start_;
        while (count < where) {
            ptr = ptr->next_node();
            count++;
        }
        new_node->set_next_node(ptr->next_node());
        ptr->set_next_node(new_node);
    }

    size_++;
}

/**
 * \brief 移除第i个元素
 *  |o|o|o|o|
 *   ^ ^ ^ ^
 *   0 1 2 3
 * \return
 */
template<class T>
void LinkedList<T>::remove(const int where) {
    if (where >= size_ || where < 0) return;
    if (where == 0) {
        if (size_ > 0) start_ = start_->next_node();
        return;
    }
    Node<T> *ptr = start_;
    int count = 1;
    while (count < where) { // 停在前一个节点
        ptr = ptr->next_node();
        count++;
    }

    Node<T> *old_node = ptr->next_node();
    ptr->set_next_node(ptr->next_node()->next_node());
    delete old_node;

    size_--;
}

/**
 * \brief 寻找元素的位置，-1表示未找到
 * \param key 寻找的元素
 * \return 元素的位置
 */
template<class T>
int LinkedList<T>::where(const T key) const {
    Node<T> *processing = start_;
    auto count = 0;
    while (processing && processing->data() != key) {
        processing = processing->next_node();
        count++;
    }
    if (count == size_) return -1;
    return count;
}

template<class T>
void LinkedList<T>::print() const {
    auto next = start_;
    std::cout << "List size: " << size_ << std::endl;
    while (next) {
        std::cout << next->data() << " ";
        next = next->next_node();
    }
    std::cout << std::endl;
}

template<class T>
void LinkedList<T>::print_content() const {
    auto next = start_;
    while (next) {
        std::cout << next->data() << " ";
        next = next->next_node();
    }
    std::cout << std::endl;
}

template<class T>
LinkedList<T>::~LinkedList() {
    while (start_) {
        auto old_node = start_;
        delete start_;
        start_ = old_node;
    }
}

template<class T>
Node<T> *LinkedList<T>::operator[](const int index) {
    if (index >= size_) throw std::invalid_argument("index error");
    Node<T> *ptr = start_;
    int count = 0;
    while (count < index) { // 停在前一个节点
        ptr = ptr->next_node();
        count++;
    }
    return ptr;
}

template<class T>
void LinkedList<T>::insert_sort() {
    for (int i = 1; i < size_; ++i) {
        for (int j = 0; j < i; ++j) {
            if (*(operator[](i)) < *(operator[](j))) {
                auto t = *(operator[](i));
                remove(i);
                insert(t.data(), j);
                print_content();
            }
        }
    }
}

template<class T>
void LinkedList<T>::select_sort() {
    for (int i = 0; i < size_; ++i) {
        auto min = i;
        for (int j = i; j < size_; ++j) {
            if (*(operator[](j)) < *(operator[](min))) {
                min = j;
            }
        }
        if (min == i) continue;
        auto t = *(operator[](min));
        remove(min);
        insert(t.data(), i);
        print_content();
    }
}

#endif //NO1_LINKED_LIST_H
