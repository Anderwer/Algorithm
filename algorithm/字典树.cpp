const int N = 100010;
const int charsize = 26;
int nxt[N + 1][charsize];
bool isend[N + 1];
int root = 0, cnt = 0;

void insert(string& s)
{
    int now = 0;
    for(auto& c : s)
    {
        int x = c - 'a';
        if(!nxt[now][x]) nxt[now][x] = ++cnt;
        now = nxt[now][x];
    }
    isend[now] = true;
}

bool search(string& s)
{
    int now = 0;
    for(auto& c : s)
    {
        int x = c - 'a';
        if(!nxt[now][x]) return false;
        now = nxt[now][x];
    }
    return isend[now];
}

