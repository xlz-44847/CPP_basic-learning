#pragma once
#include<iostream>
#include<assert.h>

using namespace std;

namespace AVLTree
{
	//AVL树的结点
	template<class K, class V>
	struct AVLTreeNode {
		//pair是一个结构体类型，它将一对值组合在一起，作为一个值
		//pair<T1，T2>作为结构体模板，T1和T2分别表示一对的两个类型
		//可以通过.first和.second来访问两个值
		pair<K, V> _pair;
		AVLTreeNode<K, V>* _left;
		AVLTreeNode<K, V>* _right;
		AVLTreeNode<K, V>* _parent;
		int _bf;//平衡因子=右子树高度-左子树高度

		AVLTreeNode(pair<K, V> kv)
			:_pair(kv)
			, _left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			, _bf(0)
		{}
	};

	template<class K, class V>
	class AVLTree {
		typedef AVLTreeNode<K, V> AVLNode;
	public:
		//无参构造
		AVLTree()
			:_root(nullptr)
		{}

		//拷贝构造
		AVLTree(const AVLTree<K, V>& avl)
		{
			_root = copy(avl._root);
		}
	private:
		AVLNode* copy(AVLNode* root)
		{
			if (root == nullptr) return nullptr;
			AVLNode* newnode = new AVLNode(root->_pair);
			newnode->_left = copy(root->_left);
			newnode->_right = copy(root->_right);
			return newnode;
		}

		//赋值重载
	public:
		AVLTree<K, V>& operator=(const AVLTree<K, V> avl)
		{
			swap(this->_root, avl._root);
			return *this;
		}

		//析构
		~AVLTree()
		{
			Destroy(_root);
			_root = nullptr;
		}
	private:
		void Destroy(AVLNode* root)
		{
			if (root == nullptr) return;
			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
		}

		//插入
	public:
		bool Insert(const pair<K, V>& kv)
		{
			//第一个结点特殊处理
			if (_root == nullptr)
			{
				_root = new AVLNode(kv);
				return true;
			}

			AVLNode* cur = _root;
			AVLNode* parent = nullptr;
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
					return false;
			}
			cur = new AVLNode(kv);
			if (parent->_pair.first > kv.first)
				parent->_left = cur;
			else
				parent->_right = cur;
			cur->_parent = parent;
			
			//更新平衡因子
			while (parent)
			{
				//parent的平衡因子：在左插入时-1，右插入时+1
				if (cur == parent->_left)
					parent->_bf--;
				else
					parent->_bf++;

				//①parent的平衡因子0->±1，表示结点插入在左右任意一边，该子树实际上新增了一层，需要向上更新
				if (parent->_bf == 1 || parent->_bf == -1)
				{
					//因为插入结点使得子树变高了一层，所以祖先也可以根据左插入-1，右插入+1的规则进行平衡因子的修改，所以变量向上传递一层即可
					cur = parent;
					parent = parent->_parent;
				}
				//②parent的平衡因子±1->0，表示结点插入在空缺的一边，没有新增层数，不需要向上更新
				else if (parent->_bf == 0)
				{
					break;
				}
				//③parent的平衡因子±1->±2，表示结点插入在已经盈余的一边，不再满足AVL树的要求，需要旋转处理
				else
				{
					//旋转处理
					//左单旋：本就突出的右子树的右子树插入新结点，形成RR的形状破坏平衡
					//以subR为中心，subR的父结点parent为悬臂左旋，那么parent与其左子树将成为subR的左子树，而subR原先的左子树subRL将成为旋转下来的父结点的右子树
					//这种RR的情况下，parent的平衡因子为2，subR的平衡因子为1
					if (parent->_bf == 2 && cur->_bf == 1)
					{
						RotateL(parent);
					}
					//右单旋：本就突出的左子树的左子树插入新结点，形成LL的形状破坏平衡
					//以subL为中心，subL的父结点parent为悬臂右旋，那么parent与其右子树将成为subL的右子树，而subL原先的右子树subLR将成为旋转下来的父结点的左子树
					else if (parent->_bf == -2 && cur->_bf == -1)
					{
						RotateR(parent);
					}
					//左右双旋：本来突出的左子树的右子树插入新结点，形成LR的形状破坏平衡
					//对于这种情况，需要先左旋再右旋，左旋针对subL，完成后再对parent右旋
					else if (parent->_bf == -2 && cur->_bf == 1)
					{
						RotateLR(parent);
					}
					//右左双旋：本来突出的右子树的左子树插入新结点，形成RL的形状破坏平衡
					//对于这种情况，需要先右旋再左旋，右旋针对subR，完成后再对parent左旋
					else if(parent->_bf == 2 && cur->_bf == -1)
					{
						RotateRL(parent);
					}
					else
					{
						assert(0);
					}

					//因为旋转情况的判断与执行发生在插入新结点后的子树，在旋转后，该子树的高度与未插入结点时的高度一致，因此无需对子树的祖先进行平衡因子修正，可以直接结束循环
					break;
				}
			}
			return true;
		}
	private:
		//左单旋
		void RotateL(AVLNode* parent)
		{
			AVLNode* subR = parent->_right;
			AVLNode* subRL = subR->_left;
			
			//结点链接三组：subR和parent、parent和sunRL、parent->_parent和subR
			subR->_left = parent;
			parent->_right = subRL;
			if (parent->_parent == nullptr)
			{
				_root = subR;
			}
			else if (parent->_parent->_left == parent)
			{
				parent->_parent->_left = subR;
			}
			else
			{
				parent->_parent->_right = subR;
			}

			subR->_parent = parent->_parent;
			parent->_parent = subR;
			if (subRL)	//右左子树为空树
				subRL->_parent = parent;

			//平衡因子修正
			//可以证明，在左旋处理后，左右subR和parent结点的平衡因子均为0，而且左旋后的子树与插入前相比高度不变，所以该子树的祖先结点平衡因子均不变
			subR->_bf = parent->_bf = 0;
		}

