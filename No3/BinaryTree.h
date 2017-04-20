#pragma once
#include <memory>
#include <ostream>
#include <functional>

struct TreeNode;
struct AsciiNode;
class BinaryTree;
typedef std::shared_ptr<TreeNode> TreeNodePtr;
typedef std::shared_ptr<AsciiNode> AsciiNodePtr;

/**
 * \brief 二叉树的节点类
 */
struct TreeNode {
    TreeNodePtr left = nullptr, right = nullptr; //左右支
    int key; //键
    int value; //值
    unsigned size; //子树下有多少元素
    explicit TreeNode(const int key,
                      const int value,
                      const unsigned size = 1U) : key{key},
                                                  value{value},
                                                  size{size} {}

    void preOrderRecursiveTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void inOrderRecursiveTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void postOrderRecursiveTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void preOrderIterativeTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void inOrderIterativeTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void postOrderIterativeTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void levelOrderBFSTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void swapChildren();
    std::string toString() const;
    friend std::ostream &operator<<(std::ostream &os, const TreeNode &obj);
};

/**
 * \brief 递归计算 以指定节点为根的二叉树 节点个数
 * \param node 二叉树的节点
 * \return 该节点的子元素个数，包括本身
 */
unsigned size(const TreeNodePtr node);


/**
 * \brief 为了输出二叉树的帮助类，保存了节点的左右支，与父节点的边长、方向，节点深度，字符标签数据
 */
struct AsciiNode {
    AsciiNodePtr left = nullptr, right = nullptr; //左右支
    int edgeLength;
    int height;
    int labelLength;
    int parentDirection;
    std::string label;
};

struct AsciiTree {
    void print_ascii_tree(const BinaryTree &t);
private:
    static const int MAX_HEIGHT = 30; // 最大打印高度
    static const int INF = 1 << 20;
    static const int GAP = 2; // 同级两个节点之间最小距离
    int leftProfile_[MAX_HEIGHT] = {0}; //左支 层
    int rightProfile_[MAX_HEIGHT] = {0}; //右支 层

    AsciiNodePtr root_;

    AsciiNodePtr buildTree(const BinaryTree &tree);

    AsciiNodePtr buildTreeRecursice(const TreeNodePtr t_node) const;

    /**
    * \brief 计算左支的偏离度
    * \param t_node 处理的节点
    * \param x 横坐标位置
    * \param y 纵坐标，第y层
    */
    void computeLeftProfile(const AsciiNodePtr t_node, const int x, const int y);

    /**
    * \brief 计算右支的偏离度
    * \param t_node 处理的节点
    * \param x 横坐标位置
    * \param y 纵坐标，第y层
    */
    void computeRightProfile(const AsciiNodePtr t_node, const int x, const int y);

    /**
     * \brief 递归计算节点与父节点之间的边长
     * \param t_node 要计算的节点
     */
    void computeEdgeLengths(const AsciiNodePtr t_node);

    /**
    * \brief 分三段打印一个节点，第一阶段level==0，在居中的位置输出标签字符串。
    第二阶段，判断是否存在左右支，输出斜杠
    第三阶段，判断连接边是否结束，没有则继续打印边，结束则递归打印子节点
    * \param node 树节点
    * \param x 一行中的坐标，可能为负数
    * \param level 当前打印的层级，使用引用，跨函数修改值
    */
    static void printLevel(const AsciiNodePtr node, const int x, const int level, int &print_next);
};


/**
 * \brief 二叉树，实际上是二叉搜索树
 */
class BinaryTree {
    TreeNodePtr root_ = nullptr;
    TreeNodePtr put(TreeNodePtr node, const int key, const int value) const;
    TreeNodePtr remove(TreeNodePtr node, const int key) const;
    TreeNodePtr min(TreeNodePtr node) const;
    TreeNodePtr max(TreeNodePtr node) const;
    TreeNodePtr deleteMin(TreeNodePtr node) const;
    TreeNodePtr deleteMax(TreeNodePtr node) const;
public:
    /**
     * \brief 创建一棵空树
     */
    BinaryTree() = default;
    /**
     * \brief 由给定的键值对生成带有根节点的二叉树
     * \param rootKey 根节点的键
     * \param rootValue 根节点的值
     */
    BinaryTree(const int rootKey, const int rootValue);
    ~BinaryTree();

    /**
     * \brief 根据键获取对应的值，会抛出std::range_error
     * \param key 搜索的键
     * \return 对应键的值，如果不存在则抛出错误
     */
    int get(const int key) const;
    /**
     * \brief 根据给定的键判断是否存在键值对在树中，递归搜索
     * \param key 搜索的键
     * \return 树中是否包含当前键的元素•
     */
    bool contain(const int key) const noexcept;
    /**
     * \brief 根据给定的键值对插入到树中，如果原先不存在该键 则创建一个新的节点；否则替换原先的值
     * \param key 要插入的键
     * \param value 对应键的要插入的值
     * \return 该键所在的节点
     */
    const TreeNode &put(const int key, const int value);
    /**
     * \brief 删除指定键的元素，操作之后依然保持二叉树性质，如果键不在树中，则抛出std::range_error
     * \param key 指定删除的键
     * \return 删除键的值
     */
    int remove(const int key);
    /**
     * \brief 判断是否是空树
     * \return 树为空则返回true
     */
    bool emptyQ() const;
    /**
     * \brief 删除最小元素，树为空会抛出std::underflow_error
     */
    void deleteMin();
    /**
     * \brief 删除最大元素，树为空会抛出std::underflow_error
     */
    void deleteMax();
    /**
     * \brief 寻找全树的最小节点
     * \return 最小节点的引用，不允许修改
     */
    const TreeNode &min() const;
    /**
     * \brief 寻找全树的最大节点
     * \return 最大节点的引用 ，不允许修改
     */
    const TreeNode &max() const;

    unsigned leavesCount() const;
    void preOrderRecursiveTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void inOrderRecursiveTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void postOrderRecursiveTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void preOrderIterativeTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void inOrderIterativeTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void postOrderIterativeTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void levelOrderBFSTraverse(const std::function<void(const TreeNode &)> &do_on_node) const;
    void swapChildren();
    void print() const;
    const TreeNodePtr &root() const { return root_; }
    friend std::ostream &operator<<(std::ostream &os, const BinaryTree &obj);
};
