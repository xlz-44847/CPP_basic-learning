#include<iostream>
using namespace std;

//void Reverse(string& s, int pos, int end)
//{
//    int left = pos, right = end;
//    while (left < right)
//    {
//        swap(s[left], s[right]);
//        ++left;
//        --right;
//    }
//}
//string reverseStr(string s, int k) {
//    int cou = 1;
//    int begin, end;
//    for (int i = 0; i < s.length(); i++, cou++)
//    {
//        if (cou == 1)
//        {
//            begin = i;
//        }
//        if (cou == k)
//        {
//            end = i;
//        }
//        if (cou == 2 * k)
//        {
//            Reverse(s, begin, end);
//            cou = 0;
//        }
//    }
//    if (cou < k)
//    {
//        Reverse(s, begin, s.size() - 1);
//    }
//    else
//    {
//        Reverse(s, begin, end);
//    }
//    return s;
//}

//void Reverse(string& s, int pos, int end)
//{
//    int left = pos, right = end;
//    while (left < right)
//    {
//        swap(s[left], s[right]);
//        ++left;
//        --right;
//    }
//}
//string reverseWords(string s) {
//    int begin = 0;
//    size_t end = 0;
//    while ((end = s.find(' ',begin)) != string::npos)
//    {
//        Reverse(s, begin, end - 1);
//        begin = end + 1;
//    }
//
//    return s;
//}

//int add(int& ci, int a = 0, int b = 0)
//{
//    int sum = a + b + ci;
//    ci = sum / 10;
//    return sum % 10;
//}
//string addStrings(string num1, string num2) {
//    int n1 = num1.size() - 1, n2 = num2.size() - 1;
//    int ci = 0;
//    string s;
//    while (n1 >= 0 && n2 >= 0)
//    {
//        s += add(ci, num1[n1] - '0', num2[n2] - '0') + '0';
//        --n1;
//        --n2;
//    }
//    while (n1 >= 0)
//    {
//        s += add(ci, num1[n1] - '0') + '0';
//        --n1;
//    }
//    while (n2 >= 0)
//    {
//        s += add(ci, num2[n2] - '0') + '0';
//        --n2;
//    }
//    if (ci != 0)
//    {
//        s += ci + '0';
//    }
//    int left = 0, right = s.size() - 1;
//    while (left < right)
//    {
//        swap(s[left], s[right]);
//        left++;
//        right--;
//    }
//    return s;
//}
//int mul(int& ci, int a, int b)
//{
//    int sum = a * b + ci;
//    ci = sum / 10;
//    return sum % 10;
//}
//string mulstring(string s1, char c, int cou)
//{
//    string ret;
//    int ci = 0;
//    for (int i = s1.size() - 1; i >= 0; i--)
//    {
//        ret += '0' + mul(ci, s1[i] - '0', c - '0');
//    }
//    if (ci != 0)
//    {
//        ret += ci + '0';
//    }
//    int left = 0, right = ret.size() - 1;
//    while (left < right)
//    {
//        swap(ret[left], ret[right]);
//        left++;
//        right--;
//    }
//    for (int i = 0; i < cou; i++)
//    {
//        ret += '0';
//    }
//    return ret;
//}
//string multiply(string num1, string num2) {
//    string ret("0");
//    if (num1 == "0" || num2 == "0")
//    {
//        return ret;
//    }
//    int n1 = num1.size() - 1;
//    int cou = 0;
//    while (n1 >= 0)
//    {
//        ret = addStrings(ret, mulstring(num2, num1[n1], cou));
//        --n1;
//        ++cou;
//    }
//    return ret;
//}
//int main()
//{
//    cout<<multiply("123", "456")<<endl;
//}

void Test1()
{
	//c_str--返回c形式的字符串，兼容c语言的字符串函数
	string s1("hello world");
	cout << strlen(s1.c_str()) << endl;

	//size_t find (const string& str / char c, size_t pos = 0) const;	find从pos位置开始查找指定字符串、字符，返回下标
	//size_t rfind (const string& str, size_t pos = npos) const;	rfind，从后往前找
	//string substr(size_t pos = 0, size_t len = npos) const;	取出pos开始len长的子串

	string s2("abc#def#ghi");
	cout << s2.substr(s2.find('#')) << endl;
	cout << s2.substr(s2.rfind('#')) << endl;

}

int main()
{
	Test1();
}