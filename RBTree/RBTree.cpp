/*!
 *  SegRBTree.cpp

 *  Copyright(c) 2009- MediaV,Inc.

 *  \b author: Peng Futian

 *  \b Date: 2010-05-24

 *  \b Description: 定义线段树数据结朿(红黑树)
 */

#include "SegRBTree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

template<class T1, class T2>
SegRBTreeNode<T1, T2>::SegRBTreeNode() :
  left_(NULL), right_(NULL), parent_(NULL), colour_(RBColour::Red), pValue_(NULL), low_(0), high_(0)
{
}

template<class T1, class T2>
SegRBTreeNode<T1, T2>::SegRBTreeNode(const T1 low, const T1 high, T2& value) :
  left_(NULL), right_(NULL), parent_(NULL), colour_(RBColour::Red), pValue_(new T2(value)), low_(low), high_(high)
{
  verify();
}

template<class T1, class T2>
SegRBTreeNode<T1, T2>::SegRBTreeNode(const T1 low, const T1 high) :
  left_(NULL), right_(NULL), parent_(NULL), colour_(RBColour::Red), pValue_(NULL), low_(low), high_(high)
{
  verify();
}

template<class T1, class T2>
SegRBTreeNode<T1, T2>::~SegRBTreeNode()
{
  release();
}

//释放节点的所申请的资源
template<class T1, class T2>
void SegRBTreeNode<T1, T2>::release()
{
  if (pValue_)
  {
    delete pValue_;
    pValue_ = NULL;
  }
}

template<class T1, class T2>
bool SegRBTreeNode<T1, T2>::equal(const SegRBTreeNode<T1, T2>& rhs) const
{
  if ((low_ == rhs.low_) && (high_ == rhs.high_))
  {
    if ((pValue_ == NULL) && (rhs.pValue_ == NULL))
    {
      return true;
    }
    if (pValue_ && rhs.pValue_ && pValue_->equal(*(rhs.pValue_)))
    {
      return true;
    }
  }
  return false;
}

template<class T1, class T2>
void SegRBTreeNode<T1, T2>::debugDump()
{
  std::cout << std::endl;
  std::cout << "segment low:" << low_ << " high:" << high_ << " colour:" << ((colour_ == RBColour::Red) ? "Red"
    : "Black") << std::endl;
  if (pValue_)
  {
    pValue_->debugDump();
  }
  if (left_)
  {
    left_->debugDump();
  }
  if (right_)
  {
    right_->debugDump();
  }
}

template<class T1, class T2>
SegRBTree<T1, T2>::SegRBTree(const size_t capacity) :
  root_(NULL), size_(0), capacity_(capacity)
{
}

template<class T1, class T2>
SegRBTree<T1, T2>::SegRBTree(SegRBTree& rhs) :
  root_(NULL), size_(0)
{
  clone(rhs);
}

template<class T1, class T2>
SegRBTree<T1, T2>::~SegRBTree()
{
  clear();
}

/*!
 * \b author: Peng Futian MediaV
 *
 * \b Date: 2010-05-26
 *
 * \b Description: 在指定的位置上创建节点
 *	@param pTree 树的指针
 *	@param low  线段起点
 *	@param high 线段终点
 *   @param pValue 线段的数据
 *	@param pInsertNode 插入点
 *   @param sn 在InsertNode的哪一侧插入新节点(Left ,Right)
 *
 *   @retval NULL失败,否则返回节点的指针
 *
 */
template<class T1, class T2>
SegRBTreeNode<T1, T2>* SegRBTree<T1, T2>::createNode(const T1 low, const T1 high, T2* pValue,
                                                     SegRBTreeNode<T1, T2>* pInsertNode, const SN sn)
{
  SegRBTreeNode<T1, T2>* result = NULL;
  if (pValue)
  {
    result = new SegRBTreeNode<T1, T2> (low, high, *pValue);
  }
  else
  {
    result = new SegRBTreeNode<T1, T2> (low, high);
  }
  if (result)
  {
    size_++;
    //将新成的节点插入到树中
    return insertNode(result, pInsertNode, sn);
  }
  return NULL;
}

