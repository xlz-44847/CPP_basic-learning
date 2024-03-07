#include<iostream>
using namespace std;

//void func()
//{}
//class Date
//{
//	//声明友元类
//	friend class Time;	//声明Time类为Date类的友元类，因此可以在Time类中可以访问Date类的私有成员
//	//声明友元函数，作为与友元类对比
//	friend void func();	//声明func函数为Date类的友元类，因此可以在func函数中访问Date类的私有成员
//private:
//	int _month;
//	int _day;
//};
//class Time
//{
//public:
//	//friend class Date;//声明Date类为Time类的友元类，支持在Date类中访问Time类的私有成员，但是在Time类中无法访问Date类，这说明友元关系是单向的
//	void Print()
//	{
//		cout << d._month << '/' << d._day << '/' << _hour << ':' << _minute << endl;
//		//由于声明了Time类是Date类的友元类，所以可以正常访问Date中的私有成员_month和_day
//	}
//private:
//	int _hour;
//	int _minute;
//	Date d;
//};
//int main()
//{
//	return 0;
//}




//内部类
//class A
//{
//public:
//	class B	//B的访问限定符是public
//	{
//	public:
//		void funcb(A& a)
//		{
//			a._a = 1;	//内部类天生就是外部类的友元类，所以可以访问外部类的私有成员
//		}
//	private:
//		int _b;
//	};
//private:
//	class C	//C的访问限定符是private
//	{};
//private:
//	int _a;
//};
//
//int main()
//{
//	A a;
//	//内部类受类域和访问限定符的限制
//	A::B b;	
//	//A::C c;	//error,C是private
//	cout << sizeof(A) << endl;	//4，注意：内部类和类对象的成员变量是两回事
//	return 0;
//}



class A
{
public:
	A(int a)
		:_a(a)
	{
		cout << "A(int)" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
	void func()
	{}
private:
	int _a;
};
int main()
{
	//有名对象
	A a1(1);
	//匿名对象---声明周期只有一行
	A(2);
	//匿名对象一般使用场景是对对象并无创建需求，但是需要一个对象作为媒介来访问类中的函数，那么匿名对象就可以充当这个媒介，进行便捷访问
	return 0;
}