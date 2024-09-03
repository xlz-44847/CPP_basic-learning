#pragma once

//array也是容器之一，它是定长数组
//和vector对比，array是一个有着固定长度的静态数组，vector是一个长度可变的动态数组
//array相当于把普通的静态数组进行了一定的包装，给出了一些方便使用的成员函数

namespace m_array
{
	//模板参数分为 类型模板参数 和 非类型模板参数
	//类型模板参数：在模板参数列表中使用class或者typename标识
	//非类型模板参数：在模板参数列表中不需要关键字，类似于函数传参的形式
	//非类型模板参数只能是整型家族，可以任意个且无顺序要求
	template<class T,size_t N = 10>
	class array
	{
	public:
		size_t size() const;
		size_t empty() const
		{
			return _size == 0;
		}
		T& operator[](size_t pos)
		{
			return _array[pos];
		}
		//实例化模板时按需实例化，只有被调用了的成员才会被实例化
		//但是在vs环境下会被进行语法检查
		const T& operator[](size_t pos) const
		{
			return _array[pos];
		}
	private:
		T _array[N];
		size_t _size = N;
	};
	//两个文件都包含了.h，所以.h中不可以出现函数定义，否则就会重定义
	//void Test1()
	//{
	//	//array<int> a1;
	//	//array<double,5> a2;
	//	
	//	//一般不使用array而使用vector
	//	//vector在堆中，长度可控，可以在创建时被初始化，具有越界检查
	//	//array在栈中，长度固定，没有初始化，越界检查只在数组后的几个位置进行抽查
	//}
}
