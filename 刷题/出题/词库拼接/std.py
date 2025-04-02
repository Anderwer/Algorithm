import sys

N = 2000010
charsize = 27
Trie = [[0] * charsize for _ in range(N)]
isend = [0] * N
cnt = 0

def insert(s):
    global Trie, isend, cnt
    cur = 0
    for c in s:
        x = ord(c) - ord('a')
        if Trie[cur][x] == 0:
            cnt = cnt + 1
            Trie[cur][x] = cnt
        cur = Trie[cur][x]
    isend[cur] = True

def search(s):
    global Trie, isend, cnt
    cur = 0
    for c in s:
        x = ord(c) - ord('a')
        if Trie[cur][x] == 0:
            return False
        cur = Trie[cur][x]
    return isend[cur]

def solve():
    input = sys.stdin.read().split()
    n = int(input[0])
    strings = input[1:n+1]

    for s in strings:
        insert(s)
    
    ans = 0
    for s in strings:
        m = len(s)
        for j in range(m-1):  # 分割点为j，分割成[0..j]和[j+1..m-1]
            if search(s[0:j+1]) and search(s[j+1:m]):
                ans += 1

    print(ans)

if __name__ == "__main__":
    solve()