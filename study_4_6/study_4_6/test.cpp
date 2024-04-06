#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void test1()
{
	//构造函数
	//1.默认构造
	vector<int> v1;
	//2.n个val构造
	vector<int> v2(9, 3);
	//3.拷贝构造
	vector<int> v3(v2);
	//尾插数据
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	//for循环遍历
	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << ' ';
	}
	cout << endl;
	//迭代器遍历
	vector<int>::iterator it = v2.begin();
	while (it != v2.end())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;
	//范围for遍历
	for (auto e : v3)
	{
		cout << e << ' ';
	}
	cout << endl;
}

void test2()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	vector<int>::iterator it1 = v1.begin();
	while (it1 != v1.end())
	{
		cout << *it1 << ' ';
		++it1;
	}
	cout << endl;
	vector<int> v2(v1);

	//insert,pos位置的指出是依靠迭代器区间的，插入的值也可以使用迭代器区间
	v1.insert(v1.begin(), 0);
	vector<int>::iterator it2 = v1.begin();
	while (it2 != v1.end())
	{
		cout << *it2 << ' ';
		++it2;
	}
	cout << endl;
	v1.insert(v1.begin() + 3, v2.begin() + 1, v2.end() - 1);
	vector<int>::iterator it3 = v1.begin();
	while (it3 != v1.end())
	{
		cout << *it3 << ' ';
		++it3;
	}
	cout << endl;
}

void test3()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	//find使用算法库中的函数，也是使用迭代器划定区域
	auto pos = find(v1.begin(), v1.end(), 3);
	if (pos != v1.end())
	{
		v1.insert(pos, 0);
	}
	vector<int>::iterator it = v1.begin();
	while (it != v1.end())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;
}

int main()
{
	//test1();
	//test2();
	test3();
}