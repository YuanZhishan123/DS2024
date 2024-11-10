#include<stack>
using  namespace  std;
#include<iostream>

#define BinNodePosi(T) BinNode<T>*  // 节点位置

#define stature(p) ((p) ? (p)->height : -1)  // 节点高度（与“空树高度为-1”的约定相统一）




// 头文件的内容
typedef enum { RB_RED, RB_BLACK }RBColor ; // 节点颜色


template <typename T>
struct BinNode {  // 二叉树节点模板类
    T data;               // 数值
    BinNodePosi(T) parent;  // 父节点
    BinNodePosi(T) lc;      // 左孩子
    BinNodePosi(T) rc;      // 右孩子
    int height;            // 高度（通用）
    int npl;               // Null Path Length（左式堆，也可直接用height代替）
    RBColor color;         // 颜色（红黑树）

    // 构造函数
    BinNode() : parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}

    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
            int h = 0, int n = 1, RBColor c = RB_RED)
        : data(e), parent(p), lc(lc), rc(rc), height(h), npl(n), color(c) {}

    // 操作接口
    int size();  // 统计当前节点后代总数，亦即以其为根的子树的规模
    BinNodePosi(T) insertAsLC(T const&e){
		return lc=new BinNode(e,this);}  // 作为当前节点的左孩子插入新节点
    BinNodePosi(T) insertAsRC(T const&e){
		return rc=new BinNode(e,this);}  // 作为当前节点的右孩子插入新节点
    BinNodePosi(T) succ();  // 取当前节点的直接后继

    // 遍历
    template <typename VST>
    void travLevel(VST&);  // 子树层次遍历

    template <typename VST>
    void travPre(VST&);  // 子树先序遍历

    template <typename VST>
    void travIn(VST&);  // 子树中序遍历

    template <typename VST>
    void travPost(VST&);  // 子树后序遍历

    // 比较器、判等器
    bool operator<(BinNode const& bn) { return data < bn.data; }  // 小于
    bool operator==(BinNode const& bn) { return data == bn.data; }  // 等于
};
template <typename T>
class BinTree {  // 二叉树模板类

protected:
    int _size;  // 树的规模
    BinNodePosi(T) _root;  // 根节点

    // 更新节点x的高度
    virtual int updateHeight(BinNodePosi(T) x); 

    // 更新节点x及其祖先的高度
    void updateHeightAbove(BinNodePosi(T) x);

public:
    // 构造函数
    BinTree() : _size(0), _root(NULL) {}

    // 析构函数
    ~BinTree() { if (_size > 0) remove(_root); }

    // 获取树的规模
    int size() const { return _size; }

    // 判断树是否为空
    bool empty() const { return !_root; }

    // 获取树根
    BinNodePosi(T) root() const { return _root; }

    // 插入根节点
    BinNodePosi(T) insertAsRoot(T const& e);

