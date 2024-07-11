#pragma once

#include<iostream>
#include<assert.h>
#include<string.h>
#include"ReverseIterator.h"

namespace m_vector	//为自己实现的vector定义一个命名空间
{
	template<class T>	//使用类模板
	class vector
	{
	public:
		//构造函数：
		//1.无参构造，成员参数全部初始化为空指针
		vector()
		{}
		//2.拷贝构造
		//拷贝构造需要一些成员函数的辅助
		vector(const vector<T>& v)
		{
			//拷贝构造：先扩容，然后将元素依次尾插
			reserve(v.capacity());
			for (auto& e : v)
			{
				push_back(e);
			}
		}
		//3.n个元素构造，构造的vector初始化为具有n个val元素
		// vector (size_type n, const value_type& val = value_type());
		vector(size_t n, const T& val = T())	//以匿名对象T()作为缺省值
		{
			resize(n, val);
		}
		//由于存在如4所示的迭代区间构造，并且3中的参数n类型为size_t，所以如vector v(2,3)的(int,int)类的构造就会被认为是4的构造类型，因为将类型推导为int更贴合。
		//所以为了避免这种情况需要为(int,int)再重载一个构造
		vector(int n, const T& val = T())
		{
			resize(n, val);
		}
		//4.迭代区间构造，构造的数组使用迭代区间的内容初始化
		// template <class InputIterator> 
		// vector (InputIterator first, InputIterator last);
		// 类模板的成员函数可以是函数模板，使用函数模板以满足各种数据类型迭代区间的构造
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			//由于任何数据类型都实现并支持迭代器，所以可以使用迭代器进行访问
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		//5.使用初始化列表进行构造
		//初始化列表：template<class T> class initializer_list;
		//这是C++11中新增的类型，也是一种类模板。在初始化列表时使用过，使用大括号进行表示。
		//这个类模板的函数很少。只满足了迭代器和size()
		vector(std::initializer_list<T> il)
		{
			reserve(il.size());
			for (auto& e : il)	//e使用引用，减小拷贝开销
			{
				push_back(e);
			}
		}
		//析构函数
		~vector()
		{
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}
		//swap，交换
		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}
		//赋值运算符重载
		vector<T>& operator=(vector<T> v)
		{
			//传参时存在拷贝，将拷贝结果与this交换，原先的this被释放
			swap(v);
			return *this;
		}

