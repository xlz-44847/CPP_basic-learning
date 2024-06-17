#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<string>

namespace my_stack {

	//template<class T>
	//class stack {
	//private:
	//	T* _a;
	//	int _top;
	//	int _capacity;
	//};

	//这样定义stack虽然可以，是我们在C语言中使用顺序表的写法
	//但是仔细思考，其中的核心顺序表可以使用已经存在的容器vector来替代
	//stack、queue包括priority_queue实际就是对其他容器进行了一层包装而得到的，所以称之为容器适配器
	//之所以叫容器适配器就是因为他们是将其他的容器进行转换，包装作为自己的底层从而实现新的功能
	//这种适配器的设计模式体现在代码中就是在类模板增加了一个选择底层容器的参数

	//在以往的学习中，栈的实现一般是采用vector进行实现
	//在这里，模板缺省值设置为deque这个容器
	
	//deque也是stl容器之一，叫做双端队列
	//deque<T>通过一个元素为T*的中控数组(vector)来管理数据，其每个元素都是一端连续空间(缓冲区)(vector）
	//deque有种类似于二维数组的感觉，但是要明确，中控数组中存储着缓冲区的地址，这样可以通过中控数组访问管理各个段的缓冲区
	//缓冲区各自连续，彼此之间不连续，所以中控数组的作用就是维持这样一个连续存储的假象，以方便访问
	//通过这种方式，deque就可以支持任意下标的访问，并且效率可观（因为存在着对下标进行计算，找到对应的缓冲区，再找到缓冲区中的元素，所以效率不及vector）
	//deque的另一个优点是无论是头部操作还是尾部操作效率都很高，因为其特殊的结构，在头尾操作时不需要移动任何元素，所以很快捷
	
	//deque的迭代器定义了一个元素的四个信息：
	// cur--当前元素的指针
	// first--当前元素所在缓冲区的起始指针
	// last--当前元素所在缓冲区的结尾指针
	// node--当前元素所在缓冲区在中控数组的指针
	
	//因此deque的优点就是在可以随机访问的同时头尾操作效率高，因此很适合头尾操作频繁的场景，所以stack和queue选择了deque作为容器

	template<class T,class Container = std::deque<T>>
	class stack {
	public:
		size_t size()
		{
			return _con.size();
		}
		bool empty()
		{
			return _con.empty();
		}
		void push(const T& x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_back();
		}
		const T& top()
		{
			return _con.back();
		}
	private:
		Container _con;
	};
	void Test1()
	{
		stack<int, std::vector<int>> s1;
		s1.push(1);
		s1.push(2);
		s1.push(3);
		while (!s1.empty())
		{
			std::cout << s1.top() << ' ';
			s1.pop();
		}
		std::cout << std::endl;
	}
	void Test2()
	{
		stack<std::string> s1;
		s1.push("hello");
		s1.push("the next");
		s1.push("final");
		while (!s1.empty())
		{
			std::cout << s1.top() << std::endl;
			s1.pop();
		}
	}
}