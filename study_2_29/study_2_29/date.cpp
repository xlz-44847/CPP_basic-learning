#include"date.h"
Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}
Date::~Date() {};

bool Date::operator==(const Date& d)
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}
bool Date::operator!=(const Date& d)
{
	return !(*this == d);
}
bool Date::operator<(const Date& d)
{
	if (_year < d._year)
		return true;
	else if (_year == d._year)
	{
		if (_month < d._month)
			return true;
		else if (_month == d._month)
		{
			if (_day < d._day)
				return true;
		}
	}
	return false;
}
bool Date::operator<=(const Date& d)
{
	return *this < d || *this == d;
}
bool Date::operator>(const Date& d)
{
	return !(*this <= d);
}
bool Date::operator>=(const Date& d)
{
	return !(*this < d);
}

Date& Date::operator=(const Date& d)
{
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	return *this;
}	
//日期+天数
Date Date::operator+(int day)
{
	Date tmp(*this);	//+操作符不改变原值，需要使用临时变量来做修改
	//Date tmp = *this;	//两种写法都是拷贝构造，赋值运算符只在已经创建的对象赋值时使用
	tmp += day;
	return tmp;	//tmp是局部变量，不可以传引用，只能传值
}
//日期+=天数
Date& Date::operator+=(int day)
{
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		++_month;
		if (_month == 13)
		{
			++_year;
			_month = 1;
		}
	}
	return *this;
}
//日期-天数
Date Date::operator-(int day)
{
	Date tmp(*this);
	tmp -= day;
	return tmp;
}
//日期-=天数
Date& Date::operator-=(int day)
{
	_day -= day;
	while (_day <= 0)
	{
		--_month;
		if (_month == 0)
		{
			--_year;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}
//日期-日期
int Date::operator-(const Date& d)
{
	//假定*this比d大，如果假设错误就交换
	int flag = 1;
	Date max = *this;
	Date min = d;
	if (*this < d)
	{
		flag = -1;
		max = d;
		min = *this;
	}

	int sum = 0;
	while (min != max)
	{
		++min;
		++sum;
	}
	return sum * flag;
}


//前置++
Date& Date::operator++()
{
	return *this += 1;
}
//后置++
Date Date::operator++(int)
{
	return (*this + 1);
}
//前置--
Date& Date::operator--()
{
	return *this -= 1;
}
//后置--
Date Date::operator--(int)
{
	return (*this - 1);
}


////第一组：实现+=，+的实现调用+=
////开销：+=返回引用，没有额外开销
////		+中需要创建临时变量，需要一次拷贝；值返回，又存在一次拷贝；调用+=，没有额外开销
//Date Date::operator+(int day)
//{
//	Date tmp(*this);	//+操作符不改变原值，需要使用临时变量来做修改
//	//Date tmp = *this;	//两种写法都是拷贝构造，赋值运算符只在已经创建的对象赋值时使用
//	tmp += day;
//	return tmp;	//tmp是局部变量，不可以传引用，只能传值
//}
//Date& Date::operator+=(int day)
//{
//	_day += day;
//	while (_day > GetMonthDay(_year, _month))
//	{
//		_day -= GetMonthDay(_year, _month);
//		++_month;
//		if (_month == 13)
//		{
//			++_year;
//			_month = 1;
//		}
//	}
//	return *this;
//}
//
////第二组：实现+，+=的实现调用+
////开销：+中需要创建临时变量，有一次拷贝；且是值返回，又存在一次拷贝
////		+=返回引用，没有额外开销。但是调用一次+，需要创建临时变量与值返回，存在两次拷贝。
//Date Date::operator+(int day)
//{
//	Date tmp(*this);
//	while (tmp._day > GetMonthDay(_year, _month))
//	{
//		tmp._day -= GetMonthDay(_year, _month);
//		++tmp._month;
//		if (tmp._month = 13)
//		{
//			++tmp._year;
//			tmp._month = 1;
//		}
//	}
//	return tmp;
//}
//Date& Date::operator+=(int day)
//{
//	*this = *this + day;
//	return *this;
//}