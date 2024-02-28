//inline int Add(int a, int b)
//{
//	return a + b;
//}
//int main()
//{
//	int c = 0;
//	c = Add(1, 2);
//	return 0;
//}
#include<iostream>
using namespace std;

//C语言
//auto：自动变量（局部变量）。一般省略不写
//static：静态区变量
//extern：外部变量
//C++：类型指示符
//int func()
//{
//	return 9;
//}
//int main()
//{
//	//auto可以根据初始化表达式推导实际类型
//	auto a = 1;
//	auto b = 1.24;
//	auto c = "hello";
//	auto d = func();
//	//typeid(变量).name()  可以打印出符号的类型
//	cout << typeid(a).name() << endl;	//int
//	cout << typeid(b).name() << endl;	//double
//	cout << typeid(c).name() << endl;	//char const* __ptr64
//	cout << typeid(d).name() << endl;	//int
//
//	return 0;
//}
//int main()
//{
//	int a = 1;
//	auto p1 = &a;
//	auto* p2 = &a;
//	//auto* p3 = a; //error
//	auto p3 = &p1;
//	auto p4 = &p3;
//	auto*** p5 = &p3;
//	//auto**** p6 = &p3; //error
//	auto& ra = a;
//	cout << typeid(p1).name() << endl;	//int * __ptr64
//	cout << typeid(p2).name() << endl;	//int * __ptr64
//	cout << typeid(p3).name() << endl;	//int * __ptr64 * __ptr64
//	cout << typeid(p4).name() << endl;	//int * __ptr64 * __ptr64 * __ptr64
//	cout << typeid(p5).name() << endl;	//int * __ptr64 * __ptr64 * __ptr64
//	cout << typeid(ra).name() << endl;	//int
//	return 0;
//}
//int main()
//{
//	auto a = 1, b = 8;
//	//auto c = 'k', d = 1.3; //error
//	return 0;
//}
//auto func1()
//{
//	return 1;
//}
////int func2(auto c) error
////{
////	return 2;
////}
//int main()
//{
//	auto a = func1();
//	cout << typeid(a).name() << endl;	//int
//	//auto b = func2(a);
//
//  //auto arr[3] = {1, 2, 3};	//error
//	return 0;
//}

//int main()
//{
//	int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	
//	//1.一般的for循环
//	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
//		cout << arr[i] << ' ';
//	cout << endl;
//
//	//2.基于范围的for循环
//	for (int num : arr) //类似于python  ---  for num in arr:
//		cout << num << ' ';
//	cout << endl;
//
//	return 0;
//}

void func(int a)
{
	cout << "int" << endl;
}
void func(int* a)
{
	cout << "int*" << endl;
}
int main()
{
	func(0);			//int
	func(NULL);			//int
	func((int*)NULL);	//int*
	func(nullptr);		//int*
}