		//size，返回vector的数组大小
		size_t size() const
		{
			return _finish - _start;	//指针-指针得到之间元素个数
		}
		//capacity，返回vector的容量大小
		size_t capacity() const
		{
			return _endofstorage - _start;
		}
		//[]运算符重载，重载const和非const版本
		T& operator[](size_t pos)
		{
			assert(pos < size());

			return _start[pos];
		}
		const T& operator[](size_t pos) const
		{
			assert(pos < size());

			return _start[pos];
		}
		typedef T* iterator;
		typedef const T* const_iterator;	//定义迭代器为T*类型
		//非const迭代器
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		//const迭代器
		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}
		//反向迭代器
		typedef ReverseIterator<iterator,T&,T*> reverse_iterator;
		typedef ReverseIterator<const_iterator, const T&, const T*> const_reverse_iterator;
		reverse_iterator rbegin()
		{
			return end();
		}
		reverse_iterator rend()
		{
			return begin();
		}
		const_reverse_iterator rbegin() const
		{
			return end();
		}
		const_reverse_iterator rend() const
		{
			return begin();
		}

		//reserve，调整容量
		//	n>capacity:扩容到n
		//	n<=capacity:不做处理
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t old_size = size();	//需要先存储原数组size
				
				//开辟新的容量的空间tmp，将原数组内容拷贝到tmp中，并释放原空间
				T* tmp = new T[n];
				//memcpy(tmp, _start, size() * sizeof(T));	
				//memcpy属于浅拷贝，在遇到类似于string、vector对象作为元素时，拷贝后的结果仅仅是将要被释放的无效的地址
				//所以要在此处完成深拷贝，即将原数组中的内容一一赋值给tmp
				for (size_t i = 0; i < old_size; i++)
				{
					tmp[i] = _start[i];	//此处实际调用的是T类型对应的赋值运算符，如数组元素为string，这时只需要保证string的赋值运算符重载是深拷贝，此处调用后完成的就是深拷贝
				}
				delete[] _start;

				//成员变量是指针类型，所以在重新分配空间后地址发生变化，所有成员变量都需要进行更新
				_start = tmp;
				_finish = tmp + old_size;	//提前计算size大小，否则当_start变化后，就无法再获得size了
				_endofstorage = tmp + n;
			}
		}
		//resize，调整大小
		//	n>size:将size扩大至n，扩展出的空间使用参数进行填充
		//	n<=size:将size缩小至n，截断
		void resize(size_t n, const T& val = T())
			//使用T()作为缺省值，T()是T类的匿名对象，被用来赋值的时候会调用其类的构造函数生成对象
			//使用了匿名对象可以保证对自定义类型的缺省
			//对于内置类型，C++为其定义一个伪构造函数，即当T是内置类型时，内置类型会被当做对象调用构造函数，如int类型会被默认初始化为0
		{
			if (n > size())
			{
				reserve(n);
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
			else
			{
				_finish = _start + n;
			}
		}
		//push_back：尾插
		void push_back(const T& val)
		{
			//检查扩容
			if (_finish == _endofstorage)
			{
				reserve(capacity() == 0 ? 4 : 2 * capacity());
			}
			
			*_finish = val;
			++_finish;
		}
		//empty：判空
		bool empty()
		{
			return _start == _finish;
		}
		//pop_back：尾删
		void pop_back()
		{
			assert(!empty());

			--_finish;
		}
		//insert：在pos位置前插入
		void insert(iterator pos, const T& val)
		{
			//检查扩容
			if (_finish == _endofstorage)
			{
				size_t old_len = pos - _start;	//pos是iterator类型参数，所以当扩容后整个数组的地址会发生改变，所以pos的值就失去了意义，因此记录相对位置，并使pos随数组做出修改
				reserve(capacity() == 0 ? 4 : 2 * capacity());
				pos = _start + old_len;
			}
			iterator it = _finish;
			while (it != pos)
			{
				*it = *(it - 1);
				--it;
			}
			*pos = val;
			++_finish;
		}
		//erase：删除pos位置的值
		//void erase(iterator pos)
		iterator erase(iterator pos)	//erase可能导致迭代器失效，所以返回新的迭代器值，来更新原先的迭代器
		{
			assert(pos < _finish && pos >= _start);

			iterator it = pos;
			while (it != _finish)
			{
				*it = *(it + 1);
				++it;
			}
			--_finish;

			return pos;
		}

	private:	//成员变量都是迭代器变量的形式（指针），尽量贴合库中的形式
		iterator _start = nullptr;	//vector起始地址
		iterator _finish = nullptr;	//vector最后一个数据的下一个地址
		iterator _endofstorage = nullptr;	//vector开辟的空间的下一个地址
		//全部给定缺省值为空指针
	};

	void Test1()
	{
		vector<int> v1;
		v1.resize(10, 6);
		for (auto e : v1)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		std::cout << v1.size() << std::endl;
		std::cout << v1.capacity() << std::endl;
		v1.reserve(20);
		std::cout << v1.size() << std::endl;
		std::cout << v1.capacity() << std::endl;
		v1.resize(5);
		std::cout << v1.size() << std::endl;
		std::cout << v1.capacity() << std::endl;
		for (auto e : v1)
		{
			std::cout << e << " ";
		}
	}
	void Test2()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(1);
		v1.push_back(1);
		v1.push_back(1);
		v1.push_back(1);
		v1.push_back(1);
		vector<int>::iterator it1 = v1.begin();
		while(it1!=v1.end())
		{
			std::cout << *it1 << " ";
			++it1;
		}
		std::cout << std::endl;
		v1.pop_back();
		v1.pop_back();
		vector<int>::iterator it2 = v1.begin();
		while (it2 != v1.end())
		{
			std::cout << *it2 << " ";
			++it2;
		}
		std::cout << std::endl;
	}
	void Test3()
	{
		vector<int> v1;
		v1.push_back(0);
		v1.push_back(0);
		v1.push_back(0);
		v1.push_back(0);
		v1.insert(v1.begin() + 1, 8);
		v1.insert(v1.begin(), 3);
		v1.insert(v1.begin() + 2, 99);
		vector<int>::iterator it1 = v1.begin();
		while (it1 != v1.end())
		{
			std::cout << *it1 << " ";
			++it1;
		}
		std::cout << std::endl;
		v1.erase(v1.begin() + 2);
		v1.erase(v1.begin() + 4);
		vector<int>::iterator it2 = v1.begin();
		while (it2 != v1.end())
		{
			std::cout << *it2 << " ";
			++it2;
		}
		std::cout << std::endl;
	}
	void Test4()
	{
		vector<int> v1(6);
		vector<int> v2(4,71);
		vector<int> v3(v2);
		for (auto e : v1)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;
		for (auto e : v2)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;
		for (auto e : v3)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		std::string s("abcdef");
		vector<char> v4(s.begin() + 1, s.end() - 1);
		for (auto e : v4)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		//实例化初始化列表类
		auto a = { 1,2,3,4,5 };
		std::initializer_list<int> b = { 2,3,4 };

		vector<int> v5(a);
		vector<int> v6{ 1,2,9 };
		vector<int> v7({ 2,3,5 });
		vector<int> v8 = { 1,1,4,5,1,4 };//单参数构造支持隐式类型转换

		for (auto e : v5)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;
		for (auto e : v6)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;
		for (auto e : v7)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;
		for (auto e : v8)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		v1 = v8;
		for (auto e : v1)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;
	}
	void Test5()
	{
		//reserve浅拷贝则会报错
		vector<std::string> v1;
		v1.push_back("one");
		v1.push_back("two");
		v1.push_back("three");
		v1.push_back("four");
		v1.push_back("five");
		for (auto& e : v1)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		//迭代器失效：
		//①在insert、push_back操作后可能会导致迭代器实现，这是由于扩容更改空间导致的
		vector<int> v2;
		v2.push_back(1);
		v2.push_back(2);
		v2.push_back(3);
		v2.push_back(4);
		vector<int>::iterator it1 = v2.begin() + 2;
		std::cout << *it1 << std::endl;
		v2.push_back(5);
		std::cout << *it1 << std::endl;	//打印了随机值，所以it1失效了，insert同理
		//针对这种迭代器失效，无法避免，所以一般在insert或push_back操作后，就不再使用之前的it
		//如有需求，可以在插入操作后对it进行更新
		it1 = v2.begin() + 2;
		std::cout << *it1 << std::endl;

		//②在erase后可能会导致迭代器失效
		//一方面是由于缩容导致的
		//另一方面则是erase函数和遍历时的协调问题，我们可以进行改进优化
		//由于我们所实现的erase会直接使用后面的值覆盖，但同时在迭代器遍历时又会让it++，这就使得it跳过了一部分元素，甚至是顺序表的end()导致越界崩溃
		vector<int> v3({ 1,2,3,4,4,5,6 });
		vector<int>::iterator it2 = v3.begin();
		while (it2 != v3.end())
		{
			if (*it2 % 2 == 0)
			{
				it2 = v3.erase(it2);	//为了避免第一种可能，所以改进erase，返回新的迭代器，以供更新
			}
			else 	//为了避免第二种可能，所以改进遍历时it自增的机制
			{
				it2++;
			}
		}
		//针对erase迭代器失效可以改进erase函数，对迭代器进行更新
		for (auto e : v3)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;
	
		//总结：迭代器失效发生在插入和删除数据(erase)时，要求在使用过insert、push_back、erase之后，原来的迭代器就不可以再使用，如果需要使用则需要先更新
	}
	void Test6()
	{
		vector<std::string> v1;
		v1.push_back("one");
		v1.push_back("two");
		v1.push_back("three");
		v1.push_back("four");
		v1.push_back("five");
		vector<int> const v2({ 1,2,3,4,5,6,7,8 });
		vector<std::string>::iterator it1 = v1.begin();
		while (it1 != v1.end())
		{
			std::cout << *it1 << ' ';
			++it1;
		}
		std::cout << std::endl;
		vector<int>::const_iterator it2 = v2.begin();
		while (it2 != v2.end())
		{
			std::cout << *it2 << ' ';
			++it2;
		}
		std::cout << std::endl;
		vector<std::string>::reverse_iterator rit1 = v1.rbegin();
		while (rit1 != v1.rend())
		{
			std::cout << *rit1 << ' ';
			++rit1;
		}
		std::cout << std::endl;
		vector<int>::const_reverse_iterator rit2 = v2.rbegin();
		while (rit2 != v2.rend())
		{
			std::cout << *rit2 << ' ';
			++rit2;
		}
		std::cout << std::endl;
	}
}