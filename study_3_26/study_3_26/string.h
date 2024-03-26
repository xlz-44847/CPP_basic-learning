#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;	//展开std命名空间，对标识符的搜索先局部在全局，所以在以下m_string的命名空间中，所有标识符会优先搜索局部，即m_string中的标识符

namespace m_string	//定义一个新的命名空间，将我们实现的string放在其中，防止和std中的string产生冲突
{
	class string
	{
	public:
		//构造函数
		string(const char* str = "")	//构造函数，全缺省输入c字符串，当无输入的时候""也有一个\0，不会产生错误
			:_size(strlen(str)),
			_capacity(_size),
			_str(new char[_capacity + 1])	//初始化列表，初始化顺序按照成员变量声明顺序，_str需要多开一个空间存储\0
		{
			strcpy(_str, str);	//使用strcpy进行赋值操作
		}
		//c_str，作用是返回一个C字符串
		const char* c_str() const	//函数内和返回值都不会修改，所以const修饰this指针，const修饰返回值
		{
			return _str;
		}
		//拷贝构造函数
		string(const string& s)	//string对象中有_str，需要深拷贝
		{
			_str = new char[s._capacity + 1];
			strcpy(_str, s._str);
			_capacity = s._capacity;
			_size = s._size;
		}
		//析构函数
		~string()	//由于_str，所以需要主动实现析构函数
		{
			delete[] _str;
			_str = NULL;
			_capacity = _size = 0;
		}
		//size，返回string的长度
		size_t size() const
		{
			return _size;
		}
		//capacity，返回string容量
		size_t capacity() const
		{
			return _capacity;
		}
		//[]重载，需要重载const和非const版本，保证非const对象可以被修改，而const对象不可修改
		char& operator[](size_t pos)	//针对非const对象，返回对应下标字符的引用
		{
			return _str[pos];
		}
		const char& operator[](size_t pos) const	//针对const对象，返回对应下标字符的const引用
		{
			return _str[pos];
		}
		//非const迭代器
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		//const迭代器
		typedef const char* const_iterator;
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
		
	private:
		size_t _size;
		size_t _capacity;
		char* _str;
	};

	void Test1()
	{
		string s1("hello world");
		string s2(s1);
		cout << s2.c_str() << endl;
		cout << s2.size() << endl;
		cout << s2.capacity() << endl;
		cout << s2[2] << endl;
		const string s3(s1);
		s2[1] = 'h';
		//s3[4] = 'l';	//const对象调用const的[]重载
		string::iterator it = s2.begin();
		while (it != s2.end())
		{
			cout << *it;
			it++;
		}
		cout << endl;
		string::const_iterator cit = s3.begin();
		while (cit != s3.end())
		{
			cout << *cit;
			cit++;
		}
		cout << endl;
	}

}