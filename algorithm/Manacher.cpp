Manacher 算法用于预处理出回文信息: p[i] 数组

给定一个长度为n字符串s,找到所有的对(i,j)使得s[i...j]为一个回文串

char s[N], ss[N << 1];
int p[N << 1], cnt, len;;
void init()
{
    len = strlen(s), cnt = 1;
    ss[0] = '!', ss[cnt] = '#';
    for(int i = 0; i < len; i++) ss[++cnt] = s[i], ss[++cnt] = '#';
}

void manacher() //max(p[i] - 1)是最长回文子串
{
    int pos = 0, mx = 0;
    for(int i = 1; i <= cnt; i++){
        if(i < mx) p[i] = min(p[pos * 2 - i], mx - i);
        else p[i] = 1;
        while(ss[i + p[i]] == ss[i - p[i]]) p[i]++;
        if(mx < i + p[i]) mx = i + p[i], pos = i;
    }
}

则 max(p[i] - 1)是最长回文子串

