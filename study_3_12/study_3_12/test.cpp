#include<iostream>
#include<string>
using namespace std;


void Test1()
{
//default (1):			string();
//copy(2):				string(const string& str);
//substring(3):			string(const string& str, size_t pos, size_t len = npos);
//from c - string(4):	string(const char* s);
//from sequence(5):		string(const char* s, size_t n);
//fill(6):				string(size_t n, char c);
//(1)默认构造
//(2)拷贝构造
//(3)部分拷贝：str字符串的pos下标开始len个长度。如果超出str范围或未传参则会一直拷贝到结尾。npos值为-1，对于size_t则是最大值
//(4)使用C-string构造
//(5)拷贝s字符串的前n个字符
//(6)n个c字符构造


	string s1;
	string s2("hello world!");
	string s3(s2);
	string s4(s2,3,5);
	string s5(s2,3,10);
	string s6(s2,3);
	string s7("good luck", 3);
	string s8(7,'#');
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;
	cout << s6 << endl;
	cout << s7 << endl;
	cout << s8 << endl;
}

//析构函数无特别用法

void Test2()
{
//string(1):		string& operator= (const string & str);
//c - string(2):	string & operator= (const char* s);
//character(3):		string& operator= (char c);
//(1)用string对象赋值
//(2)用C-string赋值
//(3)用字符赋值

	string s1("hello");
	string s2;
	s2 = s1;
	cout << s2 << endl;	
	s2 = "world";
	cout << s2 << endl;	
	s2 = '&';
	cout << s2 << endl;

}

void Test3()
{
	string s1("hello world");
	for (int i = 0; i < s1.size(); i++)
		//size()函数返回字符串长度，不包含'\0'
	{
		cout << s1[i] << ' ';
		s1[i]++;
		cout << s1[i] << ' ';
		//[]重载可读可写
		//char& operator[] (size_t pos); 
		//const字符串使用const修饰的[]重载，返回const char&，不可以写操作
		//const char& operator[] (size_t pos) const;
	}
	cout << endl;

	string s2("hello world");
	//迭代器，it类似于一个指针，通过it访问元素时需要解引用，begin和end分别返回第一个和'\0'的位置
	string::iterator it = s2.begin();
	while (it != s2.end())
	{
		*it = '*';
		it++;
	}
	cout << s2 << endl;

	//范围for循环：底层也是迭代器
	for (auto c : s2)
	{
		cout << c << endl;
	}
}

int main()
{
	//Test1();
	//Test2();
	Test3();
	return 0;
}
