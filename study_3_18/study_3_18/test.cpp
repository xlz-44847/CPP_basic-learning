#include<iostream>
using namespace std;

void Test1()
{
	string s1("hello world");
	cout << s1 << endl;
	//push_back(char c)
	//在字符串尾插字符
	s1.push_back('!');
	cout << s1 << endl;
	//append()--append有许多接口
	//在字符串尾插字符串
	s1.append("have a good time");
	cout << s1 << endl;
	//+=
	//尾插字符或字符串
	s1 += '!';
	cout << s1 << endl;
	s1 += "Perfect";
	cout << s1 << endl;

	//assign()
	//赋值（覆盖）
	s1.assign("hello");
	cout << s1 << endl;
}

void Test2()
{
	//insert()
	//在pos位置插入
	string s1("hello");
	s1.insert(3, " *** ");
	cout << s1 << endl;
	//erase(size_t pos = 0, size_t len = npos)
	//在pos位置删除len长度字符串，缺省pos从开头删，缺省len删到结尾为止
	s1.erase(3, 2);
	cout << s1 << endl;
	//replace(pos, len, str)
	//把pos位置开始的len长度替换为str字符串
	s1.replace(3, 2, "&& & &&");
	cout << s1 << endl;
	//size_t find(str/char, pos)
	//从pos位置找对应的字符串/字符，找到返回下标，没找到返回npos
	size_t pos = 0;
	while ((pos = s1.find(' ', pos)) != string::npos)
	{
		s1.replace(pos, 1, "##");
	}
	cout << s1 << endl;

	//insert、erase、replace基本都会挪动数据，效率不高

	
}
bool isPalindrome(string s) {
	string tmp;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] <= 'z' && s[i] >= 'a')
		{
			tmp += s[i];
		}
		else if (s[i] <= 'Z' && s[i] >= 'A')
		{
			tmp += s[i] - 'A' + 'a';
		}
	}
	int left = 0, right = tmp.size() - 1;
	while (left < right)
	{
		if (tmp[left] != tmp[right])
			return false;
		left++;
		right--;
	}
	return true;
}

string addStrings(string num1, string num2) {
	int n1 = 0, n2 = 0;
	for (int i = 0; i < num1.size(); i++)
	{
		n1 *= 10;
		n1 += num1[i] - '0';
	}
	for (int i = 0; i < num2.size(); i++)
	{
		n2 *= 10;
		n2 += num2[i] - '0';
	}
	int sum = n1 + n2;
	string s;
	while (sum)
	{
		int tmp = sum % 10;
		s += tmp + '0';
		sum /= 10;
	}
	return s;
}

int main()
{
	//Test1();
	//Test2();
	//isPalindrome("0a");
	addStrings("11", "123");
	return 0;
}