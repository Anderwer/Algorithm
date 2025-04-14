#include <bits/stdc++.h>
using namespace std;
int n;

int main()
{
    bitset<110> a[110];
    cin >> n;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            int w; cin >> w;
            a[i][j] = w;
        }

    for (int j = 1; j <= n; j++)
        for (int i = 1; i <= n; i++)
            if (a[i][j]) a[i] |= a[j];
            
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }
    return 0;
}