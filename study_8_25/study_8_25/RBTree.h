#pragma once

#include<iostream>
#include<assert.h>

using namespace std;

//set和map的底层容器都是红黑树，为了使得红黑树可以适配两种不同的容器，我们需要对模板的一些细节做一些优化

namespace RBTree {
	enum color {
		RED,
		BLACK
	};

	//红黑树的结点
	//由于不确定所适配的是什么容器（set是K，map是KV），因此使用一个模板参数T进行代替
	template<class T>
	struct RBTreeNode {
		T _val;
		RBTreeNode<T>* _left;
		RBTreeNode<T>* _right;
		RBTreeNode<T>* _parent;
		color _color;

		RBTreeNode(T val)
			:_val(val)
			, _left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			, _color(RED)
		{}
	};

	//对于红黑树，我们需要为它写一个迭代器类型
	template<class T, class Ptr, class Ref>
	class RBTreeIterator {
	private:
		typedef RBTreeNode<T> Node;
		Node* _node;
		Node* _root;
		typedef RBTreeIterator<T, Ptr, Ref> self;

	public:
		RBTreeIterator(Node* node, Node* root)
			:_node(node)
			, _root(root)
		{}
		self& operator++()
		{
			//采取中序遍历（左根右）的策略，那么对于++而言，找到下一位置是谁即可
			//分情况讨论：
			//基本思路就是看当前子树是否遍历完成，有右树就代表没有完成，需要继续处理右树。如果完成就向上找，自己属于哪一棵左子树，从而继续遍历根节点和右树
			
			//①如果发现当前结点有右孩子，那么说明下一个结点是右子树的最左孩子
			if (_node->_right)
			{
				Node* cur = _node->_right;
				while (cur->_left)
				{
					cur = cur->_left;
				}
				_node = cur;
			}
			else
			{
				Node* cur = _node;
				Node* parent = _node->_parent;
				
				//②如果发现当前结点是父结点的左孩子，那么下一个结点就是应该是该结点的父亲
				//③如果发现当前结点没有右子树，那么说明下个结点就是向上找，直到找到是左孩子的父结点
				while (parent && cur == parent->_right)
				{
					cur = parent;
					parent = parent->_parent;
				}
				_node = parent;
			}
			return *this;
		}
		self& operator--()
		{
			//相当于++操作的逆序，也就成了右根左的遍历顺序了
			//基本思路：看当前子树是否遍历完成，有左树就代表没有完成，需要继续处理左树。如果完成就向上找，自己属于哪一棵右子树，从而继续遍历根节点和左树

			//对于--操作而言，起点可以是end()，即一个空指针，当从空指针开始--时，需要找到中序遍历的最后一个节点，即最右节点,因此需要知道根节点，所以迭代器需要新增一个root成员
			//但在实际的std库中，红黑树具有一个头结点，所以迭代器不会走到空，也就不需要这个root成员了
			if (_node == nullptr)
			{
				Node* cur = _root;
				while (cur->_right)
				{
					cur = cur->_right;
				}
				_node = cur;
			}
			//①如果发现当前结点有左孩子，那么说明下一个结点是左子树的最右孩子
			else if (_node->_left)
			{
				Node* cur = _node->left;
				while (cur->_right)
				{
					cur = cur->_right;
				}
				_node = cur;
			}
			else
			{
				Node* cur = _node;
				Node* parent = _node->_parent;

				//②如果发现当前结点是父结点的右孩子，那么下一个结点就是应该是该结点的父亲
				//③如果发现当前结点没有左子树，那么说明下个结点就是向上找，直到找到是右孩子的父结点
				while (parent && cur == parent->_left)
				{
					cur = parent;
					parent = parent->_parent;
				}
				_node = parent;
			}
			return *this;
		}
		Ref operator*()
		{
			return _node->_val;
		}
		Ptr operator->()
		{
			return &(_node->_val);
		}
		bool operator==(const self& it)
		{
			return it._node == _node;
		}
		bool operator!=(const self& it)
		{
			return it._node != _node;
		}
	};

	template<class K, class T, class KeyOfT>
	//模板参数：
	// K——key的类型
	// T——value的类型，对于set而言T与K是相同的，对于map而言T就是pair<key，value>
	// KeyOfT——取得key值的仿函数
	class RBTree {
		typedef RBTreeNode<T> RBNode;

	public:
		//无参构造
		RBTree()
			:_root(nullptr)
		{}

		//拷贝构造
		RBTree(const RBTree& rb)
		{
			_root = copy(rb._root);
		}
	private:
		RBNode* copy(RBNode* root)
		{
			if (root == nullptr) return nullptr;
			RBNode* newnode = new RBNode(root->_val);
			newnode->_left = copy(root->_left);
			newnode->_right = copy(root->_right);
			return newnode;
		}

	public:
		//析构函数
		~RBTree()
		{
			destroy(_root);
			_root = nullptr;
		}
	private:
		void destroy(RBNode* root)
		{
			if (root == nullptr) return;
			destroy(root->_left);
			destroy(root->_right);
			delete root;
		}

