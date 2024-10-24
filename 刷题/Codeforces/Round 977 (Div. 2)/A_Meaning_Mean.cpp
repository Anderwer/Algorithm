#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i = 1; i <= n; i++) 
    {
        int x; cin >> x;
        pq.push(x);
    }
    while(pq.size() >= 2)
    {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        pq.push((a + b) / 2);
    }
    cout << pq.top() << "\n";
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