    // 将e作为x的左孩子插入（原无）
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);

    // 将e作为x的右孩子插入（原无）
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);

    // 将Tree作为x的左子树接入
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>*& Tree);

    // 将Tree作为x的右子树接入
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>*& Tree);

    // 删除以位置x处节点为根的子树，返回该子树原先的规模
    int remove(BinNodePosi(T) x);

    // 将子树x从当前树中摘除，并将其转换为一棵独立子树
    BinTree<T>* secede(BinNodePosi(T) x);

    // 递归版层次遍历
    template <typename VST>
    void travLevel(VST& visit) {
        if (_root) _root->travLevel(visit);
    }

    // 递归版先序遍历
    template <typename VST>
    void travPre_R(VST& visit) {
        if (_root) _root->travPre(visit);
    }

    // 递归版中序遍历
    template <typename VST>
    void travIn_R(VST& visit) {
        if (_root) _root->travIn(visit);
    }

    // 递归版后序遍历
    template <typename VST>
    void travPost_R(VST& visit) {
        if (_root) _root->travPost(visit);
    }
    // 迭代版的先序遍历
    template <typename VST>
    void travPre_I(VST& visit) {
        if (!_root) return;
        
        stack<BinNodePosi(T)> s;
        s.push(_root);

        while (!s.empty()) {
            BinNodePosi(T) node = s.top(); s.pop();
            visit(node->data);  // 访问节点
            if (node->rc) s.push(node->rc);  // 右子节点先入栈
            if (node->lc) s.push(node->lc);  // 左子节点后入栈
        }
    }

    // 迭代版的中序遍历
    template <typename VST>
    void travIn_I(VST& visit) {
        if (!_root) return;

        stack<BinNodePosi(T)> s;
        BinNodePosi(T) current = _root;

        while (current || !s.empty()) {
            // 向左走，直到最左节点
            while (current) {
                s.push(current);
                current = current->lc;
            }

            // 弹出栈顶元素并访问
            current = s.top(); s.pop();
            visit(current->data);  // 访问节点

            // 转向右子树
            current = current->rc;
        }
    }

    // 迭代版的后序遍历
    template <typename VST>
    void travPost_I(VST& visit) {
        if (!_root) return;

        stack<BinNodePosi(T)> s1, s2;
        s1.push(_root);

        while (!s1.empty()) {
            BinNodePosi(T) node = s1.top(); s1.pop();
            s2.push(node);  // 先将节点压入第二个栈（反向访问）

            if (node->lc) s1.push(node->lc);  // 左子节点
            if (node->rc) s1.push(node->rc);  // 右子节点
        }

        // 第二个栈弹出并访问节点，得到正确的后序遍历顺序
        while (!s2.empty()) {
            BinNodePosi(T) node = s2.top(); s2.pop();
            visit(node->data);  // 访问节点
        }
    }

    // 比较器
    bool operator<(BinTree<T> const& t) {
        return _root && t._root && (_root < t._root);
    }

    // 判等器
    bool operator==(BinTree<T> const& t) {
        return _root && t._root && (_root == t._root);
    }
};
template <typename T>
int BinNode<T>::size() {
    int s = 1;  // 当前节点算一个
    if (lc) s += lc->size();  // 加上左子树的规模
    if (rc) s += rc->size();  // 加上右子树的规模
    return s;
}
template <typename T>
BinNodePosi(T) BinNode<T>::succ() {
    BinNodePosi(T) p = this;
    if (rc) {  // 如果有右子树，后继就是右子树的最左节点
        p = rc;
        while (p->lc) p = p->lc;
    } else {  // 否则，后继是最近的祖先节点（即父节点，父节点的左子树是当前节点）
        while (p->parent && p == p->parent->rc) {
            p = p->parent;
        }
        p = p->parent;  // 父节点就是后继节点
    }
    return p;
}
template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) {
    return x->height = 1 + max(stature(x->lc), stature(x->rc));  // 高度 = 左右子树最大高度 + 1
}
template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) {
    while (x) {  // 一直往上更新
        updateHeight(x);  // 更新当前节点的高度
        x = x->parent;  // 移动到父节点
    }
}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e) {
    if (_root) return NULL;  // 如果已有根节点则无法插入
    _root = new BinNode<T>(e);  // 创建新的根节点
    _size = 1;
    return _root;
}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e) {
    x->insertAsLC(e);  // 利用节点自身的方法插入左孩子
    updateHeightAbove(x);  // 更新x及其祖先的高度
    _size++;
    return x->lc;
}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e) {
    x->insertAsRC(e);  // 利用节点自身的方法插入右孩子
    updateHeightAbove(x);  // 更新x及其祖先的高度
    _size++;
    return x->rc;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& Tree) {
    if (x->lc) return NULL;  // 如果左子树已经存在，不能接入
    x->lc = Tree->_root;  // 将Tree的根接到x的左子树
    if (x->lc) x->lc->parent = x;  // 更新左子树的父节点
    _size += Tree->_size;  // 更新树的规模
    Tree->_root = NULL;  // Tree已经被接入，清空原树
    return x->lc;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& Tree) {
    if (x->rc) return NULL;  // 如果右子树已经存在，不能接入
    x->rc = Tree->_root;  // 将Tree的根接到x的右子树
    if (x->rc) x->rc->parent = x;  // 更新右子树的父节点
    _size += Tree->_size;  // 更新树的规模
    Tree->_root = NULL;  // Tree已经被接入，清空原树
    return x->rc;
}
template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {
    if (!x) return 0;  // 空节点直接返回
    int s = x->size();  // 获取子树规模
    if (x->lc) remove(x->lc);  // 删除左子树
    if (x->rc) remove(x->rc);  // 删除右子树
    delete x;  // 删除当前节点
    _size -= s;  // 更新树的规模
    return s;
}
template <typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) {
    if (!x) return NULL;
    BinTree<T>* newTree = new BinTree<T>();  // 创建新树
    newTree->_root = x;  // 新树的根就是x
    if (x->parent) {
        if (x == x->parent->lc) x->parent->lc = NULL;
        if (x == x->parent->rc) x->parent->rc = NULL;
    }
    x->parent = NULL;  // 将x的父节点设置为空
    _size -= x->size();  // 更新当前树的规模
    return newTree;  // 返回新树
}

