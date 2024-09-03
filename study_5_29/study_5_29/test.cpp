//非类型模板参数
//#include"array.h"
//
//int main()
//{
//	//m_array::Test1();
//}


#include<iostream>
using namespace std;
//函数模板的特化
//对于一些特殊类型使用函数模板可能所需要的形式不一样

namespace test1
{
	//对于一个比较大小的模板函数：
	template<class T>
	bool myless(T e1, T e2)
	{
		cout << "bool myless(T e1, T e2)" << endl;
		return e1 < e2;
	}
	void Test1()
	{
		int a = 20, b = 10;
		int* pa = &a, * pb = &b;
		cout << myless(a, b) << endl;	//1
		cout << myless(pa, pb) << endl;	//0
		//可见这是因为函数模板实例化的类型不同，所以调用的<操作符的重载函数也就不同：整型比较值，指针比较地址

		//这似乎不是我们想要的结果，出现这种问题模板和调用双方都有问题
		//调用者应该清楚模板使用方法，想要比较指针的值不应该简单的把指针作为参数，而是应该解引用后传参
		cout << myless(*pa, *pb) << endl;	//1
		//模板也有问题，模板考虑到指针类型的比较做出修改也可以顺利解决这个问题，因此就引出了函数模板特化
		//函数模板的特化：在原模板的基础上为了支持特殊类型的实例化做出的特殊化处理
	}
}
namespace test2
{
	//函数模板的特化
	template<class T>
	bool myless(T e1, T e2)
	{
		cout << "bool myless(T e1, T e2)" << endl;
		return e1 < e2;
	}
	//特化首先必须要有一个函数模板，然后需要使用template<>，然后在之后定义特化的函数，在尖括号中写明特化类型，并参考模板写参数
	//函数模板特化可以存在多个类型的特化
	template<>
	bool myless<int*>(int* e1, int* e2)
	{
		cout << "bool myless<int*>(int* e1, int* e2)" << endl;
		return *e1 < *e2;
	}
	template<>
	bool myless<double*>(double* e1, double* e2)
	{
		cout << "bool myless<double*>(double* e1, double* e2)" << endl;
		return *e1 < *e2;
	}

	void Test1()
	{
		int a = 20, b = 10;
		int* pa = &a, * pb = &b;
		double c = 9.9, d = 8.7;
		cout << myless(a, b) << endl;	//0
		cout << myless(pa, pb) << endl;	//0
		cout << myless(c, d) << endl;	//0
	}
}
namespace test3
{
	template<class T>
	bool myless(T e1, T e2)
	{
		cout << "bool myless(T e1, T e2)" << endl;
		return e1 < e2;
	}
	//也可以再重载一种函数模板，专门用于接受指针
	//将模板参数定义为T*，在传递指针的时候会优先实例化调用这个函数
	//相较于特化更简单，更建议使用
	template<class T>
	bool myless(T* e1, T* e2)
	{
		cout << "bool myless(T* e1, T* e2)" << endl;
		return *e1 < *e2;
	}

	void Test1()
	{
		int a = 20, b = 10;
		int* pa = &a, * pb = &b;
		double c = 9.9, d = 8.7;
		cout << myless(a, b) << endl;	//0
		cout << myless(pa, pb) << endl;	//0
		cout << myless(c, d) << endl;	//0
	}
}
//类模板特化
//和函数模板特化类似，特化首先必须要有一个类模板，然后需要使用template<>，然后在之后定义特化的函数，在尖括号中写明特化类型，并参考模板写参数
//特化同样可以不只一个，template<>的尖括号中的其实是未被特化的参数
namespace test4
{
	template<class T1, int N, class T2>
	class A
	{
	public:
		A()
		{
			cout << "A< T1, N, T2>" << endl;
		}
	};
	//全特化
	//全特化没有未被确定的参数，所以template<>中没有内容
	template<>
	class A<int, 100, char>
	{
	public:
		A()
		{
			cout << "A< int, 100, char>" << endl;
		}
	};
	//半特化、偏特化
	//偏特化存在未被确定的参数，所以template<>中有内容
	//半特化的参数和半缺省一样，需要从后往前确定，不可以跳跃
	template<class T,int N>
	class A<T, N, char>
	{
	public:
		A()
		{
			cout << "A< T, N, char>" << endl;
		}
	};
	//半特化也可以是对参数进行进一步的限制
	template<class T1, int N, class T2>
	class A<T1&, N, T2*>
	{
	public:
		A()
		{
			cout << "A< T1&, N, T2*>" << endl;
		}
	};
	
	void Test1()
	{
		A<int, 10, int> a1;	//没有特化
		A<int, 100, char> a2;	//全特化
		A<int, 90, char> a3;	//半特化
		A<double, 30, int> a4;	//没有特化
		A<int&, 990, char*> a5;	//半特化

	}
}

#include"array.h"

int main()
{
	//test1::Test1();
	//test2::Test1();
	//test3::Test1();
	test4::Test1();
	m_array::array<int, 5> a1;
	cout << a1.size() << endl;	
}