template<class T1, class T2>
SegRBTreeNode<T1, T2>* SegRBTree<T1, T2>::createNode(const T1 low, const T1 high, SegRBTreeNode<T1, T2>* pInsertNode,
                                                     const SN sn)
{
  return createNode(low, high, NULL, pInsertNode, sn);
}

template<class T1, class T2>
SegRBTreeNode<T1, T2>* SegRBTree<T1, T2>::createNode(SegRBTreeNode<T1, T2> *pNode, SegRBTreeNode<T1, T2>* pInsertNode,
                                                     const SN sn)
{
  if (pNode)
  {
    return createNode(pNode->low_, pNode->high_, pNode->pValue_, pInsertNode, sn);
  }
  return NULL;
}

/*!
 * \b author: Peng Futian MediaV
 *
 * \b Date: 2010-05-26
 *
 * \b Description: 插入数据节点,如果sn=Left,则在指定的节点的左子点,或其左子点的最右子节点上插入节点
 *  如果sn=Right,则在指定的节点的右子点,或其右子点的最左子节点上插入节点
 *	@param pTree 树的指针
 *	@param pNode  需要插入的节点
 *	@param pInsertNode 插入点
 *   @param sn 插入方向(Left ,Right)
 *
 *   @retval 返回插入节点的指针
 *
 */
template<class T1, class T2>
SegRBTreeNode<T1, T2>* SegRBTree<T1, T2>::insertNode(SegRBTreeNode<T1, T2> *pNode, SegRBTreeNode<T1, T2>* pInsertNode,
                                                     const SN sn)
{
  SegRBTreeNode<T1, T2>* parent = pInsertNode;
  //如果插入点不为空,在插入点下寻找合适的位置插入数据
  if (parent)
  {
    switch (sn)
    {
      case Left:
        //如果当前节点的左子节点为空,直接插入新的节点,
        //否则取当前节点的左子节点的最右侧插入新节点
        if (parent->left_ == NULL)
        {
          parent->left_ = pNode;
        }
        else
        {
          parent = parent->left_;
          while (parent->right_)
          {
            parent = parent->right_;
          }
          parent->right_ = pNode;
        }

        break;
      case Right:
        //如果当前节点的右子节点为空,直接插入新的节点,
        //否则取当前节点的右子节点的最左侧插入新节点
        if (parent->right_ == NULL)
        {
          parent->right_ = pNode;
        }
        else
        {
          parent = parent->right_;
          while (parent->left_)
          {
            parent = parent->left_;
          }
          parent->left_ = pNode;
        }
        break;
      default:
        break;
    }
    //指定插入点的父节点
    pNode->parent_ = parent;
    //新插入的节点,总是红色的
    pNode->colour_ = RBColour::Red;
  }
  else
  {
    //插入点为空,说明是根节点,直接返回
    root_ = pNode;
    pNode->colour_ = RBColour::Black;
    return pNode;
  }
  //重新平衡红黑树
  insertRebalance(pNode);
  return pNode;
}

template<class T1, class T2>
int SegRBTree<T1, T2>::addEntry(const T1 low, const T1 high, T2& t2)
{
  return addEntry_i(low, high, t2);
}

template<class T1, class T2>
int SegRBTree<T1, T2>::addEntry(SegRBTreeNode<T1, T2> *pNode)
{
  if (pNode && pNode->pValue_)
  {
    return addEntry_i(pNode->low_, pNode->high_, *pNode->pValue_);
  }
  return -1;
}

