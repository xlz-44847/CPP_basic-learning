#include<iostream>
using namespace std;
//函数重载
//1.参数个数不同
//2.参数类型不同
//3.参数类型顺序不同
//void func(int a, char b)
//{
//	cout << a << b << endl;
//}
//void func(int a, int b)
//{
//	cout << a << b << endl;
//}
//void func(char b, int a)
//{
//	cout << b << a << endl;
//}
//void func(int a)
//{
//	cout << a << endl;
//}
//int func(int a)
//{
//	return a;
//}
//void func(int a, char b);
//void func(int a, int b);
//void func(char b, int a);
//void func(int a);
//int func(char a);
//int main()
//{
//	func(1, 2);
//	func(1, 'a');
//	func('a', 1);
//	func(1);
//	func('a');
//	return 0;
//}
//int main()
//{
//	int a = 1;
//	int& ra = a; //定义引用变量
//	cout << a << ' ' << ra << endl;
//	a++;
//	cout << a << ' ' << ra << endl;
//	ra++;
//	cout << a << ' ' << ra << endl;
//	return 0;
//}
// 
//int main()
//{
//	int a = 1;
//	int& ra = a;
//	int& rra = a;
//	int& r_rra = rra;
//	cout << a << ' ' << ra << ' ' << rra << ' ' << r_rra << endl;
//	a++;
//	cout << a << ' ' << ra << ' ' << rra << ' ' << r_rra << endl;
//	ra++;
//	cout << a << ' ' << ra << ' ' << rra << ' ' << r_rra << endl;
//	rra++;
//	cout << a << ' ' << ra << ' ' << rra << ' ' << r_rra << endl;
//	r_rra++;
//	cout << a << ' ' << ra << ' ' << rra << ' ' << r_rra << endl;
//	return 0;
//}
//void func(int a)
//{
//	cout << a << endl;
//}
//typedef void(**fpp)(int);
//typedef void(*fp)(int);
//typedef void(f)(int);
//int main()
//{
//	//对于定义函数指针引用：
//	//1.注意定义的引用的类型和引用实体的类型相同。
//	//	①函数名有两种解释方式，函数名具有右值属性。以func为例：void(*)(int)和void()(int)
//	//	②注意辨别不同级函数指针。
//	void(*pf)(int) = func;
//	void(**ppf)(int) = &pf;
//	//2.注意区别左值右值，左值只能使用非常量引用，右值只能使用常量引用
//	//		区分左右值的方式：判断能否位于赋值符号左边。如*p可以就是左值，&func不可以就是右值
//	//		注意：函数名是右值，所以在定义类似于void()(int)类型的引用（不是指针的函数类型）时,一定是常量引用
//	//3.注意定义函数指针的引用可以存在两种方式：①使用typedef；②不使用typedef。
//	
//	/*f func_;
//	f& rfunc_ = func;
//	rfunc_ = func;*/ //void()(int)类型的引用一定是常量引用
//	
//	//非常量引用的定义方式
//			//1.使用typedef
//	fp& r2 = pf;
//		//r2 = func;
//	fpp& r3 = ppf;
//		//r3 = &r2;
//			//2.不使用typedef
//	void(*&rr2)(int) = pf;
//		//rr2 = func;
//	void(**&rr3)(int) = ppf;
//		//rr3 = &rr2;
//	
//	//常量引用的定义方式
//
//		//f& r1 = func;
//		//void(&rr1)(int) = func; 
//		//以上两种方式虽然可行不报错，但是体现不出常引用，所以不建议使用
//		//r1 = func;
//		//rr1 = func;
//		
//			//1.使用typedef
//	const f& r1_c = func;
//		//r1_c = func;
//	const fp& r2_c = pf;
//		//r2_c = func;
//	const fpp& r3_c = ppf;
//		//r3_c = &r2;
//			//2.不使用typedef
//	void(const &rr1_c)(int) = func;
//		//rr1_c = func;
//	void(*const &rr2_c)(int) = pf;
//		//rr2_c = pf;
//	void(**const &rr3_c)(int) = ppf;
//		//rr3_c = ppf;
//
//	const fp& r_a = func;
//	const fp& r_b = &func;
//	void(* const& r_c)(int) = func;
//	void(* const& r_d)(int) = &func;
//	// 因为函数名有两种解释方式，所以上述的定义方式也是正确的
//	
//	void(*&r_e)(int) = *ppf;
//	//void(*&r_e)(int) = &func;
//	//void(*&r_e)(int) = func;
//	//因为*ppf是左值，所以没有问题；而&func和func是右值，所以会报错
//
//	return 0;
//}

