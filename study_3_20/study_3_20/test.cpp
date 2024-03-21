#include<iostream>
using namespace std;

void Test1()
{
	//从前往后、从后往前找与字符串中包含的字符相匹配、不匹配的字符
	//size_t find_first_of (const string& str, size_t pos = 0) const;
	//size_t find_last_of (const string& str, size_t pos = npos) const;
	//size_t find_first_not_of(const string & str, size_t pos = 0) const;
	//size_t find_last_not_of (const string& str, size_t pos = npos) const;
	string s1("hello world");
	cout << s1.find_first_of("aeiou") << endl;
	cout << s1.find_last_of("aeiou") << endl;
	cout << s1.find_first_not_of("aeiou") << endl;
	cout << s1.find_last_not_of("aeiou") << endl;
}
int main()
{
	Test1();
}