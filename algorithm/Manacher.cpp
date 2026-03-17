#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// Manacher
// 用法:
// 1. 传入原串 s(下标从 0 开始的普通 string)
// 2. build(s) 后:
//    - d1[i] 表示以 i 为中心的最长奇回文半径
//    - d2[i] 表示以 i-1 和 i 之间为中心的最长偶回文半径
// 3. longestPalindrome() 返回最长回文子串长度
// 4. isPal(l, r) 判断原串区间 [l, r] 是否为回文串

struct Manacher
{
    string s;
    int n;
    vector<int> d1, d2;

    Manacher() {}
    Manacher(const string& s_)
    {
        build(s_);
    }

    void build(const string& s_)
    {
        s = s_;
        n = (int)s.size();
        d1.assign(n, 0);
        d2.assign(n, 0);

        // 奇回文
        for(int i = 0, l = 0, r = -1; i < n; i++)
        {
            int k = (i > r ? 1 : min(d1[l + r - i], r - i + 1));
            while(i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
            d1[i] = k;
            if(i + k - 1 > r)
            {
                l = i - k + 1;
                r = i + k - 1;
            }
        }

        // 偶回文
        for(int i = 0, l = 0, r = -1; i < n; i++)
        {
            int k = (i > r ? 0 : min(d2[l + r - i + 1], r - i + 1));
            while(i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
            d2[i] = k;
            if(i + k - 1 > r)
            {
                l = i - k;
                r = i + k - 1;
            }
        }
    }

    int longestPalindrome()
    {
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            ans = max(ans, d1[i] * 2 - 1);
            ans = max(ans, d2[i] * 2);
        }
        return ans;
    }

    bool isPal(int l, int r)
    {
        if(l > r) return true;
        int len = r - l + 1;
        int mid = (l + r) >> 1;

        if(len & 1)
        {
            return d1[mid] > len / 2;
        }
        else
        {
            return d2[mid + 1] >= len / 2;
        }
    }

    pair<int, int> longestPalindromePos()
    {
        int bestLen = 0;
        pair<int, int> ans = {0, -1};

        for(int i = 0; i < n; i++)
        {
            int len1 = d1[i] * 2 - 1;
            if(len1 > bestLen)
            {
                bestLen = len1;
                ans = {i - d1[i] + 1, i + d1[i] - 1};
            }

            int len2 = d2[i] * 2;
            if(len2 > bestLen)
            {
                bestLen = len2;
                ans = {i - d2[i], i + d2[i] - 1};
            }
        }

        return ans;
    }
};

/*
示例:

string s;
cin >> s;

Manacher ma(s);

1. 最长回文子串长度
cout << ma.longestPalindrome() << "\n";

2. 判断 [l, r] 是否回文, 下标从 0 开始
if(ma.isPal(l, r))
{
    ...
}

3. 获取最长回文子串左右端点
auto [l, r] = ma.longestPalindromePos();
*/