	public:
		//赋值重载操作符
		RBTree& operator=(const RBTree rb)
		{
			swap(_root, rb->_root);
			return *this;
		}

		//迭代器
	public:
		typedef RBTreeIterator<T, T*, T&> iterator;
		typedef RBTreeIterator<T, const T*, const T&> constiterator;
		iterator begin()
		{
			RBNode* cur = _root;
			while (cur && cur->_left)
			{
				cur = cur->_left;
			}
			return iterator(cur, _root);
		}
		iterator end()
		{
			return iterator(nullptr, _root);
		}
		constiterator cbegin()
		{
			RBNode* cur = _root;
			while (cur && cur->_left)
			{
				cur = cur->_left;
			}
			return constiterator(cur, _root);
		}
		constiterator cend()
		{
			return { nullptr,_root };
		}

		//插入
		//在标准库中，insert返回的实际上是pair<iterator,bool>,可以通过库函数make_pair(T1 x,T2 y)来创建pair
		pair<iterator, bool> insert(const T& data)
		{
			//第一个结点特殊处理
			if (_root == nullptr)
			{
				_root = new RBNode(data);
				_root->_color = BLACK;
				return make_pair(iterator(_root, _root), true);
			}

			RBNode* cur = _root;
			RBNode* parent = nullptr;
			//对于set和map，它们取出key值的方法是不同的
			//set的key和value相同，就是传入的参数data，因此直接使用data既可以拿到key值
			//而map的key值不同，它传入的data是一个结构体pair，需要通过pair.first的形式来拿到key值
			//可见面对这样同种目的但操作不同的情况，就需要通过仿函数来解决了
			//
			//以红黑树为底层的容器，需要提供对应的仿函数来完成取得key值的功能，而在红黑树中，只需要使用即可
			KeyOfT Getkey;

			while (cur)
			{

				if (Getkey(cur->_val) > Getkey(data))
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (Getkey(cur->_val) < Getkey(data))
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return make_pair(iterator(cur,_root),false);
				}
			}
			cur = new RBNode(data);
			if (Getkey(parent->_val) > Getkey(data))
			{
				parent->_left = cur;
				cur->_parent = parent;
			}
			else
			{
				parent->_right = cur;
				cur->_parent = parent;
			}
			RBNode* ret = cur;
			//调整红黑树颜色
			//红黑树规则：
			// ①根结点颜色一定是黑色
			// ②不能出现连续的红结点，即红结点的孩子一定是黑色
			// ③各条路径（根结点->叶子结点）上的黑色节点数目相同
			// ④叶子结点（此处认为是空结点）颜色为黑色
            //在这样的规则限制下，不难发现红黑树最长路径一定小于最短路径的二倍这个特征
			
			//当违反了红黑树规则才需要调整红黑树颜色
			//插入新的结点时，选择插入红色节点可能违反不能有连续的红色节点的规则；选择插入黑色节点则必然会违反黑色节点数目相同的规则
			//因此两害相权取其轻，选择插入红色节点，因此我们主要处理的就是连续红结点的问题
			//于是连续的两个节点：cur和p都是红色的，而u作为p的兄弟节点决定了调整方式，而在调整中受影响的则是p和u的父结点g
			while (parent && parent->_color == RED)
			{
				//根据形式的不同，一般分为三类处理
				//在解决连续红色的问题时，也要兼顾到褐色节点数目相同这一规则
				RBNode* grandparent = parent->_parent;
				RBNode* uncle = parent == grandparent->_left ? grandparent->_right : grandparent->_left;
				//①u为红色（p、u均为红）
				//p、u同时变为黑色，g变为红色，因为g是红色，因此需要继续向上检查
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					grandparent->_color = RED;
					parent = grandparent->_parent;
					cur = grandparent;
				}
				//②u为黑色或不存在，而g、p和cur是顺位（左左或右右）
				//此时单纯的变色会使得p子树和u子树路径黑色节点数目不同（因为在修改p为黑，u本就为黑，u相较p黑色节点少一个）
				//为了可以顺利变色，我们首先要旋转，红色的p成为了子树的根，黑色的g成为了u这棵树的父结点，此时可以证明只需要p变为黑，g变为红即可
				//旋转操作就是AVL树中的左右单旋

