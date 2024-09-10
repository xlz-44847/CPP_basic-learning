#pragma once
#include<iostream>
using namespace std;

//二叉搜索树的结点——K模型（只有key值）
namespace key
{
	//成员包括：key值、左孩子指针、右孩子指针
	template <class K>
	struct BSTNode {
		K _key;
		BSTNode<K>* _left;
		BSTNode<K>* _right;

		//构造函数
		//给定key值，构造对应的结点
		BSTNode(K key)
			:_key(key)
			, _left(nullptr)
			, _right(nullptr)
		{}
	};

	//二叉搜索树——K模型
	//成员是二叉搜索树的根结点指针
	template <class K>
	class BSTree {
	private:
		typedef BSTNode<K> Node;
		Node* _root;
	public:
		//构造
		BSTree()
			:_root(nullptr)
		{}
		//析构
		//析构一棵树需要递归处理，所以需要写一个辅助函数帮助析构的递归处理部分
	private:
		void Destroy(Node* root)
		{
			if (root == nullptr) return;
			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
		}
	public:
		~BSTree()
		{
			Destroy(_root);
			_root = nullptr;
		}

		//插入数据
		//二叉搜索树左孩子比父亲小，右孩子比父亲大
		//所以插入数据需要层层比较来找到合适的位置
		bool Insert(const K& key)
		{
			Node* newnode = new Node(key);
			//如果是第一次插入，则根结点为空指针，需要特殊处理
			if (_root == nullptr)
			{
				_root = newnode;
				return true;
			}

			Node* parent = _root;
			Node* cur = _root;
			while (cur)
			{
				//二叉搜索树已经存在的值不会再插入
				//所以结点值大于key，则向左子树找；结点值小于key，向右子树找；如果相等则不再插入，返回false
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}
			if (parent->_key > key)
			{
				parent->_left = newnode;
			}
			else
			{
				parent->_right = newnode;
			}
			return true;
		}
		//查找搜索二叉树中是否存在key的结点
		bool Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else
				{
					return true;
				}
			}
			return false;
		}
		//删除结点
		//删除结点后，为了保证二叉搜索树的结构不变，则顶替该位置的结点key值应该大于左子树，小于右子树
		//为了满足这一点，可以考虑找左子树最大值或右子树最小值
		//因为右孩子一定比父结点大，所以左子树最大值只需要沿着左子树右孩子寻找到尽头即可
		//同理，右子树最小值需要沿着右子树左孩子寻找到尽头
		bool Erase(const K& key)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//删除cur：
					//1.cur左树为空（包括全空），直接将右树链在parent上
					if (cur->_left == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else if (parent->_left == cur)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
						delete cur;
						return true;
					}
					//2.cur右树为空，直接将左树链在parent上
					else if (cur->_right == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_left;
						}
						else if (parent->_left == cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
						delete cur;
						return true;
					}
					//3.cur两树均不为空，找左子树最大或右子树最小，与cur替换
					else
					{
						//MaxLeft
						Node* change_node = cur->_left;
						Node* change_parent_node = cur;
						while (change_node->_right)
						{
							change_parent_node = change_node;
							change_node = change_node->_right;
						}
						//找到最大左树值与其父，为了方便，将最大值与cur值交换即可
						cur->_key = change_node->_key;
						//由于左树最大值是先找左孩子，再一直找右孩子，所以需要判断是左孩子还是右孩子
						//并且左子树最大结点一定没有右孩子，但可能有左孩子，所以需要把左树的根结点链在最大结点父结点对应位置
						if (change_parent_node->_left == change_node)
						{
							change_parent_node->_left = change_node->_left;
						}
						else
						{
							change_parent_node->_right = change_node->_left;
						}

						delete change_node;

						return true;
					}
				}
			}
			return false;
		}
		void Inorder()
		{
			//中序遍历需要递归，而且调用时不传参，所以需要单另将递归逻辑写出去
			_Inorder(_root);
			cout << endl;
		}
		void _Inorder(Node* root)
		{
			if (root == nullptr) return;
			_Inorder(root->_left);
			cout << root->_key << ' ' << endl;
			_Inorder(root->_right);
		}
	};
}

