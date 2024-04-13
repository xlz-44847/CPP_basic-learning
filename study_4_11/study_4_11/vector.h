#pragma once

#include<iostream>
#include<assert.h>
#include<string.h>


namespace m_vector	//为自己实现的vector定义一个命名空间
{
	template<class T>	//使用类模板
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;	//定义迭代器为T*类型
		
		//构造函数
		//无参构造，成员参数全部初始化为空指针
		vector()
		{}
		//拷贝构造
		//拷贝构造需要一些成员函数的辅助
		vector(const vector<T>& v)
		{

		}

		//析构函数
		~vector()
		{
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
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
				memcpy(tmp, _start, size() * sizeof(T));
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
		void erase(iterator pos)
		{
			assert(pos < _finish && pos >= _start);

			iterator it = pos;
			while (it != _finish)
			{
				*it = *(it + 1);
				++it;
			}
			--_finish;
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

}