template<class T1, class T2>
int SegRBTree<T1, T2>::addEntry_i(const T1 low, const T1 high, T2& value)
{
  //cache full
  if (full())
  {
    return -1;
  }
  //如果线段起点大于终点,数据非法
  if (low > high)
  {
    return -1;
  }
  if (root_ == NULL)
  {
    root_ = createNode(low, high, NULL);
    if (root_ == NULL)
    {
      return -1;
    }
    return addValue(root_, value);
  }
  SegStack segStack;
  Segment<T1, T2> seg(low, high, root_);
  segStack.push(seg);
  SegRBTreeNode<T1, T2>* pNode = NULL;
  while (!segStack.empty())
  {
    seg = segStack.top();
    segStack.pop();
    pNode = seg.pNode_;
    while (pNode)
    {
      //新线段的起点大于当前节点的终点，把新线段插到节点的右子节点上(线段完全不重合)
      if (seg.low_ > pNode->high_)
      {
        if (pNode->right_)
        {
          pNode = pNode->right_;
          continue;
        }
        pNode = createNode(seg.low_, seg.high_, pNode, Right);
        if (pNode == NULL)
        {
          return -1;
        }
        if (addValue(pNode, value) != 0)
        {
          return -1;
        }
        break;
      }

      //新线段的终点小于当前节点的起点，把新线段插到节点的左子节点上(线段完全不重合)
      if (seg.high_ < pNode->low_)
      {
        if (pNode->left_)
        {
          pNode = pNode->left_;
          continue;
        }
        pNode = createNode(seg.low_, seg.high_, pNode, Left);
        if (pNode == NULL)
        {
          return -1;
        }
        if (addValue(pNode, value) != 0)
        {
          return -1;
        }
        break;
      }

      //当线段起点重合,且线段长度大于等于节点线段
      if ((seg.low_ == pNode->low_) && (seg.high_ >= pNode->high_))
      {
        if (addValue(pNode, value) != 0)
        {
          return -1;
        }
        //如果线段长度大于当前线段,则截断线段,继续处理线段的剩余部分
        if (seg.high_ > pNode->high_)
        {
          seg.low_ = pNode->high_ + 1;
          continue;
        }
        break;
      }

      //当线段终点重合, 且线段长度大于等于节点线段
      if ((seg.high_ == pNode->high_) && (seg.low_ <= pNode->low_))
      {
        if (addValue(pNode, value) != 0)
        {
          return -1;
        }
        //如果线段长度大于当前线段,则截断线段,继续处理线段的剩余部分
        if (seg.low_ < pNode->low_)
        {
          seg.high_ = pNode->low_ - 1;
          continue;
        }
        break;
      }

      //当线段起点重合,且线段长度小于节点线段
      if ((seg.low_ == pNode->low_) && (seg.high_ < pNode->high_))
      {
        //截断当前节点的线段,以当前节点的数据创建新节点并插入到当前节点的右子点
        SegRBTreeNode<T1, T2>* pNewNode = createNode(seg.high_ + 1, pNode->high_, pNode->pValue_, pNode, Right);
        if (pNewNode == NULL)
        {
          return -1;
        }
        pNode->high_ = seg.high_;
        //当前节点剩余部分与线段是完全重合的了,插入新的数据即可
        if (addValue(pNode, value) != 0)
        {
          return -1;
        }
        break;
      }

      //当线段终点重合,且线段长度小于节点线段
      if ((seg.high_ == pNode->high_) && (seg.low_ > pNode->low_))
      {
        //截断当前节点的线段,以当前节点的数据创建新节点并插入到当前节点的左子点
        SegRBTreeNode<T1, T2>* pNewNode = createNode(pNode->low_, seg.low_ - 1, pNode->pValue_, pNode, Left);
        if (pNewNode == NULL)
        {
          return -1;
        }
        pNode->low_ = seg.low_;
        //当前节点剩余部分与线段是完全重合的了,插入新的数据即可
        if (addValue(pNode, value) != 0)
        {
          return -1;
        }
        break;
      }
      //线段的终点小于当前节点线段的终点
      if (seg.high_ < pNode->high_)
      {
        //截断当前节点,以当前节点的数据创建新节点并插入到当前节点的右子点
        SegRBTreeNode<T1, T2>* pNewNode = createNode(seg.high_ + 1, pNode->high_, pNode->pValue_, pNode, Right);
        if (pNewNode == NULL)
        {
          return -1;
        }
        pNode->high_ = seg.high_;
        //继续处理,至此线段树中必有一节点的线段与当前线段终点重合
        continue;
      }
      else
      {
        //线段的终点大于当前节点线段的终点
        //根据当前节点终点,截断当前线段,继续处理当前线段时,线段树中必有一节点的线段与当前线段终点重合
        Segment<T1, T2> seg1(pNode->high_ + 1, seg.high_, pNode);
        segStack.push(seg1);
        seg.high_ = pNode->high_;
        continue;
      }
    }
  }
  return 0;
}