//二叉搜索树的结点——KV模型（每一个key都指向一个value值）
namespace keyvalue
{
	//成员包括：key值、value值、左孩子指针、右孩子指针
	template <class K, class V>
	struct BSTNode {
		K _key;
		V _value;
		BSTNode<K, V>* _left;
		BSTNode<K, V>* _right;

		//构造函数
		//给定key值和value值，构造对应的结点
		BSTNode(K key, V value)
			:_key(key)
			, _value(value)
			, _left(nullptr)
			, _right(nullptr)
		{}
	};

	//二叉搜索树——KV模型
	//成员是二叉搜索树的根结点指针
	template <class K, class V>
	class BSTree {
	private:
		typedef BSTNode<K, V> Node;
		Node* _root;
	public:
		//构造
		BSTree()
			:_root(nullptr)
		{}
		//析构
		//析构一棵树需要递归处理，所以需要写一个辅助函数帮助析构的递归处理部分
	private:
		void Destroy(Node* root)
		{
			if (root == nullptr) return;
			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
		}
	public:
		~BSTree()
		{
			Destroy(_root);
			_root = nullptr;
		}

		//插入数据
		//以key为指标，二叉搜索树左孩子比父亲小，右孩子比父亲大
		//所以插入数据需要层层比较来找到合适的位置
		bool Insert(const K& key, const V& value)
		{
			Node* newnode = new Node(key, value);
			//如果是第一次插入，则根结点为空指针，需要特殊处理
			if (_root == nullptr)
			{
				_root = newnode;
				return true;
			}

			Node* parent = _root;
			Node* cur = _root;
			while (cur)
			{
				//二叉搜索树已经存在的值不会再插入
				//所以结点值大于key，则向左子树找；结点值小于key，向右子树找；如果相等则不再插入，返回false
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}
			if (parent->_key > key)
			{
				parent->_left = newnode;
			}
			else
			{
				parent->_right = newnode;
			}
			return true;
		}
		//查找搜索二叉树中是否存在key的结点
		bool Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else
				{
					return true;
				}
			}
			return false;
		}
		//删除结点
		//删除结点后，为了保证二叉搜索树的结构不变，则顶替该位置的结点key值应该大于左子树，小于右子树
		//为了满足这一点，可以考虑找左子树最大值或右子树最小值
		//因为右孩子一定比父结点大，所以左子树最大值只需要沿着左子树右孩子寻找到尽头即可
		//同理，右子树最小值需要沿着右子树左孩子寻找到尽头
		bool Erase(const K& key)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//删除cur：
					//1.cur左树为空（包括全空），直接将右树链在parent上
					if (cur->_left == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else if (parent->_left == cur)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
						delete cur;
						return true;
					}
					//2.cur右树为空，直接将左树链在parent上
					else if (cur->_right == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_left;
						}
						else if (parent->_left == cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
						delete cur;
						return true;
					}
					//3.cur两树均不为空，找左子树最大或右子树最小，与cur替换
					else
					{
						//MaxLeft
						Node* change_node = cur->_left;
						Node* change_parent_node = cur;
						while (change_node->_right)
						{
							change_parent_node = change_node;
							change_node = change_node->_right;
						}
						//找到最大左树值与其父，为了方便，将最大值与cur值交换即可
						cur->_key = change_node->_key;
						//由于左树最大值是先找左孩子，再一直找右孩子，所以需要判断是左孩子还是右孩子
						//并且左子树最大结点一定没有右孩子，但可能有左孩子，所以需要把左树的根结点链在最大结点父结点对应位置
						if (change_parent_node->_left == change_node)
						{
							change_parent_node->_left = change_node->_left;
						}
						else
						{
							change_parent_node->_right = change_node->_left;
						}

						delete change_node;

						return true;
					}
				}
			}
			return false;
		}
		void Inorder()
		{
			//中序遍历需要递归，而且调用时不传参，所以需要单另将递归逻辑写出去
			_Inorder(_root);
			cout << endl;
		}
		void _Inorder(Node* root)
		{
			if (root == nullptr) return;
			_Inorder(root->_left);
			cout << root->_key << ' ' << root->_value << endl;
			_Inorder(root->_right);
		}
	};
}

