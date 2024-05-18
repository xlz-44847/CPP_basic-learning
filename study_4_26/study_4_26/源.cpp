#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    vector<vector<int>> dp(n + 2, vector<int>(m + 2));
    dp[0][1] = 1;
    for (int i = 1; i < n + 2; i++) {
        for (int j = 1; j < m + 2; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            if (i != n + 1 && j != m + 1) {
                if (i - 1 != x && j - 1 != y && abs(i - x - 1) + abs(j - y - 1) == 3) {
                    dp[i][j] = 0;
                }
                else if (i - 1 == x && j - 1 == y) {
                    dp[i][j] = 0;
                }
            }

            cout << i << ',' << j << ':' << dp[i][j] << endl;
        }
    }
    cout << dp[n + 1][m + 1];
}
// 64 Î»Êä³öÇëÓÃ printf("%lld")