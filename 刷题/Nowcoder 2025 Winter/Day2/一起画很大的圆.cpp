#include <iostream>
#include <cmath>
#include <algorithm>
using i64 = long long;
using ld = long double;
using namespace std;

ld get(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3)
{
    ld x,y,r,A,B,C,D;
	A=x1*(y2-y3)-y1*(x2-x3)+x2*y3-x3*y2;
	B=(x1*x1+y1*y1)*(y3-y2)+(x2*x2+y2*y2)*(y1-y3)+(x3*x3+y3*y3)*(y2-y1);
	C=(x1*x1+y1*y1)*(x2-x3)+(x2*x2+y2*y2)*(x3-x1)+(x3*x3+y3*y3)*(x1-x2);
	D=(x1*x1+y1*y1)*(x3*y2-x2*y3)+(x2*x2+y2*y2)*(x1*y3-x3*y1)+(x3*x3+y3*y3)*(x2*y1-x1*y2);
	
	x=-B/(2*A);
	y=-C/(2*A);
	r=sqrt((B*B+C*C-4*A*D)/(4*A*A));

    if(!A) return -1;
    return r;
}

void solve()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    
    int x_ = (a + b) / 2;
    ld r = 0;
    int resX = 0;
    for(int x = max(a, (x_ - 10)); x <= min(b, (x_ + 10)); x++)
    {
        ld rr = get(a, c, b, d, x, d);
        if(rr > r)
        {
            r = rr;
            resX = x;
        }
    }
    cout << a << " " << c << "\n";
    cout << b << " " << d << "\n";
    cout << resX << " " << d << "\n";
    
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
