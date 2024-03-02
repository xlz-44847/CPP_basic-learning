#include<iostream>
using namespace std;
//class Stack
//{
//private:
//	int* _arr;
//	int _capacity;
//	int _top;
//public:
//	Stack(int capacity = 4)
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
//	void Push(int x)
//	{
//		//CheckCapacity();
//		_arr[_top++] = x;
//	}
//	void Print()
//	{
//		cout << _capacity << ' ' << _top << endl;
//	}
//	~Stack()
//	{
//		free(_arr);
//		_arr = nullptr;
//		_capacity = 0;
//		_top = 0;
//	}
//};
//int main()
//{
//	Stack st1;
//	st1.Print();
//	st1.Push(3);
//}
//class Time
//{
//public:
//	~Time()
//	{
//		cout << "~Time()" << endl;
//	}
//private:
//	int _hour;
//	int _minute;
//	int _second;
//};
//class Date
//{
//private:
//	// 基本类型(内置类型)
//	int _year = 1970;
//	int _month = 1;
//	int _day = 1;
//	// 自定义类型
//	Time _t;
//};
//int main()
//{
//	Date d;
//	return 0;
//	//output:
//	//~Time()
//}
//class Date
//{
//public:
//	Date(int year = 1)
//	{
//		_year = year;
//		cout << "Date()->" << _year << endl;
//	}
//
//	~Date()
//	{
//		cout << "~Date()->" << _year << endl;
//	}
//private:
//	int _year;
//};
//
//void func()
//{
//	Date d3(3);
//	static Date d4(4);
//}
//void func1()
//{
//	Date d3(9);
//	static Date d4(10);
//}
//
//Date d5(5);
//static Date d7(7);
//Date d6(6);
//static Date d8(8);
//
//int main()
//{
//	func1();
//	Date d1(1);
//	Date d2(2);
//	func();
//
//	return 0;
//}
//class Date
//{
//private:
//	int _year;
//	int _month;
//	int _day;
//public:
//	Date(int year, int month, int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	void Print()
//	{
//		cout << _year << ' ' << _month << ' ' << _day << endl;
//	}
//};
//int main()
//{
//	Date d1(2024, 2, 27);
//	d1.Print();
//	Date d2(d1);
//	d2.Print();
//}
//class Date
//{
//private:
//	int _year;
//	int _month;
//	int _day;
//public:
//	Date(int year, int month, int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	Date(const Date& d)
//	{
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//	void Print()
//	{
//		cout << _year << ' ' << _month << ' ' << _day << endl;
//	}
//};
//void func(Date d)
//{}
//int main()
//{
//	Date d1(2024,2,27);
//	func(d1);
//	d1.Print();
//	Date d2(d1);
//	d2.Print();
//}
//class Time
//{
//public:
//	Time()
//	{
//		_hour = 1;
//	}
//	Time(const Time& t)
//	{
//		_hour = t._hour;
//		cout << "Time::Time(const Time&)" << endl;
//	}
//private:
//	int _hour;
//};
//class Date
//{
//private:
//	// 基本类型(内置类型)
//	int _year = 2000;
//	// 自定义类型
//	Time _t;
//};
//int main()
//{
//	Date d1;
//	Date d2(d1);
//	return 0;
//	//oupput:
//	//Time::Time(const Time&)
//}
class Stack
{
private:
	int* _arr;
	int _capacity;
	int _top;
public:
	Stack(int capacity = 4)
	{
		_arr = (int*)malloc(sizeof(int) * capacity);
		if (_arr == nullptr)
		{
			perror("malloc fail");
			return;
		}
		_capacity = capacity;
		_top = 0;
	}
	Stack(const Stack& st)
	{
		_arr = (int*)malloc(sizeof(int) * st._capacity);
		if (_arr == nullptr)
		{
			perror("malloc fail");
			return;
		}
		memcpy(_arr, st._arr, sizeof(int) * st._capacity);
		_capacity = st._capacity;
		_top = st._top;
	}
};
int main()
{
	Stack st1;
	Stack st2(st1);
	return 0;
}