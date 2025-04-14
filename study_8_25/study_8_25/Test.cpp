#include "Set.h"
#include "Map.h"

void Test1()
{
	int arr1[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr2[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	Set::set<int> s1;
	for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++)
	{
		s1.insert(arr1[i]);
	}
	Set::set<int> s2;
	for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); i++)
	{
		s2.insert(arr2[i]);
	}
	
	Set::set<int>::constiterator it = s1.cbegin();
	while (it != s1.cend())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	for (auto& e : s2)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << *s1.find(14) << endl;
}

void Test2()
{
	int arr1[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr2[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	Map::map<int, int> m1;
	for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++)
	{
		m1.insert(make_pair(arr1[i], arr2[i]));
	}
	
	Map::map<int, int>::constiterator it = m1.cbegin();
	while (it != m1.cend())
	{
		cout << it->first << " " << it->second << endl;
		++it;
	}
	for (auto& e : m1)
	{
		cout << e.first << " " << e.second << endl;
	}
	cout << endl;
	cout << m1.find(14)->first << " " << m1.find(14)->second << endl;
	cout << m1[14];
}

int main()
{
	Test1();
	Test2();
	return 0;
}