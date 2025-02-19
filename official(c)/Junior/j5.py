R, C, M = map(int, input().split())

prev = [(j % M) + 1 for j in range(C)]
cur = [0] * C

for i in range(1, R):
    for j in range(C):
        cost = ((i * C + j) % M) + 1
        mn = prev[j]
        if j > 0:
            mn = min(mn, prev[j-1])
        if j < C - 1:
            mn = min(mn, prev[j+1])
        cur[j] = cost + mn
    prev, cur = cur, prev

ans = min(prev)
print(ans)