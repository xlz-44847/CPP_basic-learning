#include<iostream>
using namespace std;

//class Date
//{
//private:
//	int _year;
//public:
//	Date(int year)
//	{
//		_year = year;
//	}
//
////如果成员函数涉及到成员变量的写操作，则不可以加const修饰
////如果成员函数只涉及到成员变量的读访问，则建议加const修饰
//	void Print1()
//	{
//		cout << _year << endl;
//		this->Print2();	//非const修饰的成员函数调用const修饰成员函数，this指针由非const变为const，权限缩小
//	}
//	void Print2() const	//const修饰this指针
//	{
//		cout << _year << endl;
//		//this->Print1();	//error:const修饰的成员函数this指针是const，调用非const修饰成员函数会使this指针权限放大
//	}
//};
//
//int main()
//{
//	const Date d1(2022);
//	Date d2(2023);
//	//d1.Print1();	//error:(&d1)const Date* -> (this)Date*，权限的放大 
//	d1.Print2();	// (&d1)const Date* -> (this)const Date*，权限的平移 
//	d2.Print1();	// (&d2)Date* -> (this)Date*，权限的平移 
//	d2.Print2();	// (&d2)Date* -> (this)Date*，权限的缩小 
//}

//void Print2() const	
//{
//	cout << _year << endl;
//}
////void Print2(const Date* this)
////{
////	cout << _year << endl;
////}

//class Date
//{
//public:
//	//取地址及const取地址操作符重载
//	//一般不用自己写，采取编译器默认生成的，编译器生成的默认成员函数也是返回对象变量的地址
//	//特殊情况下才需要自己生成
//	Date* operator&()
//	{
//		return this;
//	}
//	const Date* operator&()const
//	{
//		return this;
//	}
//};
//int main()
//{
//	Date d1;
//	Date d2;
//	cout << &d1 << endl;
//	cout << &d2 << endl;
//	return 0;
//}



//class Date	
//{
//private:
//	int _year;
//	int _month;
//	int _day;
//public:
//	//初始化列表
//	Date(int year,int month,int day)
//		:_year(year)
//		,_month(month)
//		,_day(day)
//	{}
//	void Print()
//	{
//		cout << _year << '-' << _month << '-' << _day << endl;
//	}
//};
//int main()
//{
//	Date d1(2003,12,4);
//	d1.Print();
//}



//class Date	
//{
//private:
//	//此部分属于成员变量的声明，还没有定义
//	//此处所写的缺省值是提供给初始化列表的，是成员变量定义的初始化值
//	int _year = 1999;
//	int _month = 10;
//	int _day;
//
//	const int _n;
//
//public:
//	//在构造函数中，初始化列表部分才是每个成员变量定义初始化的位置
//
//	Date(int year,int month,int day)	//构造函数参数缺省值和声明给定初始化缺省值不冲突，前者在调用构造函数传参缺省时才会启用，后者在初始化列表缺省时启用
//
//		//此处虽然看似只定义了_n和_month并初始化，实际上所以成员变量都在此定义了
//		:_n(1)
//		,_month(1)	//没有给出_year成员的初始化值，采取缺省值，初始化为1999
//					//给出了_month成员的初始化值，直接初始化为1
//					//没有给出_day成员的初始化值，且_day成员没有缺省值，则初始化为随机值
//					//给出了_n成员的初始化值，直接初始化为1
//
//	//在构造函数的函数体内就不再是定义初始化了，而是赋值修改
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//		//_n = n;	//error:定义不发生在构造函数函数体，所以此处认为是赋值，给const赋值所以报错
//	}
//	void Print()
//	{
//		cout << _year << '-' << _month << '-' << _day << endl;
//	}
//};
//int main()
//{
//	//在对象实例化的时候定义了对象整体，而对象的成员定义则要通过调用构造函数来定义
//	Date d1(2003,12,4);
//	d1.Print();
//}

//能用初始化列表，就用初始化列表：
//①初始化列表是不可避免会执行的，所以建议尽量多使用初始化列表
//②在定义时必须初始化的变量必须使用初始化列表：如const修饰的成员变量；引用成员变量；自定义类型成员（且不存在默认构造函数时）

//class A
//{
//public:
//	A(int a)
//	{}
//};
//class C
//{
//public:
//	C(int a = 1)
//	{}
//};
//class B
//{
//private:
//	int _b;
//	const int _n;
//	int& _ref;
//	A _aa;
//	C _cc;
//public:
//	B(int b, int n, int& ref)
//		:_b(b)
//		,_n(n)
//		,_ref(ref)
//		,_aa(3)	//A类因为实现了需要传参的构造函数，所以对A类对象初始化需要手动传参，所以需要在初始化列表显式定义
//				//C类因为存在默认构造函数（不需要传参的构造函数），所以无需手动操作，可以不在初始化列表显式定义
//		//类对象是一定会在初始化列表定义的，初始化时调用其自身的构造函数
//		//而是否存在默认构造函数，只决定是否允许不在初始化列表显式写出定义
//	{}
//};
//int main()
//{
//	int num;
//	B b1(1, 2, num);
//}




//class A
//{
//private:
//	int* p = nullptr;
//public:
//	A()
//		:p((int*)malloc(sizeof(int) * 10))
//		//x(y) 相当于是 x=y，同理此处是p=(int*)malloc(sizeof(int) * 10)，括号内应该是一个值，缺省值同理
//	{
//		if (p == NULL)
//		{
//			perror("malloc fail");
//		}
//	}
//};


//class A
//{
//private:
//	int _a;
//public:
//	A(int a)
//		:_a(a)
//	{}
//};
//class B
//{
//private:
//	A _aa = 3;//由于单参数构造函数支持隐式类型转换，便可以顺利给出类对象缺省值
//};
//int main()
//{
//	A a1(1);
//	//单参数（或只有第一个参数无缺省值）构造函数支持隐式类型转换
//	A a2 = 2;	//构造函数参数需要int，所以实际是2先构造了一个A类的临时对象，再将这个临时对象通过调用拷贝构造给a2
//				//实际执行时，同一个表达式连续步骤的构造编译器会进行优化，此处将最后的拷贝构造优化掉了
//	const A& ra1 = 3;	//3隐式转换为A类型的临时对象，具有常性从而可以被常引用引用
//	//A& ra2 = 4;	//error:发生隐式转换后的临时对象具有常性，权限缩小
//}



//class A
//{
//public:
//	explicit A(int a) //explicit关键字修饰的构造函数禁止类型转换
//	{}
//};
//int main()
//{
//	//A a1 = 1;	//由于explicit关键字修饰了构造函数，所以这种需要隐式类型转换的写法就不正确了
//}


//



//class A
//{
//private:
//	int _a2;
//	int _a1;
//public:
//	A(int a)
//		:_a1(a)
//		, _a2(_a1)
//	{}
//	void Print() {
//		cout << _a1 << " " << _a2 << endl;
//	}
//};
//int main() {
//	A aa(1);
//	aa.Print(); //输出：1 随机值
//				//规定初始化顺序按照声明顺序初始化，并不是按照初始化列表顺序
//}



//class A
//{
//private:
//	//声明
//	static int n; //静态成员不属于任何一个对象，而是属于整个类，为所以类对象共享
//public:
//	static void func()	//静态成员函数没有this指针，所以只能访问静态成员（变量或函数）
//	{
//		cout << n << endl;
//	}
//};
////定义
//int A::n = 4;	//静态成员变量在类中声明，在类外定义，定义时不加static
//int main()
//{
//	A a;
//	//cout << a.n;	//静态成员亦受访问限定符限制
//	a.func();
//	A::func();
//}