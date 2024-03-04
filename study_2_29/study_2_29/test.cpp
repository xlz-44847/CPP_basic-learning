//#include<iostream>
//using namespace std;

//class Date
//{
//private:
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
//	Date& operator=(const Date& d)
//	{
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//	//前置++，没有参数。自增后再使用，所以返回加1后的对象。
//	Date& operator++()
//	{
//		_day += 1;
//		return *this;
//	}
//	//后置++,和前置区分加入参数int。
//	//使用后再自增，所以需要返回没有加1时的对象，因此需要保存之前的对象，因此创建局部临时对象，因此需要传值返回
//	Date operator++(int)
//	{
//		Date temp(*this);
//		_day += 1;
//		return temp;
//	}
//	void Print()
//	{
//		cout << _year << ' ' << _month << ' ' << _day << endl;
//	}
//};
//int main()
//{
//	Date d1(2022, 6, 15);
//	d1.Print();		//2022 6 15
//	(++d1).Print();	//2022 6 16
//	(d1++).Print();	//2022 6 16
//	d1.Print();		//2022 6 17
//	return 0;
//}
#include"date.h"
int main()
{
	Date d1(2008, 1, 6);
	Date d2(2018, 5, 2);
	Date d3(2018, 3, 18);
	cout << (d1 < d2) << ' ' << (d1 < d3) << ' ' << (d2 < d3) << endl;
	cout << (d1 - d2) << ' ' << (d2 - d3) << endl;
	(d1 + 98).Print();
	(d3 - 72).Print();
	(d2 += 55).Print();
	(d3 -= 55).Print();
	d3.Print();
	
}