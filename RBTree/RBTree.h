/*!
 *  SegRBTree.h

 *  Copyright(c) 2009- MediaV,Inc.

 *  \b author: Peng Futian

 *  \b Date: 2010-05-24

 *  \b Description: 声明线段树(红黑树)
 红黑树的几个性质:
 1) 每个结点只有红和黑两种颜色
 2) 根结点是黑色的
 3) 如果一个结点是红色的,那么它的左右两个子结点的颜色是黑色的
 4) 对于每个结点而言,从这个结点到叶子结点的任何路径上的黑色结点
 的数目相同
 */
#ifndef INCLUDE_SEGRBTREE_H_HEADER_INCLUDED_DXXA54BDA
#define INCLUDE_SEGRBTREE_H_HEADER_INCLUDED_DXXA54BDA
#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include "Enum.h"

template<class T1, class T2>
class Segment;

template<class T1, class T2>
class SegRBTree;

template<class T1, class T2>
class TreeSubtract;

DECLARE_ENUM(RBColour, 2)
Red,
Black
END_ENUM()

template<class T1, class T2>
class SegRBTreeNode
{
  friend class SegRBTree<T1, T2> ;
  friend class Segment<T1, T2> ;
  friend class TreeSubtract<T1, T2> ;
public:
  SegRBTreeNode();
  SegRBTreeNode(const T1 low, const T1 high, T2& value);
  SegRBTreeNode(const T1 low, const T1 high);
  ~SegRBTreeNode();

  bool equal(const SegRBTreeNode<T1, T2>& rhs) const;
  void debugDump();

  inline SegRBTreeNode* left()
  {
    return left_;
  }

  inline void left(SegRBTreeNode* pNode)
  {
    left_ = pNode;
  }

  inline SegRBTreeNode* right()
  {
    return right_;
  }

  inline void right(SegRBTreeNode* pNode)
  {
    right_ = pNode;
  }

  inline SegRBTreeNode* parent()
  {
    return parent_;
  }

  inline void parent(SegRBTreeNode* pNode)
  {
    parent_ = pNode;
  }

  inline void value(T2& t)
  {
    pValue_->clone(t);
  }

  inline void value(T2* pT)
  {
    if (pT)
    {
      value(*pT);
    }
  }

  inline const T2* value() const
  {
    return pValue_;
  }

  inline T2* value()
  {
    return pValue_;
  }

  inline const T1 high() const
  {
    return high_;
  }

  inline const T1 low() const
  {
    return low_;
  }
protected:
  SegRBTreeNode(const SegRBTreeNode<T1, T2>& rhs)
  {
  }

  SegRBTreeNode<T1, T2>& operator=(const SegRBTreeNode<T1, T2>& rhs)
  {
  }
private:
  //如果低值大于高值，则交换高低值
  void verify()
  {
    if (low_ > high_)
    {
      T1 temp = high_;
      high_ = low_;
      low_ = temp;
    }
  }
  //释放节点的所申请的资源
  void release();
  void dump(int level)
  {
    std::string tabStr(level, '\t');
    std::cout << tabStr << "segment low:" << low_ << " high:" << high_ << " colour:" << ((colour_ == RBColour::Red)
      ? "Red" : "Black") << std::endl;
    if (left_)
    {
      std::cout << tabStr << "L-->";
      left_->dump(level + 1);
    }
    if (right_)
    {
      std::cout << tabStr << "R-->";
      right_->dump(level + 1);
    }
  }
  //交换节点数据,pNode是要被删除的节点,故他的数据不保留
  inline void swapData(SegRBTreeNode<T1, T2>* pNode)
  {
    T2* pValue = pValue_;
    low_ = pNode->low_;
    high_ = pNode->high_;
    //直接数据交换指针
    pValue_ = pNode->pValue_;
    pNode->pValue_ = pValue;
  }

  //左儿子
  SegRBTreeNode<T1, T2>* left_;
  //右儿子
  SegRBTreeNode<T1, T2>* right_;
  //父节点
  SegRBTreeNode<T1, T2>* parent_;
  //颜色
  RBColour colour_;
  //数据
  T2* pValue_;
  //低值
  T1 low_;
  //高值
  T1 high_;
};