//int main()
//{
//	//int a = 1;
//	//char& ra = a;
//	void (*p1)(int) = func;//函数指针  p1---void(*)(int)
//	//p1(1);
//	//fp p2 = func;
//	//p2(2);
//
//	cout << typeid(func).name() << endl; //func的类型是void()(int)
//	cout << typeid(&func).name() << endl; 
//
//	fp& r1 = p1; //r1---void(*&)(int)==void(*)(int)
//	void (*&rr1)(int) = p1; //rr1---将fp& r1 = p1展开写的形式
//	// 左值：可以写在赋值号左边，如*p
//	// 右值：不可以写在赋值号左边，如&func
//	//void (*&rr1_test)(int) = &func;//&func是右值，所以不可以对引用进行初始化赋值
//
//	cout << typeid(fp).name() << endl;
//	cout << typeid(r1).name() << endl;
//	cout << typeid(rr1).name() << endl;
//	r1(3);
//
//	f& r2 = func;//r2---void(&)(int)==void()(int)
//	void(&rr2)(int) = func; //rr2---将f& r2 = func展开写的形式
//	void(&rr2_test)(int) = *p1; //*p1是左值，所以可以对引用进行初始化赋值
//	cout << typeid(f).name() << endl;
//	cout << typeid(r2).name() << endl;
//	cout << typeid(rr2).name() << endl;
//	r2(4);
//
//	//定义常引用
//	void (* const&rrr1)(int) = &func;
//	//rrr1 = func;//error 常量引用不可修改
//	const fp& rrr1_ = &func; //rrr1类型为void(*&)(int),func作为函数名可以被解释为函数指针，类型变为void(*)(int)，因此语法正确
//	
//	const fp& rrrr1 = p1; //rrr1类型为void(*&)(int),p1类型为void(*)(int)
//	//rrrr1 = func;////error 常量引用不可修改
//	//const f&  rrr2 = &func;//rrr2类型为void(&)(int),func类型为void()(int)
//	//const f& rrrrr2 = &func;//rrr2类型为void(&)(int),func类型为void()(int)
//	//const f& rrrr2 = p1;//error  rrrr2类型为void(&)(int),p1类型为void(*)(int)且不可自动变化，因此语法正确
//	//const fpp& r3 = func;
//	//const fpp& rr3 = p1;
//	void(**pp1)(int) = &p1;
//	//void(**pp1)(int) = func;
//	const fpp& rr3 = pp1;
//
//	cout << typeid(rrr1).name() << endl;
//	cout << typeid(rrrr1).name() << endl;
//	//cout << typeid(rrr2).name() << endl;
//
//	const int aa = 1;
//	cout << typeid(aa).name() << endl;
//	return 0;
//}
//int main()
//{
//	////int& ra; //error 没有初始化
//	//int b;
//	//int& rb = b;
//	//int a = 1;
//	//int& ra = a;
//	//int& rra = a;
//	int a = 3;
//	int b = 8;
//	int& ra = a;
//	ra = b;//歧义：①将b的值赋值给ra；②将b作为引用变量ra的实体 
//	return 0;
//}
//int main()
//{
//	const int a = 10;
//	//int& ra = a;		//error
//	const int& ra = a;	//correct
//	
//	//int& rb = 10;		//error
//	const int& rb = 10;	//correct
//
//	double d = 3.14;
//	//int& rd = d;		//error
//	const int& rd = d;	//correct,rd==3  d首先隐式类型转换为int，产生一个临时变量，临时变量具有常性所以可以赋给常引用
//
//	d = 4.48;
//
//	cout << d << ' ' << rd << endl; //4.48 3
//
//	return 0;
//}
//void swap(int& a, int& b)
//{
//	int tmp = a;
//	a = b;
//	b = tmp;
//}
//int main()
//{
//	int x = 1;
//	int y = 2;
//	swap(x, y);
//	cout << x << ' ' << y << endl;
//	return 0;
//}
//struct Node
//{
//	struct Node* next;
//	int val;
//};
//void func(struct Node& node)
//{}
//int main()
//{
//	struct Node n1;
//	func(n1);
//}

