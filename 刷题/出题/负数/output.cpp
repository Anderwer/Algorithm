#include <bits/stdc++.h>
#include <fstream>
using i64 = long long;
using namespace std;

void solve(ifstream& inFile, ofstream& outFile)
{
    int n;
    inFile >> n; //读入 n
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) inFile >> a[i]; //读入数据

    int ans = 0;
    /*
    
    这里放正确代码, 用来跑答案    
    
    */

    outFile << ans << "\n"; //将答案写入 .out文件中
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int Num = 10;
    for(int i = 0; i < Num; i++)
    {
        std::string inName = "./source/" + to_string(i) + ".in";
        std::string outName = "./source/" + to_string(i) + ".out";    
        ifstream inFile(inName);
        std::ofstream outFile(outName);

        int t;
        inFile >> t;

        while(t--) solve(inFile, outFile);

        inFile.close();
        outFile.close();

        std::cout << "The " << i << " group get\n";
    }
    
    getchar();
    
    return 0;
}