				//③u为黑色或不存在，而g、p和cur是逆位（左右或右左）
				//此时只需要将p结点左旋或右旋一次即可形成如②的情况，因此这种情况使用双旋即可
				else
				{
					if (parent == grandparent->_left)
					{
						//左左顺位——右旋，p变黑，g变红
						if (cur == parent->_left)
						{
							RotateR(grandparent);
						}
						//左右逆位——左右双旋，p变黑，g变红
						else
						{
							RotateLR(grandparent);
						}
					}
					else
					{
						//右右顺位——左旋，p变黑，g变红
						if (cur == parent->_right)
						{
							RotateL(grandparent);
						}
						//右左逆位——右左双旋，p变黑，g变红
						else
						{
							RotateRL(grandparent);
						}
					}
					//由于②③结果的子树根结点都是黑色因此不会影响上一层，无需向上检查
					break;
				}
			}
			//根结点有可能变色，需要修改
			_root->_color = BLACK;
			return make_pair(iterator(ret, _root), true);
		}

		iterator find(const K& key)
		{
			RBNode* cur = _root;
			KeyOfT Getkey;

			while (cur)
			{
				if (key > Getkey(cur->_val))
				{
					cur = cur->_right;
				}
				else if (key < Getkey(cur->_val))
				{
					cur = cur->_left;
				}
				else
				{
					return iterator(cur, _root);
				}
			}
			return iterator(nullptr, _root);
		}

	private:
		void RotateL(RBNode* grandparent)
		{
			RBNode* subR = grandparent->_right;
			RBNode* subRL = subR->_left;

			//结点链接三组：subR和grandparent、grandparent和sunRL、grandparent->_parent和subR
			subR->_left = grandparent;
			grandparent->_right = subRL;
			if (grandparent->_parent == nullptr)
			{
				_root = subR;
			}
			else if (grandparent->_parent->_left == grandparent)
			{
				grandparent->_parent->_left = subR;
			}
			else
			{
				grandparent->_parent->_right = subR;
			}

			subR->_parent = grandparent->_parent;
			grandparent->_parent = subR;
			if (subRL)	//右左子树为空树
				subRL->_parent = grandparent;

			//修改颜色：p变黑，g变红
			subR->_color = BLACK;
			grandparent->_color = RED;
		}

		void RotateR(RBNode* grandparent)
		{
			RBNode* subL = grandparent->_left;
			RBNode* subLR = subL->_right;

			//结点链接三组：subL和grandparent、grandparent和sunLR、grandparent->_parent和subL
			subL->_right = grandparent;
			grandparent->_left = subLR;
			if (grandparent->_parent == nullptr)
			{
				_root = subL;
			}
			else if (grandparent->_parent->_left == grandparent)
			{
				grandparent->_parent->_left = subL;
			}
			else
			{
				grandparent->_parent->_right = subL;
			}

			subL->_parent = grandparent->_parent;
			grandparent->_parent = subL;
			if (subLR)	//左右子树为空树
				subLR->_parent = grandparent;

			//修改颜色：p变黑，g变红
			subL->_color = BLACK;
			grandparent->_color = RED;
		}

		//左右双旋
		void RotateLR(RBNode* grandparent)
		{
			RBNode* subL = grandparent->_left;
			RBNode* subLR = grandparent->_left->_right;

			//只需要旋转，颜色最后指定
			RotateL(subL);
			RotateR(grandparent);

			//修改颜色：cur变黑，g变红
			subLR->_color = BLACK;
			grandparent->_color = RED;
		}

		//右左双旋
		void RotateRL(RBNode* grandparent)
		{
			RBNode* subR = grandparent->_right;
			RBNode* subRL = grandparent->_right->_left;

			//只需要旋转，颜色最后指定
			RotateR(subR);
			RotateL(grandparent);

			//修改颜色：cur变黑，g变红
			subRL->_color = BLACK;
			grandparent->_color = RED;
		}
	public:
		void Inorder()
		{
			_Inorder(_root);
			cout << endl;
		}
	private:
		void _Inorder(RBNode* root)
		{
			if (root == nullptr) return;
			_Inorder(root->_left);
			cout << root->_pair.first << ' ' << root->_pair.second << endl;
			_Inorder(root->_right);
		}


	public:
		//检验函数
		typedef RBNode* PNode;
		bool IsValidRBTree()
		{
			PNode pRoot = GetRoot();
			// 空树也是红黑树
			if (nullptr == pRoot)
				return true;
			// 检测根节点是否满足情况
			if (BLACK != pRoot->_color)
			{
				cout << "违反红黑树性质二：根节点必须为黑色" << endl;
				return false;
			}
			// 获取任意一条路径中黑色节点的个数
			size_t blackCount = 0;
			PNode pCur = pRoot;
			while (pCur)
			{
				if (BLACK == pCur->_color)
					blackCount++;
				pCur = pCur->_left;
			}
			// 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
			size_t k = 0;
			return _IsValidRBTree(pRoot, k, blackCount);
		}
		bool _IsValidRBTree(PNode pRoot, size_t k, const size_t blackCount)
		{
			//走到null之后，判断k和black是否相等
			if (nullptr == pRoot)
			{
				if (k != blackCount)
				{
					cout << "违反性质四：每条路径中黑色节点的个数必须相同" << endl;
					return false;
				}
				return true;
			}
			// 统计黑色节点的个数
			if (BLACK == pRoot->_color)
				k++;
			// 检测当前节点与其双亲是否都为红色
			PNode pParent = pRoot->_parent;
			if (pParent && RED == pParent->_color && RED == pRoot->_color)
			{
				cout << "违反性质三：没有连在一起的红色节点" << endl;
				return false;
			}
			return _IsValidRBTree(pRoot->_left, k, blackCount) &&
				_IsValidRBTree(pRoot->_right, k, blackCount);
	}
	private:
		RBNode* GetRoot()
		{
			return _root;
		}

	private:
		RBNode* _root;
	};
}