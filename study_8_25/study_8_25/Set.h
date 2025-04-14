#pragma once

#include "RBTree.h"

namespace Set {
	template <class K>
	class set {
		//取出Key的仿函数
		struct Set_KeyOfT
		{
			//传入一个value，是T类型，要求返回value的key
			//set的value和key相同
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		//由于是对模板类中的类型进行重命名，模板类没有实例化，编译器并不知道iterator是什么，因此需要加上typename来告诉编译器这是一个类型名
		typedef typename RBTree::RBTree<K, K, Set_KeyOfT>::iterator iterator;
		typedef typename RBTree::RBTree<K, K, Set_KeyOfT>::constiterator constiterator;
		iterator begin()
		{
			return _tree.begin();
		}
		iterator end()
		{
			return _tree.end();
		}
		constiterator cbegin()
		{
			return _tree.cbegin();
		}
		constiterator cend()
		{
			return _tree.cend();
		}
		
		pair<iterator,bool> insert(const K& key)
		{
			return _tree.insert(key);
		}
		iterator find(const K& key)
		{
			return _tree.find(key);
		}

	private:
		RBTree::RBTree<K, K, Set_KeyOfT> _tree;
	};
}
