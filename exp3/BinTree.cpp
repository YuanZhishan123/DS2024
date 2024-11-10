#include<stack>
using  namespace  std;
#include<iostream>

#define BinNodePosi(T) BinNode<T>*  // �ڵ�λ��

#define stature(p) ((p) ? (p)->height : -1)  // �ڵ�߶ȣ��롰�����߶�Ϊ-1����Լ����ͳһ��




// ͷ�ļ�������
typedef enum { RB_RED, RB_BLACK }RBColor ; // �ڵ���ɫ


template <typename T>
struct BinNode {  // �������ڵ�ģ����
    T data;               // ��ֵ
    BinNodePosi(T) parent;  // ���ڵ�
    BinNodePosi(T) lc;      // ����
    BinNodePosi(T) rc;      // �Һ���
    int height;            // �߶ȣ�ͨ�ã�
    int npl;               // Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
    RBColor color;         // ��ɫ���������

    // ���캯��
    BinNode() : parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}

    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
            int h = 0, int n = 1, RBColor c = RB_RED)
        : data(e), parent(p), lc(lc), rc(rc), height(h), npl(n), color(c) {}

    // �����ӿ�
    int size();  // ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
    BinNodePosi(T) insertAsLC(T const&e){
		return lc=new BinNode(e,this);}  // ��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
    BinNodePosi(T) insertAsRC(T const&e){
		return rc=new BinNode(e,this);}  // ��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
    BinNodePosi(T) succ();  // ȡ��ǰ�ڵ��ֱ�Ӻ��

    // ����
    template <typename VST>
    void travLevel(VST&);  // ������α���

    template <typename VST>
    void travPre(VST&);  // �����������

    template <typename VST>
    void travIn(VST&);  // �����������

    template <typename VST>
    void travPost(VST&);  // �����������

    // �Ƚ������е���
    bool operator<(BinNode const& bn) { return data < bn.data; }  // С��
    bool operator==(BinNode const& bn) { return data == bn.data; }  // ����
};
template <typename T>
class BinTree {  // ������ģ����

protected:
    int _size;  // ���Ĺ�ģ
    BinNodePosi(T) _root;  // ���ڵ�

    // ���½ڵ�x�ĸ߶�
    virtual int updateHeight(BinNodePosi(T) x); 

    // ���½ڵ�x�������ȵĸ߶�
    void updateHeightAbove(BinNodePosi(T) x);

public:
    // ���캯��
    BinTree() : _size(0), _root(NULL) {}

    // ��������
    ~BinTree() { if (_size > 0) remove(_root); }

    // ��ȡ���Ĺ�ģ
    int size() const { return _size; }

    // �ж����Ƿ�Ϊ��
    bool empty() const { return !_root; }

    // ��ȡ����
    BinNodePosi(T) root() const { return _root; }

    // ������ڵ�
    BinNodePosi(T) insertAsRoot(T const& e);

