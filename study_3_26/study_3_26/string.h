#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>

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
		////拷贝构造函数
		//string(const string& s)	//string对象中有_str，需要深拷贝
		//{
		//	_str = new char[s._capacity + 1];
		//	strcpy(_str, s._str);
		//	_capacity = s._capacity;
		//	_size = s._size;
		//}
		//拷贝构造函数——函数复用
		string(const string& s)
		{
			string tmp(s._str);
			swap(tmp);
			//创建临时变量tmp，交换tmp和*this，这样*this就完成了拷贝，同时出函数后指向空的对象tmp会被销毁
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
		////赋值重载函数
		//string& operator=(string& s)
		//{
		//	char* tmp = new char[s._capacity + 1];	//使用一个临时字符数组开辟空间，保存待拷贝的字符串
		//	strcpy(tmp, s._str);

		//	delete[] _str;	//原string对象可能已有值，所以需要先释放空间，然后再把新开辟的带有已有字符串的空间赋值给对象
		//	_str = tmp;
		//	_size = s._size;
		//	_capacity = s._capacity;
		//
		//	return *this;
		//}
		////赋值重载函数——函数复用1
		//string& operator=(string& s)
		//{
		//	string tmp(s);
		//	swap(tmp);

		//	return *this;
		//	//拷贝构造创建临时对象tmp，然后和this交换，this就是和s相同的对象，而tmp在出作用域就销毁
		//}
		//赋值重载函数——函数复用2
		string& operator=(string tmp)
		{
			swap(tmp);

			return *this;
			//函数传参传了对象，所以会默认调用一次拷贝构造构造tmp，然后交换tmp和this，出了函数就会销毁tmp
		}
		//reserve(size_t n):重设capacity
		//	n>capacity:扩容
		//	n<=capacity:不做处理
		void reserve(size_t n)
		{
			if (n > _capacity)	//当n<=_capacity直接return
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);

				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}
		//resize(int n,char c):
		//	n>size:将size扩大至n，扩展出的空间使用参数c进行填充
		//	n<=size:将size缩小至n，直接截断原字符串
		void resize(size_t n, char c = '\0')
		{
			if (n > _size)
			{
				reserve(n);	//扩容,如果不需要扩容reserve就不会发生作用

				for (size_t i = _size; i < n; i++)
				{
					_str[i] = c;
				}
			}
			_str[n] = '\0';	//n<size，就截断；n>size，就在末尾补'\0'
			_size = n;
		}
		//clear:将字符串置为空
		void clear()
		{
			_size = 0;	//置空只需要将size置为0，然后注意字符串以'\0'结尾
			_str[_size] = '\0';
		}
		//push_back：尾插字符
		void push_back(char c)
		{
			if (_size == _capacity)	//判断容量是否足够
			{
				reserve(_capacity == 0 ? 4 : 2 * _capacity);	//扩容交给reserve，需要考虑capacity==0的情况
			}
			_str[_size] = c;
			++_size;
			_str[_size] = c;
		}
		//append：尾插字符串
		void append(const char* str)	//使用c_str做参数，类型是const char*，所以如果参数写成char*，权限放大会报错
		{
			size_t len = strlen(str);
			reserve(_size + len);

			strcpy(_str + _size, str);	//strcpy会自动补一个'\0'
			_size += len;
		}
		//+=运算符重载：1.尾插字符；2.尾插字符串
		string& operator+=(char c)
		{
			push_back(c);
			return *this;
		}
		string& operator+=(const char* str)	//使用c_str做参数，类型是const char*，所以如果参数写成char*，权限放大会报错
		{
			append(str);
			return *this;
		}
		//insert：1.在pos下标位置插入字符；2.在pos下标位置插入字符串
		void insert(size_t pos, char c)
		{
			assert(pos <= _size);

			if (_size == _capacity)	//判断容量是否足够
			{
				reserve(_capacity == 0 ? 4 : 2 * _capacity);	//扩容交给reserve，需要考虑capacity==0的情况
			}

			size_t end = _size + 1;	//注意此处end是交换后的下标，所以极端情况（头插）下最小为0，可以用size_t
									//如果end=_size则是交换前的下标，极端情况下最小为-1，所以只可以使用int类型
			while (end > pos)	//最后一次交换：pos位置换到pos+1位置，end是交换后的下标，所以大于pos即可
			{
				_str[end] = _str[end - 1];
				--end;
			}
			_str[pos] = c;
			++_size;
		}
		void insert(size_t pos, const char* str)
		{
			assert(pos <= _size);

			size_t len = strlen(str);
			reserve(_capacity + len);

			size_t end = _size + len;	//注意此处end是交换后的下标，所以极端情况（头插）下最小为0，可以用size_t
			//如果end=_size则是交换前的下标，极端情况下最小为-1，所以只可以使用int类型
			while (end > pos + len - 1)	//最后一次交换：pos位置换到pos+len的位置，end是交换后的下标，所以需要大于pos+len-1
			{
				_str[end] = _str[end - len];
				--end;
			}
			strncpy(_str + pos, str, len);
			_size += len;
		}
		//erase：删除pos位置开始的len个字符
		void erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);

			if (len >= _size - pos)	//截断的情况
			//删除的末尾位置超过或就是字符串的最后一个字符len+pos>=_size，这个表达式len+pos可能会溢出;或者剩余字符长度小于等于待删除字符长度len>=_size-pos，不存在溢出风险
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);	//直接将后续字符覆盖到pos位置
				_size -= len;
			}
		}
		//swap：交换两个string对象
		void swap(string& s)	//swap在C++中以函数模板存在，所以对于自定义类型需要自主实现
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}
		//find：寻找字符串中pos开始首个匹配的字符、子串的下标，找不到就返回npos
		size_t find(char c, size_t pos = 0) const
		{
			assert(pos < _size);

			for (size_t i = pos; i < _size; i++)
			{
				if (_str[i] == c)
				{
					return i;
				}
			}
			return npos;
		}
		size_t find(const char* str, size_t pos = 0) const
		{
			assert(pos < _size);

			const char* tmp = strstr(_str, str);
			if (tmp == nullptr)
			{
				return npos;
			}
			else
			{
				return tmp - _str;
			}
		}
		//substr：将pos位置开始len长度的字符串作为string对象
		string substr(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);

			string ret;
			if (len < _size - pos)	//拷贝不到原字符串结尾,避免溢出
			{
				for (size_t i = pos; i < pos + len; i++)	//拷贝到pos+len
				{
					ret += _str[i];
				}
			}
			else	//拷贝剩余所有字符
			{
				for (size_t i = pos; i < _size; i++)	//拷贝到_size
				{
					ret += _str[i];
				}
			}
			return ret;
		}
	private:
		size_t _size;
		size_t _capacity;
		char* _str;
	public:
		static const size_t npos;	//声明静态成员变量npos，属于整个类共享
	};

	const size_t m_string::string::npos = -1;	//静态成员变量在类内声明，在类外定义，需要注意npos的所在域：命名空间m_string内的类string的静态成员npos

	//在使用swap时一般会用swap(s1,s2)的形式，所以需要再写一个swap来满足该种形式的调用
	void swap(string& s1, string& s2)
	{
		s1.swap(s2);
	}

	//比较操作符重载，因为需要支持char*和string比较，所以全局重载，若在类中重载，那么this指针必然是第一个参数，就无法支持char*在==的左侧了
	//由于单参数构造支持隐式类型转换，所以char*会变为string类型进行比较，因而支持了string和char*之间的任意次序的比较
	bool operator==(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) == 0;
	}
	bool operator!=(const string& s1, const string& s2)
	{
		return !(strcmp(s1.c_str(), s2.c_str()) == 0);
	}
	bool operator<(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) < 0;
	}
	bool operator<=(const string& s1, const string& s2)
	{
		return s1 < s2 || s1 == s2;
	}
	bool operator>(const string& s1, const string& s2)
	{
		return !(s1 <= s2);
	}
	bool operator>=(const string& s1, const string& s2)
	{
		return !(s1 < s2);
	}
	//流插入
	ostream& operator<<(ostream& out, const string& s)
	{
		for (auto e : s)	//使用迭代器遍历，因为编译器支持内置类型的流插入，所以直接使用就好
		{
			out << e;
		}
		return out;
	}
	//流提取：遇到空格字符或换行字符就结束
	istream& operator>>(istream& in, string& s)
	{
		s.clear();	//流提取是覆盖原数据，所以需要先清空

		char buff[128];
		size_t cou = 0;

		char c;
		//in >> c;	//C++规定：流提取自动忽略空格字符和换行字符
		c = in.get();	//使用istream类的成员函数get来读取字符
		while (c != ' ' && c != '\n')	//当没有读到空格字符和换行字符时就继续
		{
			//s += c;	//一个字符一个字符的尾插效率不高
			
			//使用一个buff数组当做缓冲区，当缓冲区满了之后一并尾插，提高效率
			buff[cou++] = c;
			if (cou == 127)
			{
				buff[cou] = '\0';
				s += buff;
				cou = 0;
			}

			c = in.get();
		}

		if (cou > 0)	//最后缓冲数组还有数据，则全部尾插
		{
			buff[cou] = '\0';
			s += buff;
		}

		return in;
	}
	//getline：只在遇到换行字符结束
	//		   和流插入只在while判断处不同
	istream& getline(istream& in, string& s)
	{
		s.clear();

		char buff[128];
		size_t cou = 0;

		char c;
		c = in.get();
		while (c != '\n')	//没有读到换行字符时就继续
		{
			buff[cou++] = c;
			if (cou == 127)
			{
				buff[cou] = '\0';
				s += buff;
				cou = 0;
			}

			c = in.get();
		}

		if (cou > 0)
		{
			buff[cou] = '\0';
			s += buff;
		}

		return in;
	}

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

	void Test2()
	{
		string s1("hello world");
		string s2;
		s2 = s1;
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		s1.resize(4);
		s2.resize(15, '&');
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		s2.clear();
		s1.push_back('%');
		s1.append("44847");
		s1 += '#';
		s1 += "114514";
		s1.insert(0, 'L');
		s1.insert(0, "!!!");
		cout << s2.c_str() << endl;
		cout << s1.c_str() << endl;
	}

	void Test3()
	{
		cout << string().npos << endl;
		string s1;
		getline(cin, s1);
		cout << (s1 >= "hello") << endl;
		s1.erase(s1.find('l',0), 1);
		cout << s1 << endl;
		s1.erase(s1.find("wor"));
		string s2 = s1.substr(s1.find("l",2));
		string s3 = s1.substr(s1.find("o",3),4);
		cout << s1 << endl;
		cout << s2 << endl;
		cout << s3 << endl;
		string s4("lucky~");
		cin >> s4;
		swap(s1, s4);
		cout << s1 << endl;
		cout << s4 << endl;
	}
}