		//右单旋
		void RotateR(AVLNode* parent)
		{
			AVLNode* subL = parent->_left;
			AVLNode* subLR = subL->_right;

			//结点链接三组：subL和parent、parent和sunLR、parent->_parent和subL
			subL->_right = parent;
			parent->_left = subLR;
			if (parent->_parent == nullptr)
			{
				_root = subL;
			}
			else if (parent->_parent->_left == parent)
			{
				parent->_parent->_left = subL;
			}
			else
			{
				parent->_parent->_right = subL;
			}

			subL->_parent = parent->_parent;
			parent->_parent = subL;
			if (subLR)	//左右子树为空树
				subLR->_parent = parent;

			//平衡因子修正
			//可以证明，在右旋处理后，左右subL和parent结点的平衡因子均为0，而且右旋后的子树与插入前相比高度不变，所以该子树的祖先结点平衡因子均不变
			subL->_bf = parent->_bf = 0;
		}

		//左右双旋
		void RotateLR(AVLNode* parent)
		{
			AVLNode* subL = parent->_left;
			AVLNode* subLR = parent->_left->_right;

			//因为双旋调用单旋的函数，会改变平衡因子。单旋考虑的仅是需要单旋情况的平衡因子改变，我们此处只需要单旋的旋转操作而不接受其平衡因子的改变
			//所以在之后会重新进行双旋操作的平衡因子修正，但是为了确定修正方案，并且单旋会改变平衡因子，所以需要提前记录可以作为标识的平衡因子作为分支语句的条件
			int bf = subLR->_bf;

			RotateL(subL);
			RotateR(parent);

			//平衡因子修正
			//①subLR的左子树插入新结点——subLR的平衡因子为-1
			if (bf == -1)
			{
				parent->_bf = 1;
				subL->_bf = subLR->_bf = 0;
			}
			//②subLR的右子树插入新结点——subLR的平衡因子为1
			else if (bf == 1)
			{
				parent->_bf = subLR->_bf = 0;
				subL->_bf = -1;
			}
			//③subLR自身是被插入的新结点——subLR的平衡因子为0
			else
			{
				parent->_bf = subL->_bf = subLR->_bf = 0;
			}
		}
		
		//右左双旋
		void RotateRL(AVLNode* parent)
		{
			AVLNode* subR = parent->_right;
			AVLNode* subRL = parent->_right->_left;

			//因为双旋调用单旋的函数，会改变平衡因子。单旋考虑的仅是需要单旋情况的平衡因子改变，我们此处只需要单旋的旋转操作而不接受其平衡因子的改变
			//所以在之后会重新进行双旋操作的平衡因子修正，但是为了确定修正方案，并且单旋会改变平衡因子，所以需要提前记录可以作为标识的平衡因子作为分支语句的条件
			int bf = subRL->_bf;

			RotateR(subR);
			RotateL(parent);

			//平衡因子修正
			//①subRL的左子树插入新结点——subRL的平衡因子为-1
			if (bf == -1)
			{
				subR->_bf = 1;
				parent->_bf = subRL->_bf = 0;
			}
			//②subRL的右子树插入新结点——subRL的平衡因子为1
			else if (bf == 1)
			{
				subR->_bf = subRL->_bf = 0;
				parent->_bf = -1;
			}
			//③subRL自身是被插入的新结点——subRL的平衡因子为0
			else
			{
				parent->_bf = subR->_bf = subRL->_bf = 0;
			}
		}

	public:
		AVLNode* Find(const K& key)
		{
			AVLNode* cur = _root;
			while (cur)
			{
				if (cur->_pair.first < key)
				{
					cur = cur->_right;
				}
				else if (cur->_pair.first > key)
				{
					cur = cur->_left;
				}
				else
				{
					return cur;
				}
			}
			return nullptr;
		}

		void Inorder()
		{
			_Inorder(_root);
			cout << endl;
		}
	private:
		void _Inorder(AVLNode* root)
		{
			if (root == nullptr) return;
			_Inorder(root->_left);
			cout << root->_pair.first << ' ' << root->_pair.second << endl;
			_Inorder(root->_right);
		}
	public:
		//检验函数
		int _Height(AVLNode* pRoot)
		{
			if (pRoot == nullptr) return 0;
			return max(_Height(pRoot->_left), _Height(pRoot->_right)) + 1;
		}
		bool _IsBalanceTree(AVLNode* pRoot)
		{
			// 空树也是AVL树
			if (nullptr == pRoot) return true;

			// 计算pRoot节点的平衡因子：即pRoot左右子树的高度差
			int leftHeight = _Height(pRoot->_left);
			int rightHeight = _Height(pRoot->_right);
			int diff = rightHeight - leftHeight;
			// 如果计算出的平衡因子与pRoot的平衡因子不相等，或者pRoot平衡因子的绝对值超过1，则一定不是AVL树
			if (diff != pRoot->_bf || (diff > 1 || diff < -1))
			{
				return false;
			}
				// pRoot的左和右如果都是AVL树，则该树一定是AVL树
			return _IsBalanceTree(pRoot->_left) && _IsBalanceTree(pRoot->_right);
		}
		AVLNode* getroot()
		{
			return _root;
		}
	private:
		AVLNode* _root;
	};

}