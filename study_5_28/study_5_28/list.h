#pragma once
#include<iostream>
#include<assert.h>
#include"ReverseIterator.h"

namespace m_list	//为自己实现的list定义命名空间
{
	//结点
	template <class T>
	struct ListNode	//使用类模板来定义结点的信息
	{
		//双向链表，节点内存前驱指针和后继指针，以及值
		ListNode<T>* _prev;
		ListNode<T>* _next;
		T _val;
		//构造函数，使用初始化列表初始化
		ListNode(const T& val = T())	//参数注意使用const引用，因为实参可能是常性的
			:_prev(nullptr)
			,_next(nullptr)
			,_val(val)
		{}
	};

	//迭代器
	//对于链表而言，由于其物理存储空间不连续，所以迭代器不可以使用原生的指针，因为自增等行为有很大不同
	//因此需要我们自己根据需要实现迭代器，因此封装一个迭代器类，来支持链表的特性
	//对于迭代器，为了支持const和非const的迭代器，同时为了代码复用，所以在迭代器模板中增加模板参数，来选择const和非const
	//由于const版本迭代器只在解引用的时候有不同，所以增加两个模板参数对解引用的返回值进行控制
	template <class T, class Ref, class Ptr>
	struct ListIterator
	{
		//类比学习，迭代器的作用相当于元素的替身。
		//在string中，string是由一个个字符组成的，迭代器变量表示字符串中的字符，通过解引用操作即可访问其值
		//在vector中，vector是由一个个元素组成的，迭代器变量表示数组中的元素，通过解引用操作可以访问该元素
		//同理，对于list是由一个个结点组成的，迭代器应该表示链表的结点，因此采用结点指针的方式定义迭代器
		typedef ListNode<T> Node;

		Node* _node;

		//构造函数
		ListIterator(Node* node)
			:_node(node)
		{}
		//解引用
		//*it
		//迭代器追求的是不考虑组织形式，采取一致的格式进行遍历
		//因此，在list中，要保证*it可以像其他容器一样拿到对应的数据，所以*it应当返回T
		//对于*it，非const对象拿到的是非const返回值，const对象拿到的是const返回值
		Ref operator*()
		{
			return _node->_val;
		}
		//it->
		//->箭头方式的解引用使用场景是链表模板实例化为结构体，因为链表的迭代器是结点指针，所以访问结点内结构体对象的成员需要使用it->
		//如：对于结构体struct A{ int a, int b }, 链表list<A> lt
		//	按照平时使用习惯访问a的方式应该是it->a
		//	迭代器变量it是迭代器类的对象，而it->a这种方式访问成员的方式，it应该是A结构体变量的指针
		//	针对这种情况，首先重载了->操作符，返回对应的类型T的指针，但此时如果想要访问成员则还需要一个->指向a
		//	为了可读性编译器在语法上省略了一个->，所以原本的it->->a，可以写作it->a,实际上是it.operator->()->a，it.operator->()则是重载->的返回值T*
		//对于it->，非const对象拿到的是非const指针，const对象拿到的是const指针
		Ptr operator->()
		{
			return &_node->_val;
		}

		//对于list，迭代器自增自减的行为即是找到next和prev结点
		//前置++
		ListIterator<T, Ref, Ptr>& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		//后置++
		ListIterator<T, Ref, Ptr> operator++(int)
		{
			ListIterator<T, Ref, Ptr> tmp(_node);
			_node = _node->_next;
			return tmp;
		}
		//前置--
		ListIterator<T, Ref, Ptr>& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		//后置--
		ListIterator<T, Ref, Ptr> operator--(int)
		{
			ListIterator<T> tmp(_node);
			_node = _node->_prev;
			return tmp;
		}
		//==和!=
		bool operator==(const ListIterator<T, Ref, Ptr>& it)
		{
			return _node == it._node;
		}
		bool operator!=(const ListIterator<T, Ref, Ptr>& it)
		{
			return _node != it._node;
		}
	};


