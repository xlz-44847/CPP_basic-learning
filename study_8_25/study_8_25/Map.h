#pragma once

#include "RBTree.h"

namespace Map {
	template <class K, class V>
	class map {
		//取出Key的仿函数
		struct Map_KeyOfT
		{
			//传入一个value，是T类型，要求返回value的key
			//map的value是一个pair，key是pair的first
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		//由于是对模板类中的类型进行重命名，模板类没有实例化，编译器并不知道iterator是什么，因此需要加上typename来告诉编译器这是一个类型名
		typedef typename RBTree::RBTree<K, pair<const K, V>, Map_KeyOfT>::iterator iterator;
		typedef typename RBTree::RBTree<K, pair<const K, V>, Map_KeyOfT>::constiterator constiterator;
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

		pair<iterator, bool> insert(const pair<K,V>& kv)
		{
			return _tree.insert(kv);
		}
		iterator find(const K& key)
		{
			return _tree.find(key);
		}
		V& operator[](const K& key)
		{
			return find(key)->second;
		}

	private:
		RBTree::RBTree<K, pair<const K, V>, Map_KeyOfT> _tree;
	};
}

