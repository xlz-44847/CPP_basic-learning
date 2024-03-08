#include<iostream>
using namespace std;

class Date
{
private:
	int _year;
public:
	Date(int year)
	{
		_year = year;
	}
	//写法1
	//重载<<，cout实际上是ostream类的一个对象，所以使用ostream&的方式作为参数
	void operator<<(ostream& out)
	{
		out << _year << endl;
	}

	//友元声明，可以在类外访问类的私有成员
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
};

//写法2
//流插入对于内置类型在库中已经实现，自定义类型则需要我们自己重载
//重载<<，定义在类外，这样就可以自主规定参数顺序
//返回ostream&，可以支持连续调用
ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year;
	return out;
}

//流提取
istream& operator>>(istream& in, Date& d)
{
	in >> d._year;
	return in;
}

int main()
{
	//想要使用cout<<d1这样的方式进行快捷打印d1对象，因此需要对流插入运算符<<进行重载
	Date d1(2024);
	Date d2(2000);

	cin >> d2;

	//采用了写法1，发现cout<<d1没有办法正确调用
	//这是因为<<有两个操作数，当重载为成员函数后，默认左操作数传给this指针，右操作数传给显式写出的参数，也就是ostream&
	//这就导致了cout<<d1因为参数位置问题而调用失败了
	//cout << d1;
	//根据其参数位置，我们可以采取以下方法正确调用，但是发现其顺序不合逻辑，将cout控制台流插入到d1，用起来非常别扭
	d1.operator<<(cout);
	d1 << cout;

	//采用了写法2，可以按正常逻辑进行调用
	cout << d1 << '\n' << d2 << endl;

}



//class A
//{
//public:
//	A(int a)
//		:_a(a)
//	{}
//	friend void func(A& a);
//private:
//	int _a;
//};
//void func(A& a)
//{
//	cout << a._a << endl;
//}
//int main()
//{
//	A a(13);
//	func(a);
//}