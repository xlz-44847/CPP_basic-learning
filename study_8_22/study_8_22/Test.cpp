#include"RBTree.h"

void Test1()
{
	RBTree::RBTree<int, int> rb1;
	RBTree::RBTree<int, int> rb2(rb1);

}
void Test2()
{
	char arr1[] = { 'c','b','d','r','t','u','l','s','g' };
	string arr2[] = { "cat","bag","dog","run","tall","unit","long","stand","gone" };
	RBTree::RBTree<char, string> rb;
	for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++)
	{
		rb.Insert({ arr1[i], arr2[i] });
	}
	rb.Inorder();
}

void Test3()
{
	int arr1[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr2[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	RBTree::RBTree<int, int> rb1;
	for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++)
	{
		rb1.Insert({ arr1[i], arr1[i] });
	}
	RBTree::RBTree<int, int> rb2;
	for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); i++)
	{
		rb2.Insert({ arr2[i], arr2[i] });
	}
	cout << rb1.IsValidRBTree() << endl;
	cout << rb2.IsValidRBTree() << endl;

}

int main()
{
	//Test1();
	Test2();
	Test3();
	return 0;
}