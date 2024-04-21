#include<iostream>
#include<string>
using namespace std;
void dfs(string mid, string back)
{
	char root = back[back.size()-1];
	int L_len = mid.find(root);
	int R_len = mid.size() - L_len - 1;
	cout << root;
	if(L_len){
		string L_mid = mid.substr(0,L_len);
		string L_back = back.substr(0,L_len);
		dfs(L_mid,L_back);
	}
	if(R_len){
		string R_mid = mid.substr(L_len+1,R_len);
		string R_back = back.substr(L_len,R_len);
		dfs(R_mid,R_back);
	}
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	string mid,back;
	cin>>mid>>back;
	dfs(mid,back);
	return 0;
}