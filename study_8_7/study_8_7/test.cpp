#include "AVLTree.h"

void Test1()
{
	char arr1[] = { 'c','b','d','r','t','u','l','s','g' };
	string arr2[] = { "cat","bag","dog","run","tall","unit","long","stand","gone" };
	AVLTree::AVLTree<char, string> avl;
	for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++)
	{
		avl.Insert({ arr1[i], arr2[i] });
	}
	avl.Inorder();
}

void Test2()
{
	int arr1[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	int arr2[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	AVLTree::AVLTree<int, int> avl1;
	for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++)
	{
		avl1.Insert({ arr1[i], arr1[i] });
	}
	AVLTree::AVLTree<int, int> avl2;
	for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); i++)
	{
		avl2.Insert({ arr2[i], arr2[i] });
	}
 	cout << avl1._IsBalanceTree(avl1.getroot()) << endl;
	cout << avl2._IsBalanceTree(avl2.getroot()) << endl;

	cout << avl1.Find(12) << endl;
	cout << avl1.Find(16) << endl;
}

int main()
{
	Test2();
}