
求前缀数组next函数
vector<int> getnext(string s)
{
	int n = (int)s.size();
	vector<int> next(n);
	for(int i = 1; i < n; i++) {//从s[1]开始
		int j = next[i-1]; //定位当前前缀的下一个位置 假如abccabce 当 s[i] = 'e' 时 j 定位在前缀"abc"的后面 s[j] = 'c' 
		while(j > 0 && s[i] != s[j]) j = next[j-1]; //j如果定位在s[0] 则没有匹配的前后缀
		if(s[i] == s[j]) j++;						// 如果s[i] != s[j] 则让j定位到上述"abc"中的'c',
		next[i] = j;		   				    	//如果再找不到就定位到"abc"中的b 以此类推
	}   //如果相等,则统计的前缀长度+1
	return next;
}

kmp 实现find函数

int kmp(string& s,string& patt) //s是主串,patt是子串
{
	vector<int> next = getnext(patt);//获取字串next数组
	int i = 0, j = 0; // i 子串指针   j 主串指针
	int n = (int)s.size();
	int len = (int)patt.size();
	while(i < n) {
		if(s[i] == patt[j]) { //字符匹配,指针后移
			i++;
			j++;
		}
		else if(j > 0) j = next[j-1]; //字符失配,根据next数组跳过一部分字串
		else i++; //字串第一个字符就失配的情况
		if(j == len) return i-j;
	}
}

完整代码块:

vector<int> getnext(string s)
{
	int n = (int)s.size();
	vector<int> next(n);
	for(int i = 1; i < n; i++) {//从s[1]开始
		int j = next[i-1]; //定位当前前缀的下一个位置 假如abccabce 当 s[i] = 'e' 时 j 定位在前缀"abc"的后面 s[j] = 'c' 
		while(j > 0 && s[i] != s[j]) j = next[j-1]; //j如果定位在s[0] 则没有匹配的前后缀
		if(s[i] == s[j]) j++;						// 如果s[i] != s[j] 则让j定位到上述"abc"中的'c',
		next[i] = j;		   				    	//如果再找不到就定位到"abc"中的b 以此类推
	}   //如果相等,则统计的前缀长度+1
	return next;
}
vector<int> kmp(string& s,string& patt) //s是主串,patt是子串
{
	vector<int> ans;
	vector<int> next = getnext(patt);//获取字串next数组
	int i = 0, j = 0; // i 子串指针   j 主串指针
	int n = (int)s.size();
	int len = (int)patt.size();
	while(i < n) {
		if(s[i] == patt[j]) { //字符匹配,指针后移
			i++;
			j++;
		}
		else if(j > 0) j = next[j-1]; //字符失配,根据next数组跳过一部分字串
		else i++; //字串第一个字符就失配的情况
		if(j == len) ans.push_back(i-j);
	}
	return ans;
}