//int& func1()
//{
//	int a = 3;
//	return a;
//}
//int& func2()
//{
//	int b = 7;
//	return b;
//}
//
//int main()
//{
//	int& ret = func1();
//	cout << ret << endl;
//	func2();
//	cout << ret << endl;
//	return 0;
//}

//int& Add(int a,int b)
//{
//	//static int x = a + b; //这样写因为static只定义一次，所以会导致再次调用函数时不会执行这一步。
//	static int x;
//	x = a + b;
//	return x;
//}
//int main()
//{
//	int& a = Add(2,4);
//	cout << a << endl;
//	a = Add(8, 9);
//	cout << a << endl;
//	return 0;
//}

//#include <time.h>
//struct A { int a[10000]; };
//void TestFunc1(A a) {}
//void TestFunc2(A& a) {}
//void TestRefAndValue()
//{
//	A a;
//	// 以值作为函数参数
//	size_t begin1 = clock();
//	for (size_t i = 0; i < 100000; ++i)
//		TestFunc1(a);
//	size_t end1 = clock();
//	// 以引用作为函数参数
//	size_t begin2 = clock();
//	for (size_t i = 0; i < 100000; ++i)
//		TestFunc2(a);
//	size_t end2 = clock();
//	// 分别计算两个函数运行结束后的时间
//	cout << "TestFunc1(A)-time:" << end1 - begin1 << endl;
//	cout << "TestFunc2(A&)-time:" << end2 - begin2 << endl;
//}
//#include <time.h>
//struct A { int a[10000]; };
//A a;
//// 值返回
//A TestFunc1() { return a; }
//// 引用返回
//A& TestFunc2() { return a; }
//void TestReturnByRefOrValue()
//{
//	// 以值作为函数的返回值类型
//	size_t begin1 = clock();
//	for (size_t i = 0; i < 100000; ++i)
//		TestFunc1();
//	size_t end1 = clock();
//	// 以引用作为函数的返回值类型
//	size_t begin2 = clock();
//	for (size_t i = 0; i < 100000; ++i)
//		TestFunc2();
//	size_t end2 = clock();
//	// 计算两个函数运算完成之后的时间
//	cout << "TestFunc1 time:" << end1 - begin1 << endl;
//	cout << "TestFunc2 time:" << end2 - begin2 << endl;
//}
//int main()
//{
//	//TestRefAndValue();
//	TestReturnByRefOrValue();
//}

//int cal1(int a)
//{
//	int b = a * 2;
//	return b;
//}
//int& cal2(int a)
//{
//	static int b;
//	b = a * 2;
//	return b;
//}
//int main()
//{
//	int num1 = cal1(1);		//case1：返回方式：返回值。
//							//在栈中开辟空间的b在函数结束后，将值交给临时变量（寄存器），再由临时变量交给num1，内存中产生了返回值的副本（临时变量）
//	//int& num2 = cal1(2);	//case2：报错，因为函数返回的值是临时变量，具有常性
//	int num3 = cal2(3);		//case3：返回方式：返回引用。
//							//在函数结束后，因为是返回引用，所以实际上是返回b变量的别名。而num3的值则是直接从b变量处拷贝而来，避免了副本的产生。
//							//因为b变量是一个静态变量，所以不会随着栈帧被释放，才能在栈帧释放后进行拷贝。
//	int& num4 = cal2(4);	//case4：返回方式：返回引用。
//							//在函数结束后，返回了b变量且不产生副本，而引用声明num4使用返回值初始化，所以num4就成为了b变量的引用、别名。
//							//因为b变量是一个静态变量，所以不会随着栈帧被释放，所以引用依旧有效。
//}