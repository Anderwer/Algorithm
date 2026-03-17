from math import sqrt, floor

t = int(input())

for i in range(t):
    n, k = map(int, input().split())
    a = 2
    b = 4 * k - 2
    c = n - n * n - 2 * k * n
    d = 4 * k * k + 4 * k * (n - 1) + 2 * n * n - 2 * n + 1
    i = (-(2 * k - 1) + (floor(sqrt(d)))) // 2
    ans = min(abs(a * i * i + b * i + c), abs(a * (i + 1) * (i + 1) + b * (i + 1) + c)) // 2
    print(ans)