template<class T1, class T2>
class Segment
{
public:
  Segment(T1 low, T1 high, SegRBTreeNode<T1, T2>* pNode) :
    low_(low), high_(high), pNode_(pNode)
  {
  }

  Segment(const Segment<T1, T2>& rhs) :
    low_(rhs.low_), high_(rhs.high_), pNode_(rhs.pNode_)
  {
  }

  Segment<T1, T2>& operator=(const Segment<T1, T2>& rhs)
  {
    low_ = rhs.low_;
    high_ = rhs.high_;
    pNode_ = rhs.pNode_;
    return *this;
  }

  T1 low_;
  T1 high_;
  SegRBTreeNode<T1, T2>* pNode_;
};

//删除树的数据
template<class T1, class T2>
class TreeSubtract
{
public:
  TreeSubtract(SegRBTree<T1, T2>* pTree, T2& t2) :
    pTree_(pTree), pT2_(&t2)
  {
  }

  void operator ()(SegRBTreeNode<T1, T2>* pNode)
  {
    if (pNode)
    {
      T2* pT2 = pNode->pValue_;
      if (pT2)
      {
        pT2->subtract(*pT2_);
        if (pT2->empty())
        {
          //如果数据为空,删除此节点
          pTree_->erase(pNode);
        }
        else
        {
          //采用反序遍历,当前节点的后序节点是前一次处理过的节点,如果节点数据相等,且线段相连,则合并
          SegRBTreeNode<T1, T2>* next = pTree_->next(pNode);
          if (next && ((next->low_ - 1) == pNode->high_))
          {
            if (pT2->equal(*next->pValue_))
            {
              pNode->high_ = next->high_;
              pTree_->erase(next);
            }
          }
        }
      }
      else
      {
        //节点数据不存在,删除节点
        pTree_->erase(pNode);
      }
    }
  }

  void execute()
  {
    if (pTree_)
    {
      //采用反序遍历
      pTree_->rvisit(*this);
    }
  }
private:
  SegRBTree<T1, T2>* pTree_;
  T2 * pT2_;
};

template<class T1, class T2>
class TreeClone
{
public:
  TreeClone(SegRBTree<T1, T2>* pTree) :
    pTree_(pTree)
  {
  }

  void operator ()(SegRBTreeNode<T1, T2>* pNode)
  {
    if (pTree_ && pNode)
    {
      pTree_->addEntry(pNode);
    }
  }

  void execute(SegRBTree<T1, T2>& tree)
  {
    if (pTree_)
    {
      pTree_->clear();
      tree.visit(*this);
      pTree_->capacity_ = tree.capacity_;
    }
  }
private:
  SegRBTree<T1, T2>* pTree_;
};

template<class T1, class T2>
class TreeDeleter
{
public:
  TreeDeleter(SegRBTree<T1, T2>* pTree) :
    pTree_(pTree)
  {
  }

  void operator ()(SegRBTreeNode<T1, T2>* pNode)
  {
    nodeContainer_.push_back(pNode);
  }

  void execute()
  {
    if (pTree_)
    {
      pTree_->visit(*this);
      typename std::vector<SegRBTreeNode<T1, T2>*>::iterator it = nodeContainer_.begin();
      for (; it != nodeContainer_.end(); it++)
      {
        if (*it)
        {
          delete *it;
        }
      }
      pTree_->root_ = NULL;
      pTree_->size_ = 0;
      pTree_->capacity_ = 0;
    }
  }
private:
  std::vector<SegRBTreeNode<T1, T2>*> nodeContainer_;
  SegRBTree<T1, T2>* pTree_;
};

template<class T1, class T2>
class SegRBTree
{
  typedef std::stack<Segment<T1, T2> > SegStack;
  typedef TreeSubtract<T1, T2> tree_subtract;
  typedef TreeClone<T1, T2> tree_clone;
  typedef TreeDeleter<T1, T2> tree_deleter;
  typedef enum _tagSideOfNode
  {
      Left,
      Right
  } SN;
  friend class TreeSubtract<T1, T2> ;
  friend class TreeClone<T1, T2> ;
  friend class TreeDeleter<T1, T2> ;
public:
  SegRBTree(const size_t capacity = 0);
  SegRBTree(SegRBTree<T1, T2>& rhs);
  virtual ~SegRBTree();
  SegRBTree<T1, T2>& operator=(const SegRBTree<T1, T2>& rhs)
  {
    if (this == &rhs)
    {
      return *this;
    }
    clone(rhs);
    return *this;
  }

