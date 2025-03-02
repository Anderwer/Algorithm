#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1E7 + 10;
const int charsize = 26;
int Trie[N + 10][charsize];  
bool isend[N + 10];
int cnt = 0, Max = 0;

void insert(string& s)
{
    int cur = 0;
    for (auto c : s)
    {
        int x = c - 'a';
        if (!Trie[cur][x]) Trie[cur][x] = ++cnt;
        cur = Trie[cur][x];
    }
    isend[cur] = true;
}

bool search(string& s, int L, int R)
{
    int cur = 0;
    for (int i = L; i <= R; i++)
    {
        int x = s[i] - 'a';
        if (!Trie[cur][x]) return false;
        cur = Trie[cur][x];
    }
    return isend[cur];
}

void solve(ifstream& inFile, ofstream& outFile)
{
    int Sum = 0;
    int n;
    inFile >> n;
    vector<string> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        inFile >> a[i];
        Sum += a[i].size();
    }

    for (int i = 1; i <= n; i++) insert(a[i]);

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int len = a[i].size();
        for (int j = 0; j < len - 1; j++) //分割成 [0, j] 和 [j + 1, len - 1]
        {
            if (search(a[i], 0, j) && search(a[i], j + 1, len - 1)) ans++;
        }
    }
    outFile << ans;

    Max = max(Max, Sum);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int Num = 30;
    for (int i = 0; i < Num; i++)
    {
        std::string inName = "./source/" + to_string(i) + ".in";
        std::string outName = "./source/" + to_string(i) + ".out";
        ifstream inFile(inName);
        std::ofstream outFile(outName);

        for (int i = 0; i <= N; i++) for (int j = 0; j < charsize; j++) Trie[i][j] = 0;
        for (int i = 0; i <= N; i++) isend[i] = 0;
        cnt = 0;
        solve(inFile, outFile);

        inFile.close();
        outFile.close();

        std::cout << "The " << i << " group get\n";
    }

    cout << Max << "\n";
    getchar();

    return 0;
}
