
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main()
{
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;
    vector<int> wt(n), val(n);

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++)
        cin >> wt[i];

    cout << "Enter values of items:\n";
    for (int i = 0; i < n; i++)
        cin >> val[i];

    cout << "Enter knapsack capacity: ";
    cin >> W;

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (wt[i - 1] <= w)
            {
                dp[i][w] = max(
                    dp[i - 1][w],
                    val[i - 1] + dp[i - 1][w - wt[i - 1]]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "Maximum value = " << dp[n][W] << endl;

    return 0;
}