template<class T1, class T2>
int SegRBTree<T1, T2>::addValue(SegRBTreeNode<T1, T2> *pNode, T2& value)
{
  if (pNode)
  {
    //如果当前节点数据为空,需要申请内存
    if (pNode->pValue_ == NULL)
    {
      pNode->pValue_ = new T2(value);
      if (pNode->pValue_ == NULL)
      {
        return -1;
      }
      return 0;
    }
    else
    {
      pNode->pValue_->merge(value);
      return 0;
    }
  }
  return -1;
}

/*!
 * \b author: Peng Futian MediaV
 *
 * \b Date: 2010-05-25
 *
 * \b Description: 查询数据
 *	@param key 查询的key
 *	@param t 返回数据
 *	@param deadline 数据过期时间
 *
 *   @retval true 成功 false 没有查到相关记录
 *
 */
template<class T1, class T2>
bool SegRBTree<T1, T2>::query(const T1 key, T2& t)
{
  T2* result = query(key);
  if (result)
  {
    t.clone(*result);
    return true;
  }
  return false;
}

template<class T1, class T2>
T2* SegRBTree<T1, T2>::query(const T1 key)
{
  SegRBTreeNode<T1, T2>* pNode = root_;
  while (pNode)
  {
    //大于当前线段的终点,继续向右扫搜索
    if (key > pNode->high_)
    {
      pNode = pNode->right_;
      continue;
    }
    //小于当前线段的起点,继续向左扫搜索
    else if (key < pNode->low_)
    {
      pNode = pNode->left_;
      continue;
    }
    else
    {
      //到此,点落在线段上,返回数据
      return pNode->pValue_;
    }
  }
  return NULL;
}

/*!
 * \b author: Peng Futian MediaV
 *
 * \b Date: 2010-05-25
 *
 * \b Description: 复制tree
 *	@param rhs 源数据
 *
 */
template<class T1, class T2>
void SegRBTree<T1, T2>::clone(SegRBTree<T1, T2>& rhs)
{
  tree_clone cloneAction(this);
  cloneAction.execute(rhs);
}

/*!
 * \b author: Peng Futian MediaV
 *
 * \b Date: 2010-05-25
 *
 * \b Description: 在线段中删除指定数据
 *	@param dvDel 需要删除的数据
 *
 */
template<class T1, class T2>
void SegRBTree<T1, T2>::subtract(T2& t2)
{
  tree_subtract subtractAction(this, t2);
  subtractAction.execute();
}

/*!
 * \b author: Peng Futian MediaV
 *
 * \b Date: 2010-05-29
 *
 * \b Description: 清空树,释放所有节点所占用的内存
 */
template<class T1, class T2>
void SegRBTree<T1, T2>::clear()
{
  tree_deleter deleteAction(this);
  deleteAction.execute();
}

template<class T1, class T2>
bool SegRBTree<T1, T2>::equal(const SegRBTree<T1, T2> & rhs) const
{
  if (size_ != rhs.size_)
  {
    return false;
  }
  if (size_ == 0)
  {
    return true;
  }
  SegRBTreeNode<T1, T2>* rhsNode = rhs.first();
  SegRBTreeNode<T1, T2>* lhsNode = first();
  while (lhsNode)
  {
    if (!rhsNode)
    {
      return false;
    }
    if (!lhsNode->equal(*rhsNode))
    {
      return false;
    }
    lhsNode = next(lhsNode);
    rhsNode = rhs.next(rhsNode);
  }
  return true;
}

