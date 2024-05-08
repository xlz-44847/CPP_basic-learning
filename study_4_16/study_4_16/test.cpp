#include <iostream>
using namespace std;

int main() {
    string s;
    s.reserve(300000);
    string ss;
    ss.reserve(s.capacity());
    cin >> s;
    bool flag = true;
    while (flag) {
        int prev = 0, next = 1;
        flag = false;
        while (next < s.size()) {
            if (s[next] == s[prev]) {
                //s.erase(prev, 2);
                flag = true;
                next += 2;
                prev += 2;
            }
            else {
                ss += s[prev];
                ++next;
                ++prev;
            }
        }
        if (next == s.size()) {
            ss += s[prev];
        }
        swap(s, ss);
        ss.clear();
    }
    if (s.size() == 0) {
        cout << 0 << endl;
    }
    else {
        cout << s << endl;
    }

}