#include<iostream>
#include<string>
using namespace std;

void Test1()
{
	//length和size没有区别，都是返回字符串长度
	string s1("Say hello to the world!");
	cout << s1.size() << endl;
	cout << s1.length() << endl;
	//最大字符串长度（很少使用）
	cout << s1.max_size() << endl;
	//返回容量
	cout << s1.capacity() << endl;
	//清空数据，不对容量做修改
	s1.clear();
	cout << s1 << endl;
	cout << s1.capacity() << endl;
	//缩容
	s1.shrink_to_fit();	//默认缩到15
	cout << s1.capacity() << endl;
	//扩容（自动扩容）
	s1.reserve(40);	//扩容到参数值大小，当reverse参数大于capacity才会执行
	cout << s1.capacity() << endl;


	//void resize(int n,char c = '\0')，重设字符串size大小
	//n < size				删除
	//size < n < capacity	插入
	//capacity < n			扩容并插入
	string s2("hello world");
	s2.resize(9);
	cout << s2 << endl;
	cout << s2.capacity() << endl;
	s2.resize(15,'&');
	cout << s2 << endl;
	cout << s2.capacity() << endl;
	s2.resize(20,'#');
	cout << s2 << endl;
	cout << s2.capacity() << endl;

}

void Test2()
{
	//[]、at()功能一样，返回对应位置字符
	string s1("hello world");
	cout << s1[3] << endl;
	cout << s1.at(3) << endl;
	//front()、back()分别返回头尾字符
	cout << s1.front() << endl;
	cout << s1.back() << endl;

	//cout << s1[15] << endl;
	//cout << s1.at(15) << endl;
}
int main()
{
	//Test1();
	Test2();
	return 0;
}