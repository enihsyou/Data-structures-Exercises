#include "BinaryTree.h"
#include <stdexcept>
#include <ostream>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <stack>
#include <queue>


TreeNode::TreeNode(const int key, const int value, const unsigned size) : key_{key},
                                                                          value_{value},
                                                                          size_{size} { }

void TreeNode::swapChildren() {
    if (left_) left_->swapChildren();
    if (right_) right_->swapChildren();
    left_.swap(right_);
}

void TreeNode::preOrderRecursiveTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    do_on_node(*this);
    if (left_) left_->preOrderRecursiveTraverse(do_on_node);
    if (right_) right_->preOrderRecursiveTraverse(do_on_node);
}

void TreeNode::inOrderRecursiveTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    if (left_) left_->inOrderRecursiveTraverse(do_on_node);
    do_on_node(*this);
    if (right_) right_->inOrderRecursiveTraverse(do_on_node);
}

void TreeNode::postOrderRecursiveTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    if (left_) left_->postOrderRecursiveTraverse(do_on_node);
    if (right_) right_->postOrderRecursiveTraverse(do_on_node);
    do_on_node(*this);
}

void TreeNode::preOrderIterativeTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    std::stack<const TreeNode *> stack{ };
    stack.push(this);

    while (!stack.empty()) {
        const auto *temp = stack.top();
        stack.pop();
        do_on_node(*temp);
        if (temp->right_) stack.push(temp->right_.get());
        if (temp->left_) stack.push(temp->left_.get());
    }
}

void TreeNode::inOrderIterativeTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    std::stack<const TreeNode *> stack{ };
    const auto *node = this;

    do {
        if (node) {
            stack.push(node);
            node = node->left_.get();
        } else {
            node = stack.top();
            stack.pop();
            do_on_node(*node);
            node = node->right_.get();
        }
    } while (!stack.empty() || node);
}

void TreeNode::postOrderIterativeTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    std::stack<const TreeNode *> stack{ };
    const auto *node = this;
    const TreeNode *last_visited = nullptr;

    do {
        if (node) {
            stack.push(node);
            node = node->left_.get();
        } else {
            const auto *peek = stack.top();
            if (peek->right_ && last_visited != peek->right_.get()) { node = peek->right_.get(); }
            else {
                do_on_node(*peek);
                last_visited = peek;
                stack.pop();
            }
        }
    } while (!stack.empty() || node);
}

void TreeNode::levelOrderBFSTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    std::queue<const TreeNode *> queue{ };
    queue.push(this);
    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();
        do_on_node(*node);
        if (node->left_) queue.push(node->left_.get());
        if (node->right_) queue.push(node->right_.get());
    }
}

unsigned TreeNode::reSumSubSize() {
    return size_ = (left_ ? left_->reSumSubSize() : 0U)
        + (right_ ? right_->reSumSubSize() : 0U) + 1;
}

std::string TreeNode::toString() const { return std::to_string(key_).append(":").append(std::to_string(value_)); }

AsciiNodePtr AsciiTree::buildTree(const BinaryTree &tree) {
    root_ = buildTreeRecursively(tree.root());
    root_->parentDirection = 0;
    return root_;
}

AsciiNodePtr AsciiTree::buildTreeRecursively(const TreeNodePtr t_node) const {
    if (!t_node) { return nullptr; }
    auto node = std::make_shared<AsciiNode>();
    node->left = buildTreeRecursively(t_node->left_);
    node->right = buildTreeRecursively(t_node->right_);
    if (node->left) { node->left->parentDirection = -1; }
    if (node->right) { node->right->parentDirection = 1; }
    node->label = t_node->toString();
    node->labelLength = static_cast<int>(node->label.length());
    return node;
}

void AsciiTree::computeLeftProfile(const AsciiNodePtr t_node, const int x, const int y) {
    if (!t_node) return;
    bool isLeft = t_node->parentDirection == -1;
    // x - len(label)/2 lProfile都是非正数，取最小的 即最远
    leftProfile_[y] = std::min(leftProfile_[y], x - (t_node->labelLength - isLeft) / 2);
    if (t_node->left) {
        //如果有左支，对每一层 做相应的扩展
        for (int i = 1; i <= t_node->edgeLength && y + i < MAX_HEIGHT; ++i) {
            leftProfile_[y + i] = std::min(leftProfile_[y + i], x - i); // x-i向左的偏离字符数
        }
    }
    /*递归计算子节点，跳过已计算的那些边*/
    computeLeftProfile(t_node->left, x - t_node->edgeLength - 1, y + t_node->edgeLength + 1);
    computeLeftProfile(t_node->right, x + t_node->edgeLength + 1, y + t_node->edgeLength + 1);
}

void AsciiTree::computeRightProfile(const AsciiNodePtr t_node, const int x, const int y) {
    if (!t_node) return;
    bool isRight = t_node->parentDirection == 1;
    rightProfile_[y] = std::max(rightProfile_[y], x + (t_node->labelLength - isRight) / 2); //rProfile都是放非负数
    if (t_node->right) {
        for (int i = 1; i <= t_node->edgeLength && y + i < MAX_HEIGHT; ++i) {
            rightProfile_[y + i] = std::max(rightProfile_[y + i],
                                            x + i);
        }
    }
    computeRightProfile(t_node->left, x - t_node->edgeLength - 1, y + t_node->edgeLength + 1);
    computeRightProfile(t_node->right, x + t_node->edgeLength + 1, y + t_node->edgeLength + 1);
}