/*
 Y                     X
 /\                    /\
 X  C <-left  rotate-  A  Y
 /\                        /\
 A  B                      B  C
 */
template<class T1, class T2>
void SegRBTree<T1, T2>::leftRotate(SegRBTreeNode<T1, T2>* x)
{
  SegRBTreeNode<T1, T2>* y = x->right_;
  /* Turn y's left sub-tree into x's right sub-tree */
  x->right_ = y->left_;
  if (y->left_ != NULL)
  {
    y->left_->parent_ = x;
  }
  /* y's new parent was x's parent */
  y->parent_ = x->parent_;
  /* Set the parent to point to y instead of x */
  /* First see whether we're at the root */
  if (x->parent_ == NULL)
  {
    root_ = y;
  }
  else
  {
    if (x == (x->parent_)->left_)
    {
      /* x was on the left of its parent */
      x->parent_->left_ = y;
    }
    else
    {
      /* x must have been on the right */
      x->parent_->right_ = y;
    }
  }
  /* Finally, put x on y's left */
  y->left_ = x;
  x->parent_ = y;
}

/*
 X                     Y
 /\  -right rotate->   /\
 Y  C                  A  X
 /\                        /\
 A  B                      B  C
 */
template<class T1, class T2>
void SegRBTree<T1, T2>::rightRotate(SegRBTreeNode<T1, T2>* x)
{
  SegRBTreeNode<T1, T2>* y = x->left_;
  /* Turn y's right sub-tree into x's left sub-tree */
  x->left_ = y->right_;
  if (y->right_ != NULL)
  {
    y->right_->parent_ = x;
  }
  /* y's new parent was x's parent */
  y->parent_ = x->parent_;
  /* Set the parent to point to y instead of x */
  /* First see whether we're at the root */
  if (x->parent_ == NULL)
  {
    root_ = y;
  }
  else
  {
    if (x == (x->parent_)->right_)
    {
      /* x was on the right of its parent */
      x->parent_->right_ = y;
    }
    else
    {
      /* x must have been on the left */
      x->parent_->left_ = y;
    }
  }
  /* Finally, put x on y's right */
  y->right_ = x;
  x->parent_ = y;
}

/*!
 * \b author: Peng Futian MediaV
 *
 * \b Date: 2010-05-25
 *
 * \b Description: 插入一个新节点后,可能破坏了红黑树的性质,重新平衡红黑树
 *	@param pTree 树的指针
 *	@param pNode 新插入的节点
 *
 */
template<class T1, class T2>
void SegRBTree<T1, T2>::insertRebalance(SegRBTreeNode<T1, T2>* pNode)
{
  //uncle node
  SegRBTreeNode<T1, T2>* y = NULL;
  //new Node
  SegRBTreeNode<T1, T2>* x = pNode;
  while ((x != root_) && (x->parent_->colour_ == RBColour::Red))
  {
    if (x->parent_ == x->parent_->parent_->left_)
    {
      /* If x's parent is a left, y is x's right 'uncle' */
      y = x->parent_->parent_->right_;
      if (y && (y->colour_ == RBColour::Red))
      {
        /* case 1 - change the colour_s */
        x->parent_->colour_ = RBColour::Black;
        y->colour_ = RBColour::Black;
        x->parent_->parent_->colour_ = RBColour::Red;
        /* Move x up the tree */
        x = x->parent_->parent_;
      }
      else
      {
        /* y is a black node */
        if (x == x->parent_->right_)
        {
          /* and x is to the right_ */
          /* case 2 - move x up and rotate */
          x = x->parent_;
          leftRotate(x);
        }
        /* case 3 */
        x->parent_->colour_ = RBColour::Black;
        x->parent_->parent_->colour_ = RBColour::Red;
        rightRotate(x->parent_->parent_);
      }
    }
    else
    {
      /* If x's parent is a right, y is x's left 'uncle' */
      y = x->parent_->parent_->left_;
      if (y && (y->colour_ == RBColour::Red))
      {
        /* case 1 - change the colour_s */
        x->parent_->colour_ = RBColour::Black;
        y->colour_ = RBColour::Black;
        x->parent_->parent_->colour_ = RBColour::Red;
        /* Move x up the tree */
        x = x->parent_->parent_;
      }
      else
      {
        /* y is a black node */
        if (x == x->parent_->left_)
        {
          /* and x is to the left_ */
          /* case 2 - move x up and rotate */
          x = x->parent_;
          rightRotate(x);
        }
        /* case 3 */
        x->parent_->colour_ = RBColour::Black;
        x->parent_->parent_->colour_ = RBColour::Red;
        leftRotate(x->parent_->parent_);
      }
    }
  }
  /* Colour the root_ black */
  root_->colour_ = RBColour::Black;
}