    // ��e��Ϊx�����Ӳ��루ԭ�ޣ�
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);

    // ��e��Ϊx���Һ��Ӳ��루ԭ�ޣ�
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);

    // ��Tree��Ϊx������������
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>*& Tree);

    // ��Tree��Ϊx������������
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>*& Tree);

    // ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
    int remove(BinNodePosi(T) x);

    // ������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������
    BinTree<T>* secede(BinNodePosi(T) x);

    // �ݹ���α���
    template <typename VST>
    void travLevel(VST& visit) {
        if (_root) _root->travLevel(visit);
    }

    // �ݹ���������
    template <typename VST>
    void travPre_R(VST& visit) {
        if (_root) _root->travPre(visit);
    }

    // �ݹ���������
    template <typename VST>
    void travIn_R(VST& visit) {
        if (_root) _root->travIn(visit);
    }

    // �ݹ��������
    template <typename VST>
    void travPost_R(VST& visit) {
        if (_root) _root->travPost(visit);
    }
    // ��������������
    template <typename VST>
    void travPre_I(VST& visit) {
        if (!_root) return;
        
        stack<BinNodePosi(T)> s;
        s.push(_root);

        while (!s.empty()) {
            BinNodePosi(T) node = s.top(); s.pop();
            visit(node->data);  // ���ʽڵ�
            if (node->rc) s.push(node->rc);  // ���ӽڵ�����ջ
            if (node->lc) s.push(node->lc);  // ���ӽڵ����ջ
        }
    }

    // ��������������
    template <typename VST>
    void travIn_I(VST& visit) {
        if (!_root) return;

        stack<BinNodePosi(T)> s;
        BinNodePosi(T) current = _root;

        while (current || !s.empty()) {
            // �����ߣ�ֱ������ڵ�
            while (current) {
                s.push(current);
                current = current->lc;
            }

            // ����ջ��Ԫ�ز�����
            current = s.top(); s.pop();
            visit(current->data);  // ���ʽڵ�

            // ת��������
            current = current->rc;
        }
    }

    // ������ĺ������
    template <typename VST>
    void travPost_I(VST& visit) {
        if (!_root) return;

        stack<BinNodePosi(T)> s1, s2;
        s1.push(_root);

        while (!s1.empty()) {
            BinNodePosi(T) node = s1.top(); s1.pop();
            s2.push(node);  // �Ƚ��ڵ�ѹ��ڶ���ջ��������ʣ�

            if (node->lc) s1.push(node->lc);  // ���ӽڵ�
            if (node->rc) s1.push(node->rc);  // ���ӽڵ�
        }

        // �ڶ���ջ���������ʽڵ㣬�õ���ȷ�ĺ������˳��
        while (!s2.empty()) {
            BinNodePosi(T) node = s2.top(); s2.pop();
            visit(node->data);  // ���ʽڵ�
        }
    }

    // �Ƚ���
    bool operator<(BinTree<T> const& t) {
        return _root && t._root && (_root < t._root);
    }

    // �е���
    bool operator==(BinTree<T> const& t) {
        return _root && t._root && (_root == t._root);
    }
};
template <typename T>
int BinNode<T>::size() {
    int s = 1;  // ��ǰ�ڵ���һ��
    if (lc) s += lc->size();  // �����������Ĺ�ģ
    if (rc) s += rc->size();  // �����������Ĺ�ģ
    return s;
}
template <typename T>
BinNodePosi(T) BinNode<T>::succ() {
    BinNodePosi(T) p = this;
    if (rc) {  // ���������������̾���������������ڵ�
        p = rc;
        while (p->lc) p = p->lc;
    } else {  // ���򣬺������������Ƚڵ㣨�����ڵ㣬���ڵ���������ǵ�ǰ�ڵ㣩
        while (p->parent && p == p->parent->rc) {
            p = p->parent;
        }
        p = p->parent;  // ���ڵ���Ǻ�̽ڵ�
    }
    return p;
}
template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) {
    return x->height = 1 + max(stature(x->lc), stature(x->rc));  // �߶� = �����������߶� + 1
}
template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) {
    while (x) {  // һֱ���ϸ���
        updateHeight(x);  // ���µ�ǰ�ڵ�ĸ߶�
        x = x->parent;  // �ƶ������ڵ�
    }
}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e) {
    if (_root) return NULL;  // ������и��ڵ����޷�����
    _root = new BinNode<T>(e);  // �����µĸ��ڵ�
    _size = 1;
    return _root;
}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e) {
    x->insertAsLC(e);  // ���ýڵ�����ķ�����������
    updateHeightAbove(x);  // ����x�������ȵĸ߶�
    _size++;
    return x->lc;
}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e) {
    x->insertAsRC(e);  // ���ýڵ�����ķ��������Һ���
    updateHeightAbove(x);  // ����x�������ȵĸ߶�
    _size++;
    return x->rc;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& Tree) {
    if (x->lc) return NULL;  // ����������Ѿ����ڣ����ܽ���
    x->lc = Tree->_root;  // ��Tree�ĸ��ӵ�x��������
    if (x->lc) x->lc->parent = x;  // �����������ĸ��ڵ�
    _size += Tree->_size;  // �������Ĺ�ģ
    Tree->_root = NULL;  // Tree�Ѿ������룬���ԭ��
    return x->lc;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& Tree) {
    if (x->rc) return NULL;  // ����������Ѿ����ڣ����ܽ���
    x->rc = Tree->_root;  // ��Tree�ĸ��ӵ�x��������
    if (x->rc) x->rc->parent = x;  // �����������ĸ��ڵ�
    _size += Tree->_size;  // �������Ĺ�ģ
    Tree->_root = NULL;  // Tree�Ѿ������룬���ԭ��
    return x->rc;
}
template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {
    if (!x) return 0;  // �սڵ�ֱ�ӷ���
    int s = x->size();  // ��ȡ������ģ
    if (x->lc) remove(x->lc);  // ɾ��������
    if (x->rc) remove(x->rc);  // ɾ��������
    delete x;  // ɾ����ǰ�ڵ�
    _size -= s;  // �������Ĺ�ģ
    return s;
}
template <typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) {
    if (!x) return NULL;
    BinTree<T>* newTree = new BinTree<T>();  // ��������
    newTree->_root = x;  // �����ĸ�����x
    if (x->parent) {
        if (x == x->parent->lc) x->parent->lc = NULL;
        if (x == x->parent->rc) x->parent->rc = NULL;
    }
    x->parent = NULL;  // ��x�ĸ��ڵ�����Ϊ��
    _size -= x->size();  // ���µ�ǰ���Ĺ�ģ
    return newTree;  // ��������
}

