#include<iostream>
using namespace std;

//struct Stack {
//	//C++的结构体内既可以定义变量，也可以定义函数
//	//变量
//	int* _arr;
//	int _capacity;
//	int _top;
//	//函数
//	void Init(int capacity = 4)
//	{
//		_arr = (int*)malloc(sizeof(int) * capacity);
//		if (_arr == nullptr)
//		{
//			perror("malloc fail");
//			return;
//		}
//		_capacity = capacity;
//		_top = 0;
//	}
//};
//int main()
//{
//	//定义结构体变量可以不加struct
//	struct Stack st1;
//	Stack st2;
//	//调用成员函数
//	st1.Init();
//	st2.Init(8);
//}

//class Date
//{
//	int _year;
//	int _month;
//	int _day;
//	void Show()
//	{
//		cout << _year << '-' << _month << '-' << _day << endl;
//	}
//};

//#include"date.h"
//void Date::Show()
//{
//	cout << _year << '-' << _month << '-' << _day << endl;
//}

//struct Stack {
//	int* _arr;
//	int _capacity;
//	int _top;
//	
//	void Init(int capacity = 4)
//	{
//		_arr = (int*)malloc(sizeof(int) * capacity);
//		if (_arr == nullptr)
//		{
//			perror("malloc fail");
//			return;
//		}
//		_capacity = capacity;
//		_top = 0;
//	}
//private:
//	void Show()
//	{}
//};
//class Date
//{
//	int _year;
//	int _month;
//	int _day;
//
//public:
//	void Init(int year = 2000, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	void Show()
//	{
//		cout << _year << '-' << _month << '-' << _day << endl;
//	}
//};
//
//int main()
//{
//	struct Stack st1;
//	//struct默认访问权限是public
//	st1.Init();
//	int a = st1._capacity;
//	//st1.Show();//error
//
//	Date d1;
//	//class默认访问权限是private
//	//d1._year = 2024; //error
//	d1.Init();
//	d1.Show(); 
//
//	//Date.Init(); //error 没有实例化
//}

//class C1
//{
//	int a;
//	char c;
//	double d;
//	void func()
//	{}
//};
//class C2
//{
//	void func()
//	{}
//};
//class C3
//{};
//
//int main()
//{
//	cout << sizeof(C1) << endl; //16
//	cout << sizeof(C2) << endl; //1
//	cout << sizeof(C3) << endl; //1
//}
//class Date
//{
//	int _year;
//	int _month;
//	int _day;
//
//public:
//	//void Init(Date* const this, int year = 2000, int month = 1, int day = 1)
//	void Init(int year = 2000, int month = 1, int day = 1)	
//	{
//		this->_year = year;
//		_month = month;
//		_day = day;
//	}
//	//void Show(Date* const this)
//	void Show()
//	{
//		cout << _year << '-' << _month << '-' << _day << endl;
//	}
//};
//int main()
//{
//	Date d1;
//	d1.Init(2024, 2, 25);
//	d1.Show();
//}

class C
{
public:
	int _a;

	void func()
	{
		cout << "func()" << endl; //没有使用this指针，所以没有空指针解引用，不报错
		//cout << _a << endl; //error 实际上是this->_a，this是空指针，所以报错
	}
};
int main()
{
	C c1;
	C* pc = nullptr;
	pc->func(); //-> 不解引用，而是将pc作为参数传给this，this接收参数，值为nullptr
	(*pc).func(); //. 不解引用，也是将pc传给this指针，this接收参数，值为nullptr
}