/*!
 * \b author: Peng Futian MediaV
 *
 * \b Date: 2010-05-25
 *
 * \b Description: 删除一个节点
 *	@param pTree 树的指针
 *	@param x 需要删除的节点指针
 *
 *	@retval 指向下一个节点
 */
template<class T1, class T2>
void SegRBTree<T1, T2>::erase(SegRBTreeNode<T1, T2>* x)
{
  if (x == NULL)
  {
    return;
  }
  //x的继承者
  SegRBTreeNode<T1, T2>* y = NULL;
  SegRBTreeNode<T1, T2>* parent = NULL;
  RBColour colour;
  if (!x->left_)
  {
    //x只有一个右子树,取其右子树作为x的继承者
    y = x->right_;
  }
  else if (!x->right_)
  {
    //x只有一个左子树,取其左子树作为x的继承者
    y = x->left_;
  }
  //当x有两个儿子时,转换为只有一个儿子的情形来处理,对于这种情形,我们总是取右子树做为继承者
  else
  {
    //取左子树或左子树的最右子树
    y = x->right_;
    while (y->left_)
    {
      y = y->left_;
    }

    //将x与y的内容互换
    x->swapData(y);
    //现在我们需要删除的是y,将x的指针指向y
    x = y;
    //这里y只可能有一个右子树,y的右子树作为删除节点的继承者,将y指向y的右子树
    y = x->right_;
  }
  parent = x->parent_;
  colour = x->colour_;
  //更新y的父节点
  if (y)
  {
    y->parent_ = parent;
  }
  //将父节点的指针指向y
  //如果父节点为空,则将root指向y
  if (parent == NULL)
  {
    root_ = y;
  }
  else
  {
    if (x == parent->left_)
    {
      parent->left_ = y;
    }
    else
    {
      parent->right_ = y;
    }
  }

  //只有删除黑颜色的点,才需要重平衡红黑树
  if (colour == RBColour::Black)
  {
    //在被删除节点是黑色而它的儿子是红色的时候。如果只是去除这个黑色节点，用它的红色儿子顶替上来的话，
    //会破坏属性5，但是如果我们重绘它的儿子为黑色，则曾经通过它的所有路径将通过它的黑色儿子，
    //这样可以继续保持属性5。
    if (y && (y->colour_ == RBColour::Red))
    {
      y->colour_ = RBColour::Black;
    }
    else
    {
      deleteRebalance(y, parent);
    }
  }
  delete x;
  if (size_ > 0)
  {
    size_--;
  }
}

/*!
 * \b author: Peng Futian MediaV
 *
 * \b Date: 2010-05-25
 *
 * \b Description: 删除一个节点后,可能破坏了红黑树的性质,重新平衡红黑树
 如果删除一个红色的节点，不用做任何操作，红黑树的任何属性都不会被破坏。当删除一个黑色节点的时候，
 会出现3个问题：

 1. 如果删除了根且一个红色的节点做了新的根，则属性1就会被破坏；

 2. 该节点的所有祖辈的black height都会少1；

 3. 如果该节点的父亲和孩子都是红色的，那么删除这个节点还可能引起连红的情况；

 *	@param pTree 树的指针
 *	@param x 是删除节点的继承者
 *	@param parent 是x的父节点
 *
 */
