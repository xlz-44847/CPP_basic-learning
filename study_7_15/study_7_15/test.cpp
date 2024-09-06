#include<iostream>
using namespace std;

namespace Test1 {
	//多态的条件：
	//①使用基类的 指针或引用 调用虚函数
	
	//②被调用的函数必须是虚函数，且被派生类重写
	class A
	{
	public:
		virtual void func()
		{
			cout << "A::func()" << endl;
		}
	};
	//被virtual修饰的成员函数被称为虚函数
	//重写：子类中存在的一个与父类完全相同的虚函数，与父类中的该虚函数之间构成重写
	//	 重写的完全相同要求返回类型、函数名、参数列表完全相同

	class B : public A
	{
	public:
		virtual void func()
		{
			cout << "B::func()" << endl;
		}
	};
	class C : public A
	{
	public:
		virtual void func()
		{
			cout << "C::func()" << endl;
		}
	};


	void Func(A& a)
	{
		a.func();
	}
	void func()
	{
		A a;
		B b;
		C c;
		Func(a);
		Func(b);
		Func(c);
	}
	//重写的例外①：协变——基类与派生类的虚函数返回类型不同
	//	 这个规则的出现主要是为了迎合函数返回类型是自身相关类型的情况
	//   如：A的函数 virtual A1* fun();
	//      B的函数 virtual B1* fun();
	class A1
	{
		virtual A1* fun()
		{
			return new A1;
		}
	};
	class B1 : public A1
	{
		virtual B1* fun()
		{
			return new B1;
		}
	};
	//重写的例外②：析构函数的重写
	//析构函数看似函数名不同，实际上经过编译器处理，最后析构函数的函数名都会被处理成destructor
	class A2
	{
	public:
		virtual ~A2()
		{
			cout << "~A2()" << endl;
		}
	};
	class B2 : public A2
	{
	public:
		virtual ~B2()
		{
			cout << "~B2()" << endl;
		}
	};
	//继承体系下，析构函数被定义为虚函数是很有必要的
	//因为实际代码中存在赋值兼容转换的情况，设计为虚函数重写后可以根据对象类型完成多态，分类处理
	//如果不设计为虚函数，则不构成重写，那么在销毁对象时就不会多态调用析构函数，那么如果子类赋值兼容转换给了父类的指针，在析构时会调用父类析构，此时子类那一部分就造成内存泄漏了
	void func2()
	{
		A2* p1 = new A2;
		A2* p2 = new B2;
		delete p1;
		delete p2;
	}
	//重写的例外③：子类重写的虚函数不加virtual是可以的，但是不建议

	//override修饰的虚函数会检查是否重写了父类的某个虚函数，如果没有重写则报错
	//final修饰的虚函数不可以再被重写
	class A3
	{
	public:
		virtual void func1() final
		{}
		virtual void func2(int a=1)
		{}
	};
	class B3 : public A3
	{
	public:
		//virtual void func1()
		//{}
		virtual void func2(int b=2) override
		{}
		//重写只重写函数体，而不重写函数名、参数列表等，所以B3中的函数体和A3不同，但是B3的func2的参数列表仍为int a=1，缺省值为1而非2
	};

	//重载要求只发生在同一作用域下，要求函数名相同，参数列表不同。重载可以实现不同类型参数调用不同函数体的功能。
	//隐藏（重定义）的两个函数分别位于父类和子类，要求函数名相同。隐藏解决子类和父类的同名成员冲突问题，隐藏父类成员，使用子类成员。
	//重写（覆盖）是一种特殊的隐藏，函数都为虚函数，分别位于父类和子类，要求函数名、参数、返回类型相同。重写帮助实现多态，重写的函数根据调用的对象来决定使用父类或者是子类的函数。
	//重写是特殊的隐藏，基类和派生类同名函数，如果不是重写关系，就是隐藏关系
}

namespace Test2 {
	//在虚函数声明的后面标识“=0”，则表示该函数是一个纯虚函数
	//包含纯虚函数的类称为抽象类，抽象类不可以被实例化
	//所以一般概念层的类，这样的类不存在对象，就把它写成一个抽象类
	//抽象类的作用一般就是继承给其他类，然后由其他类实现其中的纯虚函数
	class A1
	{
		virtual void func() = 0;
	};
	class A2 : public A1
	{
		virtual void func2() = 0;
	};
}

namespace Test3 {
	class A
	{
	public:
		virtual void Func1() {}
		virtual void Func2() {}
		virtual void Func3() {}
	private:
		int a;
	};
	class B : public A
	{
	public:
		virtual void Func1() {}
		virtual void Func2() {}
	private:
		int b;
	};
	void func()
	{
		A a;
		B b;
		cout << sizeof(A) << endl;
		
		A a1 = b;
		A* pa = &b;
		A& ra = b;
		
		pa->Func1();
		pa->Func3();

		cout << typeid(a).name() << endl;
		cout << typeid(b).name() << endl;
		cout << typeid(a1).name() << endl;
		cout << typeid(pa).name() << endl;
		cout << typeid(ra).name() << endl;
		//多态的具体表现是：对象调用同一个函数，由于对象的不同从而调用不同的函数
		//多态只可以通过指针和引用实现，这是因为多态在调用函数时并不确定调用的是继承体系中哪一个对象的函数，从而需要在运行时确定调用的函数位置，因而其指令中函数地址是在运行时动态绑定的
		//指针和引用实际上是切片，也就是并未创建出新的对象，只是指针引用指向了基类部分，是披着基类类型壳子的子类，所以在调用重写的函数时，指针和引用很清楚自己真正是什么类型，从而正确完成多态
		//而对象，就是非常确定的存在，基类对象就是基类，不可能是子类或其他什么，这也印证子类赋值兼容转换给基类，基类会创建新空间。一个确定的对象去调用重写的函数，自然只会调用自己的，从而不会发生多态。所以对象调用函数是静态绑定，在编译时就已经确定
		//·可以通过调试观察各个对象中_vfptr的值区别
	}
	//当类中存在虚函数时，对象的大小将增加包含一个指针_vfptr
	//对象的空间中包含：成员变量+指针_vfptr
	//_vfptr又叫做虚函数表指针，指向一个函数指针数组，也就是虚函数表（虚表），这个数组中存放着各个虚函数的地址
	//为了实现多态，所以父类和子类对象的成员的虚函数不完全相同，所以子类对象和父类对象有着自己独自的虚表
	//如上述代码，A和B类对象的虚表中，Func1和Func2被重写了，所以他们对应的虚表中的地址不一样，在多态调用的时候根据对象的不同，会访问属于各自不同的虚表，从而找到代码段中的不同函数
	//而Func3没有被重写，所以在a和b对象的虚表中，Func3地址相同

}

void main()
{
	//Test1::func();
	//Test1::func2();
	Test3::func();
}