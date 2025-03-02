t = int(input())
N = 10010

while t > 0:
    t = t - 1
    n = int(input())
    a = list(map(int, input().split()))

    cnt = [0 for i in range(N)]
    for num in a:
        if num < 0:
            cnt[-num] += 1
        else:
            cnt[num] += 1
    
    ans = 0
    for i in range(N):
        if cnt[i] > 2:
            ans += 2
        else:
            ans += cnt[i]

    if cnt[0] > 1:
        ans -= 1
    
    print(ans)
