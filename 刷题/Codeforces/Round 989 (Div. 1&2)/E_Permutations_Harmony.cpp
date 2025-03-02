#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 n, k;
    cin >> n >> k;

    if(n % 2 == 0 && k % 2 == 1) {cout << "NO\n"; return;}
    if(n == 1 && k == 1) {cout << "YES\n" << "1\n"; return;}
    i64 fac = 1; //处理 n!
    for(int i = 1; i <= n && fac < k + 5; i++) fac *= i;
    if(fac < k) {cout << "NO\n"; return;}
    if(k == 1 || k == fac - 1) {cout << "NO\n"; return;}

    if(k % 2 == 0) // k 偶数
    {
        vector<int> a(n);
        for(int i = 0; i < n; i++) a[i] = i + 1;
        vector<vector<int>> ans;
        for(int i = 1; i <= k / 2; i++)
        {
            vector<int> b(n);
            for(int j = 0; j < n; j++) b[j] = n - a[j] + 1;
            ans.push_back(a);
            ans.push_back(b);
            next_permutation(a.begin(), a.end());
        }
        
        cout << "YES\n";
        for(auto& v : ans)
        {
            for(auto& x : v) cout << x << " ";
            cout << "\n";
        }
    }
    else // k 奇数
    {
        vector<int> a(n);
        for(int i = 0; i < n; i++) a[i] = i + 1;
        vector<vector<int>> ans;
        set<vector<int>> vis;
        reverse(a.begin(), a.end()); //先变成 {7, 6, 5, 4, 3, 2, 1}
        i64 sum = (3 * (n + 1)) / 2;
        vis.insert(a);
        ans.push_back(a);
        vector<int> b(n);
        for(int i = 0, now = sum - n - 1; i < n; i++, now--)
        {
            if(now == 0) now = n;
            b[i] = now;
        }
        vis.insert(b);
        ans.push_back(b);
        for(int i = 0; i < n; i++) b[i] = sum - a[i] - b[i];
        vis.insert(b);
        ans.push_back(b);
        reverse(a.begin(), a.end()); //再变回 {1, 2, 3, 4, 5, 6, 7}
        while(ans.size() < k)
        {
            for(int j = 0; j < n; j++) b[j] = n - a[j] + 1;
            if(vis.count(a) == 0 && vis.count(b) == 0)
            {
                ans.push_back(a);
                ans.push_back(b);
            }
            next_permutation(a.begin(), a.end());
        }

        cout << "YES\n";
        for(auto& v : ans)
        {
            for(auto& x : v) cout << x << " ";
            cout << "\n";
        }
    }

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

/*
首先要满足 每一列的和都相等
我们先计算所有的和 sum = k * (n * (n + 1)) / 2
因此每一列的和 = sum / n = (k * (n + 1)) / 2
如果 (k * (n + 1)) 不是偶数的话, 就凑不齐每一列的和相等, 不满足条件
因此, 当 k 和 (n + 1) 都是奇数的情况下是不成立的 (k 是奇数且 n 是偶数)

接下来分类讨论
1#. 当 k 是偶数时, 如下

1 2 3 4 5 6 a
6 5 4 3 2 1 b

1 2 3 4 6 5
6 5 4 3 1 2
...
我们总能得到一个排列, 然后以这个排列为基准互补, 如第 i 个位置的 b[i] = n - a[i] + 1, 这样构造出来的 b 也是一个排列
n 个数的排列方式有 n! 种, 如果 n! < k 则不成立, 否则总能构造出答案

2#. 当 k 是奇数时
首先 k = 1 且 n != 1 的情况下, 此时只有一排无法互补, 因此不成立
其次 k = n! - 1 也是不成立的, 首先需要花3个排列使得变为第一种形式, 则还需要 n! - 4 种排列, 但此时只剩下 n! - 3 种排列可选且还要凑成偶数形式, 两者奇偶性不同无法凑齐
由最上方的分析得, 当 k 是奇数且 n 是奇数的情况下才有解
因此我们可以先特判是否 (k == 1 && n == 1), 否则 k >=3 才有解
我们先观察一下前三排的构造情况, 然后 k -= 3,  之后就成第一种构造形式了

现在来构造前三排, 由于上面算出了每一列的和为 (k * (n + 1)) / 2
举例 n = 7的时候, 前三排的和为 (3 * (7 + 1)) / 2 = 12
我们以第一排的开头为 n, 第三排的开头为 1 来构造
第一排 : {7, 6, 5, 4, 3, 2, 1}, 则此时还需要 {5, 6, 7, 8, 9, 10, 11}
第二排 : {4, 3, 2, 1, 7, 6, 5}, 则此时还需要 {1, 3, 5, 7, 2, 4, 6}
第三排 : {1, 3, 5, 7, 2, 4, 6}, 构造完成
接下来把这三个排列都存进一个 map 中, 在下面进行第一种形式时特判一下即可 
*/