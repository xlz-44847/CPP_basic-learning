#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
//哈希（散列）的主要思想是用于查找，希望可以不通过比较，一次性拿到要搜索的元素
//于是考虑将带存储的元素按照某种哈希方法（散列方法）映射到指定位置，这样就在存储元素和存储位置之间产生了一一映射关系
//通过这种关系，我们可以根据待搜索的元素通过哈希函数直接计算出存储位置
//通过以上的方法构建出来的结构即为哈希表（散列表）

//哈希函数用于计算不同的元素应该存储的位置
//常见的哈希函数 Hash(key) ：
//①直接定址法：即线性关系确定位置 Hash(key) = A*key+B
//②除留余数法：即对哈希表的长度取模 Hash(key) = key%m

//哈希函数虽然决定了映射关系，但问题也很明显，即无法避免位置的冲突，我们一般将 不同关键码而具有相同哈希地址的现象 称为哈希冲突
//为了解决哈希冲突，可以采取闭散列或者开散列两种方法

//①闭散列，又称为开放地址法。即当发生哈希冲突时，可以把当前的key存储到冲突位置的“下一个”位置
namespace HashTable_open_address {
	//因为哈希冲突的存在，我们在占用对应位置时需要先对哈希表中对应位置的数据进行性质判断
	//哈希表中的元素包括 有效、已删除、空 三种状态，通过枚举常量来定义出这三种状态
	enum state{
		EMPTY,
		DELETE,
		EXIST
	};

	//哈希表元素既要包含key-value，还需要包含状态，因此使用结构体
	template <class K, class V>
	struct HashData
	{
		pair<K, V> _kv;
		state _state = EMPTY;
	};

	//需要注意，当前哈希表的哈希函数是直接对key取模
	//但是当哈希表元素的key是其他类型，如string时，很明显这种取模运算就会产生错误，因此我们需要想办法将string对象转化为可以取模运算的数值
	//我们通过模板参数HashFunc来处理，这是一个仿函数类，通过这个仿函数我们可以得到到对应对象的可进行模运算的数字

	//这是哈希表缺省仿函数类，当key类型可以转换成size_t时即可不传参采取默认的仿函数
	template<class K>
	struct HashFunc {
		size_t operator()(const K& key)
		{
			return (size_t)key;
		}
	};
	//类模板的特化，这样string类型也可以采取默认的仿函数了
	template<>
	struct HashFunc<string> {
		size_t operator()(const string& s)
		{
			size_t ret = 0;
			for (const auto& e : s)
			{
				ret = ret * 31 + e;	//string对象采取每次乘31再加下一个字符的策略
			}
			return ret;
		}
	};

	template<class K, class V, class HashFunc = HashFunc<K>>
	class HashTable {
	public:
		//构造函数
		HashTable()
		{
			_table.resize(10);
		}

		//查找
		HashData<K, V>* Find(const K& key)
		{
			HashFunc hsf;
			size_t hashi = hsf(key) % _table.size();
			while (_table[hashi]._state != EMPTY)	//注意DELETE不能作为判断查找完毕的标志
			{
				if (_table[hashi]._kv.first == key)
				{
					return &_table[hashi];
				}
				hashi = (hashi + 1) % _table.size();
			}
			return nullptr;
		}

		//插入
		bool Insert(const pair<K,V>& kv)
		{
			//使用find函数排除重复的情况
			if (Find(kv.first))
			{
				return false;
			}

			//处理扩容的情况
			//当负载因子（已存储元素/哈希表总长度）>= 0.7时就进行扩容
			//已存储元素由成员_num记录，每次成功insert后_num++
			if (_num * 10 / _table.size() >= 7)
			{
				//因为哈希函数计算中参考了哈希表长度，所以在扩容后会使得映射关系发生变化，所以需要一个一个重新调整
				//扩容方法：定义一个原先size大小二倍的数组，遍历原来的哈希表，将值一一映射到新的哈希表中，最后将这个局部变量与旧表交换，出函数作用域销毁旧表留下新表
				//我们发现上述方法中，将原值重新映射到新的哈希表中实际上就是对新表的insert，于是我们可以复用insert逻辑
				//由于在此阶段，新表不会涉及到重复或扩容问题，所以实际复用的是之后正常的插入逻辑

				HashTable<K, V> newtable;
				newtable._table.resize(2 * _table.size());
				for (int i = 0; i < _table.size(); i++)
				{
					if (_table[i]._state == EXIST)
					{
						newtable.Insert(_table[i]._kv);
					}
				}
				_table.swap(newtable._table);
			}

			HashFunc hfs;
			size_t hashi = hfs(kv.first) % _table.size();
			//当发生哈希冲突时，采取线性探测的方法找寻下一个空位置
			//线性探测：从发生冲突的位置开始，依次向后逐个检查是否有空位置
			//与之相似的探测方法还有二次探测：从发生冲突的位置开始，按二次方的规律找后1、4、9、16…的位置是否有空位置
			while (_table[hashi]._state == EXIST)
			{
				hashi = (hashi + 1) % _table.size();
			}
			//找到空位（DELETE、EMPTY），修改对应地址下的数据
			_table[hashi]._kv = kv;
			_table[hashi]._state = EXIST;
			_num++;
			return true;
		}
		
