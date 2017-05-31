//
// Created by Shane on 2017/3/8.
//

#ifndef NO1_NODE_H
#define NO1_NODE_H

template<class T>
class Node {
public:
    Node() : next_node_(nullptr) { }

    Node(T init) : Node(init, nullptr) { }

    Node(T init, Node<T> *next) : data_(init),
                                  next_node_(next) { };

    T data() const { return data_; }

    void set_data(T data) { data_ = data; }

    Node *next_node() const { return next_node_; }

    void set_next_node(Node *next_node) { next_node_ = next_node; }

    bool operator<(Node<T> &a) { return data_ < a.data_; }

    bool operator==(Node<T> &a) { return data_ == a.data_; }

    bool operator>(Node<T> &a) { return data_ > a.data_; }

    virtual ~Node() { }

private:
    T data_;
    Node<T> *next_node_;
};

#endif //NO1_NODE_H
