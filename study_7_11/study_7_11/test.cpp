#include<iostream>
using namespace std;

namespace Test1 {
	//继承本质上就是类之间的复用
	//继承关系下，父类会成为子类的一部分；即子类是由自身的成员和父类继承下来的成员组成
	//继承定义方法：class 子类（派生类）：<继承方式> 父类（基类）
	class Person
	{
	public:
		void Print()
		{
			cout << _name << ',' << age << endl;
		}
	protected:
		string _name;
		int age;
	};

	class Student :public Person
	{
	private:
		double score;
	};

	//继承后的访问限定符由 父类访问权限+继承方式 两方面决定，共9类
	//private成员无论什么继承方式在子类中都不可见
	//其余的6类根据public>protected>private的关系，选择 父类访问权限、继承方式 二者中较小的一个
	//如protected的成员在public继承后，取较小就是protected，所以可以认为是子类的protected成员
	class A
	{
	public:
		int a_public;
	protected:
		int a_protected;
	private:
		int a_private;
	};
	class A_PUBLIC : public A
	{
		//实际上有的成员：
		//public: int a_public
		//protected: int a_protected
		//不可见：a_private
		void func()
		{
			a_public;
			a_protected;
			//a_private;	//error
		}
	};
	class A_PROTECTED : protected A
	{
		//实际上有的成员：
		//protected: int a_public
		//protected: int a_protected
		//不可见：a_private
	};
	class A_PRIVATE : private A
	{
		//实际上有的成员：
		//private: int a_public
		//private: int a_protected
		//不可见：a_private
	};
	//总结：
	//private只在自己类中可被访问，不可见指不可以被访问，不代表不存在
	//protected在自己类中和子类中可被访问
	//public在自己类、子类、类外均可被访问
	//可以发现public继承后除了private外，public仍是子类的public，protected仍是子类的protected。
	//所以一般都会使用public继承，而很少使用protected和private继承
	
	class B : A
	{};
	struct C : A
	{};
	void func()
	{
		B b;
		C c;
		//b.A::a_public;	//error：class默认继承方式是private
		c.A::a_public;	//struct默认继承方式是public
		//建议显式写出继承方式
	}
}

namespace Test2 {
	class Person
	{
	public:
		string _name = "Jone";
		int age = 13;
	};
	class Student :public Person
	{
	public:
		double score = 98.2;
	};

	void func()
	{
		Student st;
		//子类对象可以赋值给父类对象、指针、引用————派生类和基类的赋值兼容转换（JAVA中的向上转型）
		Person per = st;
		Person* pper = &st;
		Person& rper = st;
		//赋值兼容转换实际上就是切片或切割
		//对于父类对象而言，赋值兼容转换实际上将子类中父类部分切割出去，产生了一个新的父类对象
		//而对于父类指针、引用，他们并没有新创建空间，而是让父类的指针、引用指向了子类中继承父类的那一部分，相当于切割
		//因此修改子类对象会影响父类指针、引用指向的值，同样的通过他们也可以修改子类对象的值
		cout << st._name << ',' << per._name << ',' << pper->_name << ',' << rper._name << endl;
		st._name = "Alice";
		cout << st._name << ',' << per._name << ',' << pper->_name << ',' << rper._name << endl;
		st._name = "Tom";
		cout << st._name << ',' << per._name << ',' << pper->_name << ',' << rper._name << endl;
		
		//对于父类赋值给子类的情况我们暂且认为不允许，等以后详细讨论
	}
}

namespace Test3 {
	class A
	{
	public:
		void Print()
		{
			cout << "A::Print()" << endl;
		}
		int num = 10;
		double d = 80.8;
	};
	class B : public A
	{
	public:
		void Print()
		{
			cout << "B::Print()" << endl;
		}
		int num = 20;
	};
	void func()
	{
		//父类和子类具有独立的作用域
		//对于同名的函数或变量，会优先访问子类作用域中的函数和变量，这样就构成了 隐藏（重定义） 的关系
		//如果想要访问父类成员，则需要使用::作用域限定符来标识作用域

		B b;
		b.Print();
		cout << b.num << endl;
		cout << b.d << endl;
		b.A::Print();
		cout << b.A::num << endl;
		cout << b.A::d << endl;
	}

	//对于函数而言，只需要子类父类函数名相同即可认为是隐藏
	//这里需要指出，重载会考虑参数是否相同，但是重载只会发生在同一作用域下的函数之间，父类和子类同名函数一定是隐藏
	class C
	{
	public:
		void func1()
		{}
	};
	class D : public C
	{
	public:
		void func1(int a)
		{}
	};
}


//在考虑继承后的默认函数时，要明白此时的类的成员有着三种角色：①内置类型；②自定义类型；③父类切片
//默认函数实际的操作也就根据这三类有不同的表现
namespace Test4 {
	class Person
	{
	public:
		Person(string name)
			:_name(name)
		{}

