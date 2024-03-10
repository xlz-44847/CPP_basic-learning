#include<iostream>
using namespace std;

////函数模板
//template<typename T>
//void Swap(T& a, T& b)
//{
//	T tmp = a;
//	a = b;
//	b = tmp;
//}
////模板和函数可以同时存在，调用时优先选择函数
////如果函数不够匹配，则使用模板
//void Swap(int& a, int& b)
//{
//	int tmp = a;
//	a = b;
//	b = tmp;
//}
//int main()
//{
//	int a1 = 10, a2 = 20;
//	cout << a1 << ' ' << a2 << endl;
//	Swap(a1, a2);	//函数模板实例化，int类型	//使用函数
//	cout << a1 << ' ' << a2 << endl;
//	
//	double d1 = 1.2, d2 = 3.7;
//	cout << d1 << ' ' << d2 << endl;
//	Swap(d1, d2);	//函数模板实例化，double类型	//使用模板
//	cout << d1 << ' ' << d2 << endl;
//	Swap<double>(d1, d2);	//函数模板显式实例化	//显示实例化强制使用模板
//	cout << d1 << ' ' << d2 << endl;
//
//	return 0;
//}
//
//template<class T1,class T2>	//模板参数可以多个，以逗号分隔，关键字也可以是class
//void func()
//{}



//类模板
template<class T>
class Stack
{
public:
	void Push(T x)
	{}
private:
	T* _a;
	int _size;
	int _capacity;
};
int main()
{
	Stack<int> st1;	//类模板实例化
	Stack<double> st2;
	return 0;
}