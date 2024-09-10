#include "SearchBinaryTree.h"
void Test1()
{
	int arr[] = { 17,5,92,23,56,84,34,12,55,60,18,22 };
	key::BSTree<int> bst;
	for (auto e : arr)
	{
		bst.Insert(e);
	}
	bst.Inorder();
	bst.Erase(17);
	bst.Erase(18);
	bst.Erase(84);
	bst.Inorder();
	cout << "Find:";
	int num;
	cin >> num;
	if (bst.Find(num))
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
}

void Test2()
{
	char arr1[] = { 'c','b','d','r','t','u','l','s','g' };
	string arr2[] = { "cat","bag","dog","run","tall","unit","long","stand","gone" };
	keyvalue::BSTree<char, string> bst;
	for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++)
	{
		bst.Insert(arr1[i], arr2[i]);
	}
	bst.Inorder();
	bst.Erase('v');
	bst.Erase('b');
	bst.Erase('t');
	bst.Inorder();
	cout << "Find:";
	char num;
	cin >> num;
	if (bst.Find(num))
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
}

void Test3()
{
	int arr[] = { 1,5,6,8,16,22,34,43,55,60 };
	key::BSTree<int> bst;
	for (auto e : arr)
	{
		bst.Insert(e);
	}
	bst.Inorder();
	bst.Erase(1);
	bst.Inorder();
}

void Test4()
{
	int arr[] = { 1,5,6,8,16,22,34,43,55,60 };
	keyvalue::BSTree<int,int> bst;
	for (auto e : arr)
	{
		bst.Insert(e,e);
	}
	bst.Inorder();
	bst.Erase(1);
	bst.Inorder();
}

int main()
{
	//Test1();
	//Test2();
	//Test3();
	Test4();
}