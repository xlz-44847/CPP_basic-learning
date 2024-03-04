#pragma once
#include<iostream>
using namespace std;

class Date
{
private:
	int _year;
	int _month;
	int _day;
public:
	Date(int year = 2000, int month = 1, int day = 1);
	Date(const Date& d);
	~Date();

	bool operator==(const Date& d);
	bool operator!=(const Date& d);
	bool operator<(const Date& d);
	bool operator<=(const Date& d);
	bool operator>(const Date& d);
	bool operator>=(const Date& d);

	Date& operator=(const Date& d);

	inline int GetMonthDay(int year, int month)	//频繁调用，设定为内联函数
	{
		static int months[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };	//频繁访问，months无需销毁，使用static
		if (month == 2 && ((year % 4 == 0) && year % 100 != 0 || year % 400 == 0))	//判断闰年
			return 29;
		else
			return months[month];
	}

	void Print()
	{
		cout << _year << ' ' << _month << ' ' << _day << endl;
	}

	//日期+天数
	Date operator+(int day);
	//日期-天数
	Date operator-(int day);
	//日期-日期
	int operator-(const Date& d);
	//日期+=天数
	Date& operator+=(int day);
	//日期-=天数
	Date& operator-=(int day);
	//前置++
	Date& operator++();
	//后置++
	Date operator++(int);
	//前置--
	Date& operator--();
	//后置--
	Date operator--(int);
};

