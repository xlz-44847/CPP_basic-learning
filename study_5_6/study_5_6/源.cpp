#include <iostream>
#include <stack>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--)
    {
        cout << t;
        int n;
        cin >> n;
        string s(n + 1, 0);
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
        }
        cout << s;
        int left = 0, right = n - 1;
        int flag = 1;
        while (left <= right)
        {
            if (s[left] != s[right])
            {
                flag = 0;
                cout << "No" << endl;
                break;
            }
            else {
                left++;
                right--;
            }
        }
        if (flag)
        {
            cout << "Yes" << endl;
        }
        cout << "end";
    }
}

/*
int n;
cin>>n;
char ch;
stack<char> s;
for(int i=0;i<n;i++)
{
    //4:0 1   2 3      4/2=2
    //5:0 1   2   3 4  5/2=2
    cin>>ch;
    //cout<<i<<ch<<endl;
    if(i<n/2)
    {
        s.push(ch);
    }
    else if(n%2==1&&i==n/2)
    {
        continue;
    }
    else if(ch==s.top())
    {
        s.pop();
    }
    else {
        break;
    }
}
if(s.empty())
{
    cout<<"Yes"<<endl;
}
else {
    cout<<"No"<<endl;
}
}
}
// 64 Î»Êä³öÇëÓÃ printf("%lld")*/