		//删除
		//删除只需要将对应位置的状态置为删除即可
		bool Erase(const K& key)
		{
			if (HashData<K, V>* dst = Find(key))
			{
				dst->_state = DELETE;
				_num--;
				return true;
			}
			else
			{
				return false;
			}
		}

	private:
		vector<HashData<K, V>> _table;
		size_t _num = 0;
	};
}

//②开散列，又称为链地址法（拉链法），即在哈希表的每个位置定义一个哈希桶（也就是链表），在发生冲突时将后来的结点链接在当前位置的链表后，即一个位置可以有多个由链表链接起来的元素
namespace HashTable_bucket {
	template <class K, class V>
	struct HashNode
	{
		//结点的构造函数
		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			,_next(nullptr)
		{}

		pair<K, V> _kv;
		HashNode<K, V>* _next;
	};

	//依然采取仿函数处理非数字对象的key
	template<class K>
	struct HashFunc {
		size_t operator()(const K& key)
		{
			return (size_t)key;
		}
	};
	//类模板的特化
	template<>
	struct HashFunc<string> {
		size_t operator()(const string& s)
		{
			size_t ret = 0;
			for (const auto& e : s)
			{
				ret = ret * 31 + e;	//string对象采取每次乘31再加下一个字符的策略
			}
			return ret;
		}
	};

	template<class K, class V, class HashFunc = HashFunc<K>>
	class HashTable {
	public:
		typedef HashNode<K, V> Node;
		//构造函数
		HashTable()
		{
			_table.resize(10, nullptr);
		}
		//析构函数
		~HashTable()
		{
			for (int i = 0; i < _table.size(); i++)
			{
				Node* cur = _table[i];
				while (cur)
				{
					Node* tmp = cur;
					cur = cur->_next;
					delete tmp;
				}
				_table[i] = nullptr;
			}
		}

		//查找
		//哈希函数定位到位置，遍历哈希桶寻找
		Node* Find(const K& key)
		{
			HashFunc hsf;
			size_t hashi = hsf(key) % _table.size();
			Node* cur = _table[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					return cur;
				}
				cur = cur->_next;
			}
			return nullptr;
		}

		//插入
		bool Insert(const pair<K, V>& kv)
		{
			//使用find函数排除重复的情况
			if (Find(kv.first))
			{
				return false;
			}

			HashFunc hfs;
			size_t hashi = hfs(kv.first) % _table.size();

			//处理扩容的情况
			//当负载因子（已存储元素/哈希桶总数量（也即哈希表长度））>= 1时就进行扩容,
			//已存储元素由成员_num记录，每次成功insert后_num++
			if (_num  / _table.size() >= 1)
			{
				//同样的，在扩容后会使得映射关系发生变化，需要一个一个重新调整
				//扩容方法：定义一个原先size大小二倍的数组，遍历原来的哈希表，将值一一映射到新的哈希表中，最后将这个局部变量与旧表交换，出函数作用域销毁旧表留下新表
				
				//我们采取老方法，将这个过程看作向新表插入数据，复用insert
				//但是这种方法需要将原哈希表的结点全部释放后再new一遍，效率低
				
				/*HashTable<K, V> newtable;
				newtable._table.resize(2 * _table.size(), nullptr);
				for (int i = 0; i < _table.size(); i++)
				{
					Node* cur = _table[i];
					while (cur)
					{
						newtable.Insert(cur->_kv);
						cur = cur->_next;
					}
				}
				_table.swap(newtable._table);*/

				//我们可以采取直接转移结点的方法，遍历原哈希表，将其中的结点直接链在新哈希表中,实际上就是把Insert的复用部分再写一遍
				vector<Node*> newtable;	//新建一个vector作为新的table
				newtable.resize(2 * _table.size(), nullptr);
				for (int i = 0; i < _table.size(); i++)
				{
					Node* cur = _table[i];
					while (cur)
					{
						Node* tmp = cur->_next;//记录cur的next

						size_t hashi = hfs(cur->_kv.first) % newtable.size();//根据新表计算地址
						//头插
						cur->_next = newtable[hashi];
						newtable[hashi] = cur;
						cur = tmp;
					}
					_table[i] = nullptr;//原表置空是好习惯，此处换出去的是vector，析构时析构的也是vector<Node*>不会调用到哈希表的析构函数，所以不会释放结点，不置空也不会有问题
				}
				_table.swap(newtable);
			}

			//找到了对应位置后直接头插即可
			Node* newnode = new Node(kv);
			newnode->_next = _table[hashi];
			_table[hashi] = newnode;
			_num++;

			return true;
		}

		//删除
		//因为是单链表的删除，需要遍历桶找到前驱节点,并且考虑头删的问题
		bool Erase(const K& key)
		{
			HashFunc hsf;
			size_t hashi = hsf(key) % _table.size();
			Node* cur = _table[hashi];
			Node* prev = nullptr;
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (prev == nullptr)
					{
						_table[hashi] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}
					delete cur;
					_num--;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}

	private:
		vector<Node*> _table;
		size_t _num = 0;
	};
}