  bool operator==(const SegRBTree<T1, T2>& rhs) const
  {
    return equal(rhs);
  }

  int addEntry(const T1 low, const T1 high, T2& t2);

  bool query(const T1 key, T2& value);
  T2* query(const T1 key);
  void clone(SegRBTree<T1, T2>& rhs);

  inline bool empty() const
  {
    return size_ == 0;
  }

  inline bool full()
  {
    return (capacity_ > 0) && (capacity_ < size_);
  }

  void capacity(const size_t capacity)
  {
    capacity_ = capacity;
  }

  const size_t capacity() const
  {
    return capacity_;
  }

  inline const size_t size() const
  {
    return size_;
  }
  bool equal(const SegRBTree<T1, T2> & rhs) const;

  void clear();

  void debugDump(int detail = 0)
  {
    if (!detail)
    {
      std::cout << std::endl;
      if (root_)
        root_->dump(0);
    }
    else
    {
      std::cout << std::endl;
      if (root_)
        root_->debugDump();
    }
  }
private:
  SegRBTreeNode<T1, T2>* createNode(const T1 low, const T1 high, T2* pValue, SegRBTreeNode<T1, T2>* pInsertNode,
                                    const SN sn = Right);
  SegRBTreeNode<T1, T2>* createNode(const T1 low, const T1 high, SegRBTreeNode<T1, T2>* pInsertNode,
                                    const SN sn = Right);
  SegRBTreeNode<T1, T2>* createNode(SegRBTreeNode<T1, T2> *pNode, SegRBTreeNode<T1, T2>* pInsertNode,
                                    const SN sn = Right);
  SegRBTreeNode<T1, T2>* insertNode(SegRBTreeNode<T1, T2> *pNode, SegRBTreeNode<T1, T2>* pInsertNode,
                                    const SN sn = Right);
  int addEntry(SegRBTreeNode<T1, T2> *pNode);
  int addEntry_i(const T1 low, const T1 high, T2& value);
  int addValue(SegRBTreeNode<T1, T2> *pNode, T2& value);
  //向左旋转
  void leftRotate(SegRBTreeNode<T1, T2>* x);
  //向右旋转
  void rightRotate(SegRBTreeNode<T1, T2>* x);
  //插入节点后,重新平衡红黑树
  void insertRebalance(SegRBTreeNode<T1, T2>* pNode);
  void subtract(T2& t2);

  void deleteRebalance(SegRBTreeNode<T1, T2>* x, SegRBTreeNode<T1, T2>* parent);

  void erase(SegRBTreeNode<T1, T2>* x);
  SegRBTreeNode<T1, T2>* first() const;
  SegRBTreeNode<T1, T2>* last() const;
  SegRBTreeNode<T1, T2>* next(const SegRBTreeNode<T1, T2>* pNode) const;
  SegRBTreeNode<T1, T2>* prev(const SegRBTreeNode<T1, T2>* pNode) const ;

  /*!
   * \b author: Peng Futian MediaV
   *
   * \b Date: 2010-05-25
   *
   * \b Description: 顺序遍历树,并对每个节点执行指定的操作
   *	@param action 操作
   *
   *	@reval 操作对象
   */
  template<class T>
  T& visit(T& action)
  {
    SegRBTreeNode<T1, T2>* pNode = first();
    while (pNode)
    {
      action(pNode);
      pNode = next(pNode);
    }
    return action;
  }

  /*!
   * \b author: Peng Futian MediaV
   *
   * \b Date: 2010-05-25
   *
   * \b Description: 反序遍历树,并对每个节点执行指定的操作
   *	@param action 操作
   *
   *	@reval 操作对象
   */
  template<class T>
  T& rvisit(T& action)
  {
    SegRBTreeNode<T1, T2>* preNode = NULL;
    SegRBTreeNode<T1, T2>* pNode = last();
    while (pNode)
    {
      preNode = prev(pNode);
      action(pNode);
      pNode = preNode;
    }
    return action;
  }

  SegRBTreeNode<T1, T2>* root_;
  size_t size_;
  size_t capacity_;
};

#include "SegRBTree_inl.h"

#
