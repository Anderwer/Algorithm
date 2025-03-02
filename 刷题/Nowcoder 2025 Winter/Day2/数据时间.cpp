#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    string h, m;
    cin >> n >> h >> m;
    map<string, bool> vis;
    vector<int> cnt(4, 0);
    if(m.size() == 1) m = "0" + m;
    for(int i = 1; i <= n; i++)
    {
        string id, date, time;
        cin >> id >> date >> time;
        //cout << id << " " << date << " " << time << "\n";
        if(date.substr(0, 4) == h && date.substr(5, 2) == m)
        {
            int hh = stoi(time.substr(0, 2));
            int mm = stoi(time.substr(3, 2));
            int ss = stoi(time.substr(6, 2));
            int cur = hh * 3600 + mm * 60 + ss;
            if((cur >= 25200 && cur <= 32400) || (cur >= 64800 && cur <= 72000)) //通勤
            {
                id += "#1";
                if(vis[id] == false)
                {
                    cnt[1]++;
                    vis[id] = true;
                }
            }
            if((cur >= 39600 && cur <= 46800)) //午休
            {
                id += "#2";
                if(vis[id] == false)
                {
                    cnt[2]++;
                    vis[id] = true;
                }
            }
            if(cur >= 79200 || cur <= 3600) //通勤
            {
                id += "#3";
                if(vis[id] == false)
                {
                    cnt[3]++;
                    vis[id] = true;
                }
            }
        }
    }
    for(int i = 1; i <= 3; i++) cout << cnt[i] << " ";

}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
