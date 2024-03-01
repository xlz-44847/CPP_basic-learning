#include<iostream>
using namespace std;
//class Date 
//{
//private:
//	int _year;
//	int _month;
//	int _day;
//public:
//	void Init(int year = 2000, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	void Print()
//	{
//		cout << _year << '-' << _month << '-' << _day;
//	}
//};
//int main()
//{
//	Date d1;
//	d1.Init(2024, 2, 26);
//	d1.Print();
//}
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
//	//void Init(int year = 2000, int month = 1, int day = 1)
//	//{
//	//	_year = year;
//	//	_month = month;
//	//	_day = day;
//	//}
//	void Print()
//	{
//		cout << _year << '-' << _month << '-' << _day << endl;
//	}
//};
//int main()
//{
//	Date d1;
//	Date d2(2024, 2, 26);
//	//d1.Init(2024, 2, 26);
//	d1.Print();
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
//	void Print()
//	{
//		cout << _year << '-' << _month << '-' << _day << endl;
//	}
//};
//int main()
//{
//	Date d1(2024, 2, 26);
//	d1.Print();	//2024-2-26
//}
//class Time
//{
//private:
//	int _hour;
//	int _minute;
//	int _second;
//public:
//	Time()
//	{
//		cout << "Time()" << endl;
//	}
//};
//class Date
//{
//private:
//	int _year;
//	int _month;
//	int _day;
//	Time _t;
//public:
//	Date(int year, int month, int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//		cout << "Date()" << endl;
//	}
//	void Print()
//	{
//		cout << _year << '-' << _month << '-' << _day << endl;
//	}
//};
//int main()
//{
//	Date d1(2024,2,26);
//	d1.Print();
//	
//	//output
//	//Time()
//	//Date()
//	//2024 - 2 - 26
//}
class Date
{
private:
	//在类中给默认值
	int _year = 2000;
	int _month = 1;
	int _day = 1;
public:
	void Print()
	{
		cout << _year << '-' << _month << '-' << _day << endl;
	}
};
int main()
{
	Date d1;
	d1.Print();	//2000-1-1
}