#pragma once

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

	private:	//成员变量都是迭代器变量的形式（指针），尽量贴合库中的形式
		iterator _start = nullptr;	//vector起始地址
		iterator _finish = nullptr;	//vector最后一个数据的下一个地址
		iterator _endofstorage = nullptr;	//vector开辟的空间的下一个地址
		//全部给定缺省值为空指针
	};

}