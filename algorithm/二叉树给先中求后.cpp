#include<iostream>
#include<string>
using namespace std;
void dfs(string mid, string front)
{
	char root = front[0];
	int L_len = mid.find(root);
	int R_len = mid.size() - L_len - 1;
	if(L_len){
		string L_mid = mid.substr(0,L_len);
		string L_front = front.substr(1,L_len);
		dfs(L_mid,L_front);
	}
	if(R_len){
		string R_mid = mid.substr(L_len+1,R_len);
		string R_front = front.substr(L_len+1,R_len);
		dfs(R_mid,R_front);
	}
	cout << root;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	string mid,front;
	cin>>mid>>front;
	dfs(mid,front);
	return 0;
}