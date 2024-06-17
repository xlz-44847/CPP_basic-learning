#pragma once
#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<string>

namespace my_queue {
	template<class T, class Container = std::deque<T>>
	class queue {
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
			_con.pop_front();
		}
		const T& front()
		{
			return _con.front();
		}
		const T& back()
		{
			return _con.back();
		}
	private:
		Container _con;
	};

	void Test1()
	{
		queue<int, std::list<int>> s1;
		s1.push(1);
		s1.push(2);
		s1.push(3);
		while (!s1.empty())
		{
			std::cout << s1.front() << ' ' << s1.back() << ',';
			s1.pop();
		}
		std::cout << std::endl;
	}
	void Test2()
	{
		queue<std::string> s1;
		s1.push("hello");
		s1.push("the next");
		s1.push("final");
		while (!s1.empty())
		{
			std::cout << s1.front() << std::endl;
			s1.pop();
		}
	}

	//priority_queue是stl的容器之一，叫作优先队列
	//优先队列实际就是我们所学过的堆的数据结构的容器，默认是大堆
	//之所以取名叫作优先队列，是因为对于堆而言，最有价值的就是堆顶的元素，因为堆顶的元素是所有元素中的最大或最小的一个，堆的各种应用也是利用了这一点
	//所以因为其首元素的特殊特征，所以认为是队列中优先级最高的元素，所以称为优先队列

	//priority_queue也是采取适配器模式，默认使用的底层容器是vector
	//回忆堆的知识会发现，堆的最关键的向上调整和向下调整会涉及到频繁的随机下标访问，而下标访问最佳的就是vector，所以采用vector作为容器适配器

	//priority_queue为了区分建立大堆和小堆，给出了第三个模板参数，需要通过传递仿函数来选择生成大小堆
	//我们知道大队和小堆的关键区别在于向下调整和向上调整的比较的逻辑
	//在C语言中，我们为了可以灵活处理大堆小堆的不同情况，采取了函数指针的方式来区别大堆小堆的行为
	//在C++11中，给出了一种新的方法来完成这一步操作，那就是仿函数
	
	//仿函数：如其名，仿函数并不是一个函数，而是一个类，只是使用方法类似于函数
	//仿函数的类重载了()这个运算符，所以可以使用这个类的实例化对象调用()重载函数，而运算符重载的调用方式是直接使用在对象上即可
	//因此这样的调用方式在形式上就类似于函数调用，对象(参数) 的方式进行调用

	//如对于priority_queue，实现大堆利用的就是less仿函数，less的()重载了小于比较，因此调用()时完成的就是两个参数之间的小于比较
	//实现小堆则利用的是greater仿函数，其将()重载为了大于比较

	//对于仿函数的调用方式，首先要明确虽然称作仿函数，但实际上仍然只是一个类，调用仿函数实际上就是在调用类的成员函数
	//所以在调用时首先需要实例化对象，因为我们的目的是调用仿函数，所以可以实例化为有名对象，也可以是匿名对象
	//然后利用对象进行()运算符的重载函数的调用，对象(参数) ，因为()运算符的调用方式就是这样，类似于函数，所以才叫仿函数

	template<class T>
	class less {
	public:
		bool operator()(const T& e1, const T& e2) {
			return e1 < e2;
		}
	};

	template<class T>
	class greater {
	public:
		bool operator()(const T& e1, const T& e2) {
			return e1 > e2;
		}
	};

	template<class T, class Container = std::vector<T>, class Compare = less<T>>
	class priority_queue {
	public:
		size_t size()
		{
			return _con.size();
		}
		bool empty()
		{
			return _con.empty();
		}
		void adjust_up(size_t child)
		{
			size_t parent = (child - 1) / 2;
			while (child > 0)
			{
				//Compare cmp;
				//if (_con[child] > _con[parent])	//大堆
				//if (_con[child] < _con[parent])	//小堆
				if(Compare()(_con[parent],_con[child]))	//仿函数（匿名对象）
				{
					std::swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
		void push(const T& x)
		{
			_con.push_back(x);
			adjust_up(_con.size()-1);
		}
		void adjust_down(size_t parent)
		{
			Compare cmp;
			size_t child = parent * 2 + 1;
			while (child < _con.size())
			{
				//if (child + 1 < _con.size() && _con[child] < _con[child + 1])	//大堆
				//if (child + 1 < _con.size() && _con[child] > _con[child + 1])	//小堆
				if (child + 1 < _con.size() && cmp(_con[child] , _con[child + 1]))	//仿函数（有名对象）
				{
					++child;
				}
				//if (_con[child] > _con[parent])	//大堆
				//if (_con[child] < _con[parent])	//小堆
				if (cmp(_con[parent] , _con[child]))	//仿函数
				{
					std::swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		void pop()
		{
			std::swap(_con[0], _con[_con.size()-1]);
			_con.pop_back();
			adjust_down(0);
		}
		const T& top()
		{
			return _con.front();
		}
	private:
		Container _con;
	};

	void Test3()
	{
		priority_queue<int, std::vector<int>> s1;
		s1.push(1);
		s1.push(2);
		s1.push(9);
		s1.push(4);
		s1.push(8);
		s1.push(3);
		while (!s1.empty())
		{
			std::cout << s1.top() << ' ';
			s1.pop();
		}
		std::cout << std::endl;
	}
	void Test4()
	{
		priority_queue<std::string> s1;
		s1.push("hello");
		s1.push("the next");
		s1.push("final");
		while (!s1.empty())
		{
			std::cout << s1.top() << std::endl;
			s1.pop();
		}
	}
	void Test5()
	{
		priority_queue<int, std::vector<int>, greater<int>> s1;
		s1.push(1);
		s1.push(2);
		s1.push(9);
		s1.push(4);
		s1.push(8);
		s1.push(3);
		while (!s1.empty())
		{
			std::cout << s1.top() << ' ';
			s1.pop();
		}
		std::cout << std::endl;
	}
	//仿函数的出现，是为了取代C语言中函数指针的作用，所以有的时候需要仿函数参数的函数调用，我们需要根据自己的需求自己实现对应的仿函数，这个和回调函数的思考方式是一样的
	//以优先队列的比较为例：
	//string重载了比较运算符，所以我们才可以直接使用之less和greater来作为仿函数
	void Test6()
	{
		priority_queue < std::string, std::vector<std::string>, greater<std::string>> s1;
		s1.push("hello");
		s1.push("the next");
		s1.push("final");
		while (!s1.empty())
		{
			std::cout << s1.top() << std::endl;
			s1.pop();
		}
	}
	//对于其他没有重载比较运算符的自定义类型，就需要自己实现比较逻辑来交给优先队列
	struct A {
		int a;
		char c;
	};
	//可以看到，仿函数的类不一定需要类模板，在priority_queue实例化时是类即可
	class A_less_a {
	public:
		bool operator()(const A& e1, const A& e2)
		{
			return e1.a < e2.a;
		}
	};
	template<class T>
	class A_less_c {
	public:
		bool operator()(const T& e1, const T& e2)
		{
			return e1.c < e2.c;
		}
	};
	std::ostream& operator<<(std::ostream& out, const A& a)
	{
		out << a.a << ',' << a.c;
		return out;
	}
	void Test7()
	{
		priority_queue<A, std::vector<A>, A_less_a> q;
		q.push({ 7,'f' });
		q.push({ 3,'j' });
		q.push({ 10,'b' });
		q.push({ 9,'a' });
		q.push({ 2,'p' });
		q.push({ 5,'k' });
		while (!q.empty())
		{
			std::cout << q.top() << std::endl;
			q.pop();
		}
	}
	void Test8()
	{
		priority_queue<A, std::vector<A>, A_less_c<A>> q;
		q.push({ 7,'f' });
		q.push({ 3,'j' });
		q.push({ 10,'b' });
		q.push({ 9,'a' });
		q.push({ 2,'p' });
		q.push({ 5,'k' });
		while (!q.empty())
		{
			std::cout << q.top() << std::endl;
			q.pop();
		}
	}
}