template<class T1, class T2>
void SegRBTree<T1, T2>::deleteRebalance(SegRBTreeNode<T1, T2>* x, SegRBTreeNode<T1, T2>* parent)
{
  //x的兄弟
  SegRBTreeNode<T1, T2>* y = NULL;

  while ((x != root_) && (!x || (x->colour_ == RBColour::Black)))
  {
    if (x == parent->left_)
    {
      y = parent->right_;
      //y 是红色。在这种情况下我们在x的父亲上做左旋转，把红色兄弟转换成x的祖父。
      //我们接着对调 x 的父亲和祖父的颜色。尽管所有的路径仍然有相同数目的黑色节点，
      //现在 x 有了一个黑色的兄弟和一个红色的父亲
      if (y && (y->colour_ == RBColour::Red))
      {
        // Case 1: y is Red. We change the color of
        // x's parent and y, then perform a left rotate on
        // parent of x, then ye can  enter 2, 3 or 4.
        y->colour_ = RBColour::Black;
        parent->colour_ = RBColour::Red;
        leftRotate(parent);
        y = parent->right_; // Adjust the y to the new sibling of x
      }
      if ((!y->left_ || (y->left_->colour_ == RBColour::Black)) && (!y->right_ || (y->right_->colour_
          == RBColour::Black)))
      {
        // Case 2: y is Black and both left_ and right_
        // children of y is black
        y->colour_ = RBColour::Red;
        if (parent->colour_ == RBColour::Red)
        {
          //y 和 y 的儿子都是黑色，但是 x 的父亲是红色。在这种情况下，
          //我们简单的交换 x 的兄弟和父亲的颜色。这不影响不通过 x 的路径的黑色节点的数目，
          //但是它在通过 x 的路径上对黑色节点数目增加了一，添补了在这些路径上删除的黑色节点。
          parent->colour_ = RBColour::Black;
          x = root_;
        }
        else
        {
          //x 的父亲、y 和 y 的儿子都是黑色的。在这种情况下，我们简单的重绘 y 为红色。
          //结果是通过y的所有路径，它们就是以前不通过 x 的那些路径，都少了一个黑色节点。
          //因为删除 x 的初始的父亲使通过 x 的所有路径少了一个黑色节点，这使事情都平衡了起来。
          //但是，通过 parent 的所有路径现在比不通过 parent 的路径少了一个黑色节点
          x = parent; // Shift x up a layer and re-enter the loop
          parent = parent->parent_;
        }
      }
      else if (!y->right_ || (y->right_->colour_ == RBColour::Black))
      {
        // Case 3: y is Black and the left child of y is Red, the
        // right child of y is Black
        y->colour_ = RBColour::Red;
        y->left_->colour_ = RBColour::Black;
        rightRotate(y);
        y = y->parent_;
      }
      else
      {
        // Case 4: y is Black and the right child of y is Red.
        // After some color change and a left rotation, the tree
        // is balanced again.
        y->colour_ = y->parent_->colour_;
        parent->colour_ = RBColour::Black;
        y->right_->colour_ = RBColour::Black;
        leftRotate(parent);
        x = root_;
      }
    }
    else
    {
      y = parent->left_;
      if (y && (y->colour_ == RBColour::Red))
      {
        // Case 1: y is Red. We change the color of
        // x's parent_ and y, then perform a right_ rotate on
        // parent_ of x, then ye can  enter 2, 3 or 4.
        y->colour_ = RBColour::Black;
        parent->colour_ = RBColour::Red;
        rightRotate(parent);
        // Adjust the y to the ney sibling of x
        y = parent->left_;
      }
      if ((!y->right_ || (y->right_->colour_ == RBColour::Black)) && (!y->left_ || (y->left_->colour_
          == RBColour::Black)))
      {
        // Case 2: y is Black and both right and left
        // children of y is black
        y->colour_ = RBColour::Red;
        if (parent->colour_ == RBColour::Red)
        {
          //y 和 y 的儿子都是黑色，但是 x 的父亲是红色。在这种情况下，
          //我们简单的交换 x 的兄弟和父亲的颜色。这不影响不通过 x 的路径的黑色节点的数目，
          //但是它在通过 x 的路径上对黑色节点数目增加了一，添补了在这些路径上删除的黑色节点。
          parent->colour_ = RBColour::Black;
          x = root_;
        }
        else
        {
          // Shift x up a layer and re-enter the loop
          x = parent;
          parent = parent->parent_;
        }
      }
      else if (!y->left_ || (y->left_->colour_ == RBColour::Black))
      {
        // Case 3: y is Black and the right child of y is Red, the
        // left child of y is Black
        y->colour_ = RBColour::Red;
        if (y->right_)
        {
          y->right_->colour_ = RBColour::Black;
        }
        leftRotate(y);
        y = y->parent_;
      }
      else
      {
        // Case 4: y is Black and the left child of y is Red.
        // After some color change and a right rotation, the tree
        // is balanced again.
        y->colour_ = y->parent_->colour_;
        parent->colour_ = RBColour::Black;
        if (y->left_)
        {
          y->left_->colour_ = RBColour::Black;
        }
        rightRotate(parent);
        x = root_;
      }
    }
  }
  if (root_)
  {
    root_->colour_ = RBColour::Black;
  }
}

