#include<iostream>
using namespace std;

//class Date
//{
//public:
//	int _year;
//	int _month;
//	int _day;
//	Date(int year = 2000, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	bool operator ==(const Date& d2)
//	{
//		_day = 1;
//		return _year == d2._year
//			&& _month == d2._month
//			&& _day == d2._day;
//	}
//};
//bool operator ==(const Date& d1, const Date& d2)
//{
//	d1._day = 1;
//	return d1._year == d2._year
//		&& d1._month == d2._month
//		&& d1._day == d2._day;
//}
//
//
//int main()
//{
//	Date d1(2021, 5, 5);
//	Date d2(2021, 8, 19);
//	cout << (d1 == d2) << endl;	//0
//	cout << (d1 == d1) << endl; //1
//	return 0;
//}
//class Date
//{
//public:
//	int _year;
//	int _month;
//	int _day;
//public:
//	Date(int year = 2000, int month = 1, int day = 1)
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
//	//Date& operator=(const Date& d)
//	//{
//	//	if (this != &d)
//	//	{
//	//		_year = d._year;
//	//		_month = d._month;
//	//		_day = d._day;
//	//	}
//	//	return *this;
//	//}
//};
//
//Date& operator=(Date& d1,const Date& d2)
//{
//	if (&d1 != &d2)
//	{
//		d1._year = d2._year;
//		d1._month = d2._month;
//		d1._day = d2._day;
//	}
//	return d1;
//}
//
//int main()
//{
//	Date d1(2021, 2, 23);
//	Date d2;
//	d2 = d1;
//	return 0;
//}
//class Date
//{
//private:
//	int _year;
//	int _month;
//	int _day;
//public:
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
//int main()
//{
//	//Date d1(2022, 6, 5);
//	Date d1;
//	Date d2(d1);
//	d1.Print();
//	d2.Print();
//}

class Time
{
private:
	int _hour;
public:
	Time() = default;	//强制编译器生成默认构造
	Time(const Time& t)
	{
		_hour = t._hour;
	}
};
class Date
{
private:
	int _year;
public:
	Date(int year)
	{
		_year = year;
	}
};
int main()
{
	Date d1(2024);
	Date d2(d1);	//只有构造函数，会生成拷贝构造
	Time t1;	//error 不存在默认构造  只有拷贝构造函数，不会生成构造函数
	Time t2(t1);
}