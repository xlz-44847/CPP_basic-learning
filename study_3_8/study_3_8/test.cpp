#include<iostream>
using namespace std;

class A
{
public:
	A(int a, int b)
		:_a(a)
		,_b(b)
	{
		cout << "A(int, int)" << endl;
	}
	~A()
	{
		cout << "~A(int, int)" << endl;
	}
private:
	int _a;
	int _b;
};
int main()
{
	//对于内置类型：
	int* p1 = new int;	//动态申请int类型空间
	int* p2 = new int(2);	//使用圆括号动态申请的空间进行初始化
	int* p3 = new int[4];	//使用方括号标识申请的数量
	int* p4 = new int[6] {1, 2, 3};	//使用大括号进行初始化，不完全初始化下（new时使用了大括号），未初始化的空间默认为0

	delete p1;	//释放空间使用delete
	delete p2;
	delete[] p3;	//释放new[]的空间，使用delete[]
	delete[] p4;

	//对于自定义类型
	A* pa1 = new A(1, 2);	//new自定义类型时会自动调用构造函数进行初始化
	//A* pa1 = new A;	//error,因为new自定义类型时会调用构造函数，A没有默认构造函数，所以会报错
	A* pa2 = new A[4]{ {1,2},{2,3},{3,4},{4,5} };	//new多个自定义类型变量并初始化

	delete pa1;	//delete自定义类型时会自动调用析构函数进行销毁
	delete[] pa2;	//delete[]释放new[]的空间

	//new的使用不需要进行检查，当出错时malloc会持续进行开辟空指针，new则会抛异常
	return 0;
}