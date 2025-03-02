const int N = 100010;
const int charsize = 26;
int Trie[N + 1][charsize];
bool isend[N + 1];
int root = 0, cnt = 0;

void insert(string& s)
{
    int cur = 0;
    for(auto c : s)
    {
        int x = c - 'a';
        if(!Trie[cur][x]) Trie[cur][x] = ++cnt;
        cur = Trie[cur][x];
    }
    isend[cur] = true;
}

bool search(string& s)
{
    int cur = 0;
    for(auto c : s)
    {
        int x = c - 'a';
        if(!Trie[cur][x]) return false;
        cur = Trie[cur][x];
    }
    return isend[cur];
}