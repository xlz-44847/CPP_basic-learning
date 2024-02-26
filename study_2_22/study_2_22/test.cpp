//#include<iostream>
//using namespace std;
//int main()
//{
//	cout << "hello world" << endl;
//	return 0;
//}
//int main()
//{
//	// <<
//	//1.左移
//	int a = 2;
//	int b = a << 2;
//	//2.流插入
//	const char* str = "ccc\n";
//	cout << "hello world" << a << str << b << endl;
//	// >>
//	//1.右移
//	//2.流提取
//	cin >> a >> b;
//	cout << a << b;
//	return 0;
//}
//void func1(int a = 10, int b = 33)
//{
//	cout << a << ' ' << b << endl;
//}
//void func2(int a, int b = 79, int c = 88)
//{
//	cout << a << ' ' << b << ' ' << c << endl;
//}
//int main()
//{
//	func1(7, 9); //7 9
//	func1(23);   //23 33
//	func1();     //10 33
//	func2(1,62,35);  //1 62 35
//	func2(48,29);    //48 29 88
//	func2(12);       //12 79 88
//	//func2();       //error
//	return 0;
//}
//void func(int a = 10, int b) //error
//{
//	cout << a << ' ' << b << endl;
//}
//
//int main()
//{
//	func(7, 9); //7 9
//	return 0;
//}
//#include"test.h"
#include<iostream>
using namespace std;
void func(int a, int b = 10)
{
	cout << a + b << endl;
}
void func(int a,int b);
int main()
{
	func(1);
	return 0;
}