	//链表
	template <class T>
	class list
	{
	public:
		//构造函数
		//无参构造
		//双向带头链表，所以需要先new一个头结点，并且前后指针都指向自己
		list()
			:_head(new Node)
			, _size(0)
		{
			_head->_prev = _head;
			_head->_next = _head;
		}
		//初始化列表构造
		list(std::initializer_list<T> il)
			:_head(new Node)
			, _size(0)
		{
			_head->_prev = _head;
			_head->_next = _head;
			for (auto& e : il)
			{
				push_back(e);
			}
		}
		//拷贝构造
		//拷贝构造初始化出头结点，然后将结点逐个插入
		list(const list<T>& lt)
			:_head(new Node)
			,_size(0)
		{
			_head->_prev = _head;
			_head->_next = _head;

			for (auto& e : lt)
			{
				push_back(e);
			}
		}
		//析构函数
		//析构需要释放所有的结点，可以通过逐个结点删除的方式来复用函数，完成释放
		~list()
		{
			clear();
			delete _head;

			_head = nullptr;
		}
		void clear()
		{
			iterator it = begin();
			//使用迭代器对链表结点进行删除时，注意无需it++
			while (it != end())
			{
				it = erase(it);
			}
		}
		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}
		//赋值运算符重载
		list<T> operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}
		size_t size()
		{
			return _size;
		}
		bool empty()
		{
			return _size == 0;
		}
		//正向迭代器
		//对于*it，非const对象拿到的是非const返回值，const对象拿到的是const返回值
		//对于it->，非const对象拿到的是非const指针，const对象拿到的是const指针
		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T*> const_iterator;
		//begin和end返回值都是迭代器类的对象，单参数构造函数所以支持隐式类型转换
		//非const
		iterator begin()
		{
			return _head->_next;
		}
		iterator end()
		{
			return _head;
		}
		//const
		const_iterator begin() const
		{
			return _head->_next;
		}
		const_iterator end() const
		{
			return _head;
		}

		//反向迭代器
		//对于*it，非const对象拿到的是非const返回值，const对象拿到的是const返回值
		//对于it->，非const对象拿到的是非const指针，const对象拿到的是const指针
		typedef ReverseIterator<iterator, T&, T*> reverse_iterator;
		typedef ReverseIterator<const_iterator, const T&, const T*> const_reverse_iterator;
		//begin和end返回值都是迭代器类的对象，单参数构造函数所以支持隐式类型转换
		//非const
		reverse_iterator rbegin()
		{
			return end();	//同样是单参数的隐式类型转换
		}
		reverse_iterator rend()
		{
			return begin();
		}
		//const
		const_reverse_iterator rbegin() const
		{
			return end();
		}
		const_reverse_iterator rend() const
		{
			return begin();
		}
		
		//插入
		//对于list而言，不存在扩容的行为，所以list的插入不会导致迭代器失效
		//insert在pos位置前插入val，为满足临时变量的插入需要使用const引用
		void insert(iterator pos, const T& val)
		{
			Node* next = pos._node;
			Node* prev = next->_prev;
			Node* newnode = new Node(val);

			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = next;
			next->_prev = newnode;

			++_size;
		}
		void push_back(const T& val)
		{
			insert(end(), val);
		}
		void push_front(const T& val)
		{
			insert(begin(), val);
		}
		//删除
		//erase由于释放结点，所以有迭代器失效的可能性，所以删除操作需要返回迭代器提供更新
		iterator erase(iterator pos)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;
			
			prev->_next = next;
			next->_prev = prev;
			delete cur;
			//cur是ListNode<T>类型，delete时会调用对应的析构函数
			//由于ListNode<T>的成员变量都是内置类型，所以无需手动释放资源，使用编译器生成的析构函数即可
			--_size;

			//return next;	//也可以，单参数构造函数支持隐式类型转换
			return iterator(next);
		}
		iterator pop_back()
		{
			erase(--end());
		}
		iterator pop_front()
		{
			erase(begin());
		}
	private:
		typedef ListNode<T> Node;	//使用结点时需要对结构体模板参数实例化，因此使用typedef简化代码
		
		Node* _head;	//链表的头
		size_t _size;	//链表的规模
	};
	
	void Test1()
	{
		list<int> l1;
		l1.push_back(3);
		l1.push_back(4);
		l1.push_back(5);
		l1.push_front(2);
		l1.push_front(1);

		list<int>::iterator it = l1.begin();
		while (it != l1.end())
		{
			std::cout << *it << ' ';
			++it;
		}
		std::cout << std::endl;

		list<int> l2(l1);
		for(auto& e:l2)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		list<int> l3;
		l3.push_back(10);
		for (auto& e : l3)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;
		l3 = l1;
		for (auto& e : l3)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;
	}
	
	struct A {
		char c1;
		int a[2];
	};
	void Test2()
	{
		A a{ 'a',{1,1} };
		list<A> lt1;
		lt1.push_back(a);
		lt1.push_back({ 'b', { 2,2 } });
		list<A>::iterator it1 = lt1.begin();
		while (it1 != lt1.end())
		{
			std::cout << it1->c1 << ' ';
			++it1;
		}
		std::cout << std::endl;

		it1 = lt1.begin();
		std::cout << it1->a[0] << ' ' << it1->a[1] << std::endl;
		++it1;
		std::cout << it1->a[0] << ' ' << it1->a[1] << std::endl;
	}
	void Test3()
	{
		list<A> lt1;
		lt1.push_back({ 'a',{1,1} });
		list<A>::iterator it1 = lt1.begin();
		it1->c1;
		//it1实际的类型是ListIterator<A,A&,A*>，成员是ListNode<A>的结构体指针，这个结构体是链表的结点，包含成员前序、后继指针和值
		//it1的构造函数将ListNode<A>*类型的参数赋值给it1下的成员（链表结点指针），使用的是lt1调用的begin，返回值是ListIterator<A,A&,A*>类型，其中的结点是头结点的下一个结点
		//ListIterator<A,A&,A*>类型的参数通过隐式类型转换传参给构造函数，赋值给it1对象
		//it1->c1调用了Ptr operator->()函数，Ptr被实例化为了A*，返回了_node->_val的地址，也就是返回了lt1链表中的值的地址，即结构体{ 'a',{1,1} }的地址
		//省略了一个->操作符，找到了c1成员，实际上是it1.operator->()->c1
		
		list<int> lt2;
		lt2.push_back(1);
		list<int>::iterator it2 = lt2.begin();
		*it2;
		//it2实际的类型是ListIterator<int,int&,int*>，成员是ListNode<int>的结构体指针，这个结构体是链表的结点，包含成员前序、后继指针和值
		//it2的构造函数将ListNode<int>*类型的参数赋值给it1下的成员（链表结点指针），使用的是lt1调用的begin，返回值是ListIterator<int,int&,int*>类型，其中的结点是头结点的下一个结点
		//ListIterator<int,int&,int*>类型的参数通过隐式类型转换传参给构造函数，赋值给it2对象
		//*it2调用了Ref operator*()函数，Ref被实例化为了int&，返回了_node->_val的引用，也就是返回了lt2链表中的值的引用，即结点内容 1 的引用
	}
	void Test4()
	{
		list<int> l1({ 1,3,5,7,9 });
		list<int>::iterator it = l1.begin();
		while (it != l1.end())
		{
			std::cout << *it << ' ';
			++it;
		}
		std::cout << std::endl;
	}
	void Test5()
	{
		list<int> l1({ 1,2,3,4,5,6,7,8 });
		list<int> const l2({ 11,22,33,44,55,66,77,88 });
		list<int>::iterator it1 = l1.begin();
		while (it1 != l1.end())
		{
			std::cout << *it1 << ' ';
			++it1;
		}
		std::cout << std::endl;
		list<int>::const_iterator it2 = l2.begin();
		while (it2 != l2.end())
		{
			std::cout << *it2 << ' ';
			++it2;
		}
		std::cout << std::endl;
		list<int>::reverse_iterator rit1 = l1.rbegin();
		while (rit1 != l1.rend())
		{
			std::cout << *rit1 << ' ';
			++rit1;
		}
		std::cout << std::endl;
		list<int>::const_reverse_iterator rit2 = l2.rbegin();
		while (rit2 != l2.rend())
		{
			std::cout << *rit2 << ' ';
			++rit2;
		}
		std::cout << std::endl;
	}
	void Test6()
	{
		list<A> l1;
		l1.push_back({ 'a', { 1,1 } });
		l1.push_back({ 'b', { 2,2 } });
		l1.push_back({ 'c', { 3,3 } });
		list<A> const l2(l1);

		list<A>::iterator it1 = l1.begin();
		while (it1 != l1.end())
		{
			std::cout << it1->c1 << ' ';
			++it1;
		}
		std::cout << std::endl;
		list<A>::const_iterator it2 = l2.begin();
		while (it2 != l2.end())
		{
			std::cout << it2->a[0] << ' ';
			++it2;
		}
		std::cout << std::endl;
		list<A>::reverse_iterator rit1 = l1.rbegin();
		while (rit1 != l1.rend())
		{
			std::cout << rit1->c1 << ' ';
			++rit1;
		}
		std::cout << std::endl;
		list<A>::const_reverse_iterator rit2 = l2.rbegin();
		while (rit2 != l2.rend())
		{
			std::cout << rit2->a[1] << ' ';
			++rit2;
		}
		std::cout << std::endl;
	}
}