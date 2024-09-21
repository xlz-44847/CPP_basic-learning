#pragma once
#pragma once
#include<iostream>
#include<assert.h>

using namespace std;

namespace RBTree {
	//定义枚举类型来标识红、黑两种颜色
	enum color {
		RED,
		BLACK
	};

	//红黑树的结点
	template<class K, class V>
	struct RBTreeNode {
		pair<K, V> _pair;
		RBTreeNode<K, V>* _left;
		RBTreeNode<K, V>* _right;
		RBTreeNode<K, V>* _parent;
		color _color;

		RBTreeNode(pair<K, V> kv)
			:_pair(kv)
			, _left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			//红黑树要求每条路径的黑色节点数目相等，所以默认插入红色节点更加合理
			, _color(RED)
		{}
	};

	template<class K, class V>
	class RBTree {
		typedef RBTreeNode<K, V> RBNode;

	public:
		//无参构造
		RBTree()
			:_root(nullptr)
		{}

		//拷贝构造
		RBTree(const RBTree<K, V>& rb)
		{
			_root = copy(rb._root);
		}
	private:
		RBNode* copy(RBNode* root)
		{
			if (root == nullptr) return nullptr;
			RBNode* newnode = new RBNode(root->_pair);
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
		RBTree<K, V>& operator=(const RBTree<K, V> rb)
		{
			swap(_root, rb->_root);
			return *this;
		}

		//插入
		bool Insert(const pair<K, V>& kv)
		{
			//第一个结点特殊处理
			if (_root == nullptr)
			{
				_root = new RBNode(kv);
				_root->_color = BLACK;
				return true;
			}

			RBNode* cur = _root;
			RBNode* parent = nullptr;
			while (cur)
			{
				if (cur->_pair.first > kv.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_pair.first < kv.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}
			cur = new RBNode(kv);
			if (parent->_pair.first > kv.first)
			{
				parent->_left = cur;
				cur->_parent = parent;
			}
			else
			{
				parent->_right = cur;
				cur->_parent = parent;
			}

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
				//在解决连续红色的问题时，也要兼顾到黑色节点数目相同这一规则
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
						//左右逆位——左右双旋，cur变黑，g变红
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
						//右左逆位——右左双旋，cur变黑，g变红
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
			return true;
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