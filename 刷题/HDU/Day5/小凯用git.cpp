#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

bool LCA(int a, int b, vector<vector<int>>& fa)
{
    if(a == b) return true;
    queue<int> q;
    unordered_set<int> vis;
    q.push(b);
    vis.insert(b);

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        for(auto p : fa[cur])
        {
            if(p == a) return true;
            if(vis.count(p) == 0)
            {
                vis.insert(p);
                q.push(p);
            }
        }
    }
    return false;
}

void solve()
{
    int n;
    cin >> n;

    int cnt = 1;
    map<string, int> branch;
    string cur = "main";
    branch[cur] = 1;
    
    vector<vector<int>> parent(2);
    for(int i = 1; i <= n; i++)
    {
        string cmd; cin >> cmd;
        if(cmd == "commit")
        {
            cnt++;
            parent.resize(cnt + 1);
            parent[cnt].push_back(branch[cur]);
            branch[cur] = cnt;
        }
        else if(cmd == "branch")
        {
            string sub; cin >> sub;
            if(sub == "-d")
            {
                string name; cin >> name;
                if(branch.find(name) != branch.end() && name != cur) 
                    branch.erase(branch.find(name));
            }
            else
            {
                string name = sub;
                int nxt = branch[cur];
                if(cin.peek() != '\n') cin >> nxt;
                if(branch.find(name) == branch.end()) branch[name] = nxt;
            }
        }
        else if(cmd == "merge")
        {
            string nxt; cin >> nxt;
            if(LCA(branch[cur], branch[nxt], parent))
                branch[cur] = branch[nxt];
            else if(LCA(branch[nxt], branch[cur], parent))
                continue;
            else
            {
                cnt++;
                parent.resize(cnt + 1);
                parent[cnt].push_back(branch[cur]);
                parent[cnt].push_back(branch[nxt]);
                branch[cur] = cnt;
            }
        }
        else if(cmd == "checkout")
        {
            string name; cin >> name;
            cur = name;
        }
        else if(cmd == "reset")
        {
            int nxt;
            if(cin.peek() == '\n') nxt = branch[cur];
            else cin >> nxt;
            branch[cur] = nxt;
        }
    }

    cout << branch.size() << "\n";
    for(auto& [x, y] : branch) cout << x << " " << y << "\n";
    cout << cnt << "\n";
    for(int i = 1; i <= cnt; i++)
    {
        cout << parent[i].size() << " ";
        sort(parent[i].begin(), parent[i].end());
        for(auto v : parent[i]) cout << v << " ";
        cout << "\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
