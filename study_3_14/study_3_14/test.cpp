#include<iostream>
#include<string>
using namespace std;

void Test1()
{
	//迭代器：正向、反向、const、非const
	string s1("hello world");
	//正向非const迭代器
	string::iterator it = s1.begin();
	while (it != s1.end())
	{
		cout << *it << ' ';
		it++;
	}
	cout << endl;
	//反向非const迭代器
	string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend())
	{
		cout << *rit << ' ';
		rit++;	//注意是++
	}
	cout << endl;
	
	const string s2("hello world");

	//正向const迭代器
	string::const_iterator c_it = s2.begin();
	while (c_it != s2.end())
	{
		cout << *c_it << ' ';
		c_it++;
	}
	cout << endl;
	//反向const迭代器
	string::const_reverse_iterator c_rit = s2.rbegin();
	while (c_rit != s2.rend())
	{
		cout << *c_rit << ' ';
		c_rit++;
	}
	cout << endl;
}
int main()
{
	Test1();
	return 0;
}