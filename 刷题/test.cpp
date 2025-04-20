#include <bits/stdc++.h>
using namespace std;

bool check(char c)
{
    if(c >= 'a' && c <= 'z') return false;
    if(c >= 'A' && c <= 'Z') return false;
    if(c >= '0' && c <= '9') return false;
    return true;
}

bool notBackspace(char c)
{
    if(c >= 'a' && c <= 'z') return false;
    if(c >= 'A' && c <= 'Z') return false;
    if(c >= '0' && c <= '9') return false;
    if(c == ' ') return false;
    return true;
}

void solve()
{
    string s;
    getline(cin, s);
    cout << s << "\n";

    while(*s.begin() == ' ') s.erase(s.begin());
    while(*s.rbegin() == ' ') s.pop_back();
    for(int i = 1; i < s.size(); i++)
    {
        if(s[i] == ' ' && s[i - 1] == ' ')
        {
            s.erase(i - 1, 1);
            i = i - 1;
        }
    }
    for(int i = 1; i < s.size(); i++)
    {
        if(notBackspace(s[i]) && s[i - 1] == ' ')
        {
            s.erase(i - 1, 1);
            i = i - 1;
        }
    }
    
    for(int i = 0; i < s.size(); i++)
        if(s[i] != 'I' && s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
    
    s = " " + s + " ";
    for(int L = 0; L + 8 < s.size(); L++)
    {
        int R = L + 8;
        if(check(s[L]) && check(s[R]))
        {
            string t = s.substr(L + 1, 7);
            if(t == "can you") s.replace(L + 1, 7, "# can");
        }
    }
    for(int L = 0; L + 10 < s.size(); L++)
    {
        int R = L + 10;
        if(check(s[L]) && check(s[R]))
        {
            string t = s.substr(L + 1, 9);
            if(t == "could you") s.replace(L + 1, 9, "# could");
        }
    }
    for(int L = 0; L + 2 < s.size(); L++)
    {
        int R = L + 2;
        if(check(s[L]) && check(s[R]))
        {
            string t = s.substr(L + 1, 1);
            if(t == "I") s.replace(L + 1, 1, "you");
        }
    }
    for(int L = 0; L + 3 < s.size(); L++)
    {
        int R = L + 3;
        if(check(s[L]) && check(s[R]))
        {
            string t = s.substr(L + 1, 2);
            if(t == "me") s.replace(L + 1, 2, "you");
        }
    }
    
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == '?') s[i] = '!';
        if(s[i] == '#') s[i] = 'I';
    }
    while(*s.begin() == ' ') s.erase(s.begin());
    while(*s.rbegin() == ' ') s.pop_back();
    cout << "AI: " <<  s << "\n";
}

int main()
{
    int n;
    cin >> n;
    getchar();
    while(n--) solve();
    return 0;
}