		Person(const Person& p)
			:_name(p._name)
		{}
	
		Person& operator=(Person& p)
		{
			if (this != &p)
			{
				_name = p._name;
				return *this;
			}
		}
		
		~Person()
		{}

		string _name;
	};
	class Student : public Person
	{
	public:
		//对于构造函数，无论父类还是子类在不写时，编译器都会自动生成一个默认构造
		//默认构造对内置类型不做处理、对自定义类型会调用它的默认构造函数、对子类中父类的那一部分会调用父类的默认构造函数
		//子类如果不显式调用父类的构造函数，则编译器会使用父类的默认构造
		//所以父类如果没有默认构造，就代表着子类必须自己写构造函数，并且要求子类必须显式调用父类的构造函数
		Student(string name, int age)
			:_age(age)
			, Person(name)
		{}

		//对于拷贝构造函数:
		//编译器生成的拷贝构造函数，对内置类型按字节完成拷贝、对自定义类型调用它的拷贝构造、对子类中父类的那一部分会调用父类的拷贝构造
		//拷贝构造终究属于构造函数，当子类拷贝构造中不显式调用父类的拷贝构造时，编译器会调用父类的默认构造
		//所以为了可以正常拷贝，我们需要在子类的拷贝构造中显式调用父类的拷贝构造
		//另外，由于拷贝构造也属于构造函数，所以我们在调用父类的构造函数时也可以调用非拷贝构造的函数
		Student(const Student& s)
			:_age(s._age)
			,Person(s)	//兼容复制转换，父类引用=子类对象，实际传的是子类对象中父类那一部分的引用
		{}
		//在构造函数中，优先调用父类的构造函数，在父类部分初始化结束后再初始化子类成员

		//对于赋值运算符重载：
		//编译器生成的赋值运算符重载函数，对内置类型按字节完成拷贝、对自定义类型调用它的赋值运算符重载、对子类中父类的那一部分会调用父类的赋值运算符重载
		//所以如果子类自己实现赋值运算符重载函数，需要显式调用父类的赋值运算符重载
		Student& operator=(Student& s)
		{
			if (this != &s)
			{
				_age = s._age;
				Person::operator=(s);	//同样采取兼容复制转换的方法进行传参
			}
			return *this;
		}

		//对于析构函数：
		//编译器生成的析构函数，对内置类型不处理，系统自动回收，对自定义类型调用它的析构函数，对子类中父类放入那一部分调用父类的析构函数
		//当自己实现析构函数时，因为构造顺序是先父类后子类，所以析构顺序是先子类后父类
		//为了避免出现先父后子的析构顺序，父类的析构函数不需要显式写出，会自动调用
		~Student()
		{}
		int _age;
	};

	void func()
	{
		Student s1("Alice", 12);
		Student s2(s1);
		Student s3("Mike",16);
		s1 = s3;
	}
}

namespace Test5 {
	class B;	//声明
	class A
	{
	public:
		friend 	void funca(A& a, B& b);
	private:
		int _a = 10;
	public:
		static double d;
	};
	double A::d = 1.97;
	class B : public A
	{
	private:
		int _b = 20;
	};
	void funca(A& a, B& b)
	{
		cout << a._a << endl;
		//cout << b._b << endl;	//友元关系不可以被继承，即函数是父类的友元，但并不是子类的友元，所以可以访问父类私有成员而不可以访问子类私有成员
	}
	void func()
	{
		B b;
		A a;
		funca(a, b);
		cout << a.d << ' ' << b.d << endl;	//父类定义的static成员，在整个继承体系中被共用，即无论如何继承，只有一个static成员
	}
}

namespace Test6 {
	//class A
	//{};
	//class B 
	//{};
	////单继承
	//class C : public A
	//{};
	////多继承
	//class D : public A, public B
	//{};
	//对于多继承可能会出现菱形继承的问题：即继承的父类有着共同的“祖先”，同宗同源
	//在菱形继承下，子类会存在两份共同父类的成员，即为二义性或称为数据冗余问题
	//解决这个问题需要追溯到二义性源头，如A类因为继承了B、C类而具有二义性，B、C又是最初分别通过D、E继承自F的，那么D和E就需要虚拟继承，即在继承方法前加入virtual
	class F
	{};
	class D : virtual public F
	{};
	class E : virtual public F
	{};
	class B : public D
	{};
	class C : public E
	{};
	class A : public B, public C
	{};
	//使用继承时应该尽量避免菱形继承
	
	//相较于继承，组合是一个类似的概念
	//继承：把一个类的细节（成员）完全转移到子类中，实际上内部需要同时考虑父类子类的所有成员，因为继承就是类的合二为一
	//组合：一个类的对象作为另一个类的成员，这样子对象就可以作为一个整体出现并使用，耦合度低
}

int main()
{
	Test3::func();
}