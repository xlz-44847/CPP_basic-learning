#include<string>
#include<vector>
#include<iostream>
using namespace std;
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param s string字符串 第一个整数
     * @param t string字符串 第二个整数
     * @return string字符串
     */
    int mul(int a, int b, int& c)
    {
        int res = a * b + c;
        c = res / 10;
        return res % 10;
    }
    string solve(string s, string t) {
        vector<int> v;
        v.resize(s.size() * t.size(), 0);
        int c = 0;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            int lower = s.size() - 1 - i;
            int factor = 0;
            for (int j = t.size() - 1; j >= 0; j--)
            {
                factor = t.size() - 1 - j;
                c += v[lower + factor];
                v[lower + factor] = mul(s[i] - '0', t[j] - '0', c);
            }
            int k = 1;
            while (c != 0)
            {
                v[lower + factor + k] = mul(0, 0, c);
            }
        }
        string ret;
        int i = v.size() - 1;
        while (v[i] == 0)
            i--;
        for (; i >= 0; i--)
        {
            ret += v[i] + '0';
        }
        return ret;
    }
};
void main()
{
    Solution s;
    cout<<s.solve("11", "99")<<endl;
}