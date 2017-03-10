//
// Created by Shane on 2017/3/8.
//

#ifndef NO1_NODE_H
#define NO1_NODE_H
template<class T>
class node {
 public:
  node() : next_node_(nullptr) {}
  node(T init) : node(init, nullptr) {}
  node(T init, node<T> *next) : data_(init), next_node_(next) {};
  inline T data() const { return data_; }
  void set_data(T data) { data_ = data; }
  inline node *next_node() const { return next_node_; }
  void set_next_node(node *next_node) { next_node_ = next_node; }
  bool operator<(node<T> &a) { return data() < a.data(); }
  virtual ~node() {}
 private:
  T data_;
  node<T> *next_node_;
};

#endif //NO1_NODE_H