void AsciiTree::computeEdgeLengths(const AsciiNodePtr t_node) {
    if (!t_node) return;
    computeEdgeLengths(t_node->left);
    computeEdgeLengths(t_node->right);

    int min_height;
    /* 自底向上递归 */
    if (!t_node->right && !t_node->left) { // 如果没有后继，边长则为0
        t_node->edgeLength = 0;
    } else {
        if (t_node->left) { // 如果有左支
            for (int i = 0; i < t_node->left->height && i < MAX_HEIGHT; i++) { rightProfile_[i] = -INF; }
            computeRightProfile(t_node->left, 0, 0);
            min_height = t_node->left->height;
        } else { min_height = 0; }
        if (t_node->right) { // 如果有右支
            for (int i = 0; i < t_node->right->height && i < MAX_HEIGHT; i++) { leftProfile_[i] = INF; }
            computeLeftProfile(t_node->right, 0, 0);
            min_height = std::min(t_node->right->height, min_height);
        } else { min_height = 0; }
        int delta = 4;
        for (int i = 0; i < min_height; i++) { delta = std::max(delta, GAP + 1 + rightProfile_[i] - leftProfile_[i]); }

        // 如果节点有两个高度为1的子节点
        //那么我们允许这两个子节点都在高度1，而不是2
        if ((t_node->left && t_node->left->height == 1 ||
            t_node->right && t_node->right->height == 1) && delta > 4) { delta--; }

        t_node->edgeLength = ((delta + 1) / 2) - 1;
    }

    //计算并填写节点的高度
    int height = 1;
    if (t_node->left) { height = std::max(t_node->left->height + t_node->edgeLength + 1, height); }
    if (t_node->right) { height = std::max(t_node->right->height + t_node->edgeLength + 1, height); }
    t_node->height = height;
}

void AsciiTree::printLevel(const AsciiNodePtr node, const int x, const int level, int &print_next) {
    if (!node) return; // 空节点不作操作
    bool isLeft = node->parentDirection == -1; // 当前是否是父节点的左支，是的话要进行偏移操作
    if (level == 0) { //打印节点
        auto print_size =
            x - print_next - (node->labelLength - isLeft) / 2; //父节点x坐标减去当前层偏移量，再根据字符串长度居中
        for (int i = 0; i < print_size; i++) { std::cout << " "; }
        std::cout << node->label;

        print_next += print_size + node->labelLength; // 空格数量 + 标签字符数量
    } else if (node->edgeLength >= level) { //打印两节点之间的边
        if (node->left) {
            /*计算数字左端的位置，填充空格到最左端*/
            auto print_size = x - print_next - level;
            for (int i = 0; i < print_size; i++) { std::cout << " "; }
            std::cout << '/';

            print_next += print_size + 1; // 包括制表符的1个
        }
        if (node->right) {
            auto print_size = x - print_next + level;
            for (int i = 0; i < print_size; i++) { std::cout << " "; }
            std::cout << '\\';

            print_next += print_size + 1;
        }
    } else { //递归打印两个子节点，每一条边的一个成分 宽度是1，每一条边的长度+当前层级=下一节点的层级
        printLevel(node->left,
                   x - node->edgeLength - 1,
                   level - node->edgeLength - 1, print_next);
        printLevel(node->right,
                   x + node->edgeLength + 1,
                   level - node->edgeLength - 1, print_next);
    }
}

void AsciiTree::print_ascii_tree(const BinaryTree &t) {
    if (!t.root()) {
        std::cout << "EMPTY" << std::endl;
        return;
    }
    AsciiNodePtr parent_root = buildTree(t);
    computeEdgeLengths(parent_root);
    for (int i = 0; i < parent_root->height && i < MAX_HEIGHT; i++) { leftProfile_[i] = INF; }
    computeLeftProfile(parent_root, 0, 0);
    int x_min = 0; // 中点
    for (int i = 0; i < parent_root->height && i < MAX_HEIGHT; i++) { x_min = std::min(x_min, leftProfile_[i]); }
    int print_next = 0;
    for (int i = 0; i < parent_root->height; i++) {
        printLevel(parent_root, -x_min, i, print_next);
        print_next = 0; //每新的一行 归零光标 移至首位
        std::cout << std::endl;
    }
    if (parent_root->height >= MAX_HEIGHT) {
        std::cout << "(This tree is taller than " << MAX_HEIGHT
                  << ", and may be drawn incorrectly.)" << std::endl;
    }
}

int BinaryTree::get(const int key) const {
    auto node = root_;
    while (node) {
        auto node_value = node->key_;
        if (key < node_value) { node = node->left_; } //值比中间的小，递归插到左边
        else if (key > node_value) { node = node->right_; } //值比中间的大，递归插到右边
        else { return node->value_; } // 值相同 重复，不进行操作
    }
    throw std::range_error(std::to_string(key) + " not Found.");
}