template<class T1, class T2>
SegRBTreeNode<T1, T2>* SegRBTree<T1, T2>::first() const
{
  SegRBTreeNode<T1, T2>* result = root_;
  if (!result)
  {
    return NULL;
  }
  while (result->left_)
  {
    result = result->left_;
  }
  return result;
}

template<class T1, class T2>
SegRBTreeNode<T1, T2>* SegRBTree<T1, T2>::last() const
{
  SegRBTreeNode<T1, T2>* result = root_;
  if (!result)
  {
    return NULL;
  }
  while (result->right_)
  {
    result = result->right_;
  }
  return result;
}

template<class T1, class T2>
SegRBTreeNode<T1, T2>* SegRBTree<T1, T2>::next(const SegRBTreeNode<T1, T2>* pNode) const
{
  if (!pNode)
  {
    return NULL;
  }

  /* If we have a right-hand child, go down and then left as far
   as we can. */
  if (pNode->right_)
  {
    pNode = pNode->right_;
    while (pNode->left_)
    {
      pNode = pNode->left_;
    }
    return (SegRBTreeNode<T1, T2>*) pNode;
  }
  SegRBTreeNode<T1, T2>* parent = pNode->parent_;
  /* No right-hand children.  Everything down and left is
   smaller than us, so any 'next' node must be in the general
   direction of our parent. Go up the tree; any time the
   ancestor is a right-hand child of its parent, keep going
   up. First time it's a left-hand child of its parent, said
   parent is our 'next' node. */
  while ((parent = pNode->parent_) && (pNode == parent->right_))
  {
    pNode = parent;
  }
  return parent;
}

template<class T1, class T2>
SegRBTreeNode<T1, T2>* SegRBTree<T1, T2>::prev(const SegRBTreeNode<T1, T2>* pNode) const
{
  if (!pNode)
  {
    return NULL;
  }
  SegRBTreeNode<T1, T2>* parent = pNode->parent_;

  /* If we have a left-hand child, go down and then right as far
   as we can. */
  if (pNode->left_)
  {
    pNode = pNode->left_;
    while (pNode->right_)
    {
      pNode = pNode->right_;
    }
    return (SegRBTreeNode<T1, T2>*) pNode;
  }

  /* No left-hand children. Go up till we find an ancestor which
   is a right-hand child of its parent */
  while ((parent = pNode->parent_) && (pNode == parent->left_))
  {
    pNode = parent;
  }
  return parent;
}


