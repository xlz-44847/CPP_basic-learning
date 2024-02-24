//#include<stdio.h>
//#include<stdlib.h>
//命名空间
//int main()
//{
//	int rand = 2;//在C语言中会出现重命名的情况，因为rand是一个库函数名
//	return 0;
//}

////命名空间的定义
//namespace np1
//{
//	//命名空间内可以定义变量、函数、类型，也可以嵌套其他命名空间
//	int a = 9;
//	int Add(int a, int b)
//	{
//		return a + b;
//	}
//	struct Node
//	{
//		struct Node* next;
//		int val;
//	};
//	namespace np2
//	{
//		int a = 8;
//		char c;
//		int Sub(int a, int b)
//		{
//			return a - b;
//		}
//	}
//}
////相同名称的命名空间最后会被编译器合并成为一个
//namespace np1
//{
//	int b;
//}
//namespace np2 //该命名空间不会和np1中的np2合并
//{
//	int b = 6;
//	short a = 7;
//}

//命名空间的使用
////1.命名空间 配合 ::
//// :: -- 域作用限定符
//int main()
//{
//	printf("%d ", np1::a);
//	printf("%d ", np1::Add(2,6));
//	return 0;
//}
//
////2.通过using引入命名空间的某个成员
//using np1::np2::a;
//using np2::b;
//int main()
//{
//	printf("%d ", a);
//	printf("%d ", b);
//	return 0;
//}
//
////3.通过using namespace引入整个命名空间
//using namespace np1;
//int main()
//{
//	printf("%d ", Add(7, 9));
//	printf("%d ", a);
//	printf("%d ", np1::np2::a);//因为np1被展开了，所以np2的指向不明确，np1::np2表示np1中的np2
//	printf("%d ", ::np2::a);//::np2表示全局域下的np2
//	return 0;
//}


////域：全局域、局部域、命名空间域、类域
////对于一个变量名：如果没有指定域则先搜索局部，后搜索全局
////				  如果指定了域则直接去对应域中搜索
//int a = 4;
//int main()
//{
//	int a = 2;
//	printf("%d\n", a);
//	{
//		printf("%d\n", a);
//	}
//	printf("%d\n", ::a);
//	printf("%d\n", np1::a);
//	printf("%d\n", np2::a);
//	return 0;
//}