bool BinaryTree::contain(const int key) const noexcept {
    try {
        get(key);
        return true;
    }
    catch (std::range_error &error) {
        std::cerr << error.what();
        return false;
    }
}

const TreeNode &BinaryTree::put(const int key, const int value) {
    root_ = put(root_, key, value);
    return *root_;
}

TreeNodePtr BinaryTree::put(TreeNodePtr node, const int key, const int value) const {
    if (!node) return std::make_shared<TreeNode>(key, value);

    auto node_value = node->key_;
    if (key < node_value) { node->left_ = put(node->left_, key, value); } //值比中间的小，递归插到左边
    else if (key > node_value) { node->right_ = put(node->right_, key, value); } //值比中间的大，递归插到右边
    else { node->value_ = value; } // 找到相同的键了 替换值
    node->reSumSubSize();
    return node;
}

const TreeNode &BinaryTree::min() const {
    if (emptyQ()) throw std::underflow_error("Empty Tree!");
    return *min(root_);
}

TreeNodePtr BinaryTree::min(TreeNodePtr node) const {
    if (!node->left_) return node;
    return min(node->left_);
}

bool BinaryTree::emptyQ() const noexcept { return root_ == nullptr; }

TreeNodePtr BinaryTree::max(TreeNodePtr node) const {
    if (!node->right_) return node;
    return max(node->right_);
}

const TreeNode &BinaryTree::max() const {
    if (emptyQ()) throw std::underflow_error("Empty Tree!");
    return *max(root_);
}

unsigned BinaryTree::leavesCount() const {
    unsigned count = 0U;
    auto counter =
        [&count](const TreeNode &node) -> void { if (!(node.left_ || node.right_)) count++; };
    preOrderIterativeTraverse(counter);
    return count;
}

void BinaryTree::preOrderRecursiveTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    if (root_)
        root_->preOrderRecursiveTraverse(do_on_node);
}

void BinaryTree::inOrderRecursiveTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    if (root_)
        root_->inOrderRecursiveTraverse(do_on_node);
}

void BinaryTree::postOrderRecursiveTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    if (root_)
        root_->postOrderRecursiveTraverse(do_on_node);
}

void BinaryTree::preOrderIterativeTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    if (root_)
        root_->preOrderIterativeTraverse(do_on_node);
}

void BinaryTree::inOrderIterativeTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    if (root_)
        root_->inOrderIterativeTraverse(do_on_node);
}

void BinaryTree::postOrderIterativeTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    if (root_)
        root_->postOrderIterativeTraverse(do_on_node);
}

void BinaryTree::levelOrderBFSTraverse(const std::function<void(const TreeNode &)> &do_on_node) const {
    if (root_)
        root_->levelOrderBFSTraverse(do_on_node);
}

void BinaryTree::swapChildren() const { if (root_) root_->swapChildren(); }

void BinaryTree::print() const { AsciiTree().print_ascii_tree(*this); }

void BinaryTree::deleteMin() {
    if (emptyQ()) throw std::underflow_error("Empty Tree!");
    root_ = deleteMin(root_);
}

TreeNodePtr BinaryTree::deleteMin(TreeNodePtr node) const {
    if (!node->left_) return node->right_;
    node->left_ = deleteMin(node->left_);
    node->reSumSubSize();
    return node;
}

void BinaryTree::deleteMax() {
    if (emptyQ()) throw std::underflow_error("Empty Tree!");
    root_ = deleteMax(root_);
}

TreeNodePtr BinaryTree::deleteMax(TreeNodePtr node) const {
    if (!node->right_) return node->left_;
    node->right_ = deleteMin(node->right_);
    node->reSumSubSize();
    return node;
}

int BinaryTree::remove(const int key) {
    auto old_value = get(key);
    root_ = remove(root_, key);
    return old_value;
}

TreeNodePtr BinaryTree::remove(TreeNodePtr node, const int key) const {
    if (!node) return nullptr;

    if (key > node->key_) { //比节点大，向右支前进
        node->right_ = remove(node->right_, key);
    } else if (key < node->key_) { //比节点小，向左支前进
        node->left_ = remove(node->left_, key);
    } else { //相等，把右支最小元素提到上层来
        if (!node->right_) return node->left_;
        if (!node->left_) return node->right_;
        auto original_node = node; // 备份这个要删除的节点
        node = min(original_node->right_); // 先找到右支最小节点
        node->right_ = deleteMin(original_node->right_); // 把原节点的右支接在最小节点右边
        node->left_ = original_node->left_; //把原节点的左支接在最小节点上
    }
    return node; // 递归连接回去
}

BinaryTree::BinaryTree(const int rootKey, const int rootValue) :
    root_{std::make_shared<TreeNode>(rootKey, rootValue)} { }

BinaryTree::~BinaryTree() { while (root_) { root_ = deleteMin(root_); }}

std::ostream &operator<<(std::ostream &os, const TreeNode &obj) { return os << obj.toString(); }

std::ostream &operator<<(std::ostream &os, const BinaryTree &obj) {
    obj.print();
    return os;
}
