def lexico_compare(a, b):
    i = 0
    while i < len(a) and i < len(b):
        if a[i] < b[i]:
            return -1
        elif a[i] > b[i]:
            return 1
        i += 1
    if len(a) < len(b):
        return -1
    elif len(a) > len(b):
        return 1
    return 0

def compute_b(a):
    n = len(a)
    dp = [[] for _ in range(n + 1)]
    for i in range(n - 1, -1, -1):
        max_suffix = []
        for j in range(i + 1, n):
            if a[j] <= a[i]:
                if lexico_compare(dp[j], max_suffix) > 0:
                    max_suffix = dp[j]
        dp[i] = [a[i]] + max_suffix
        if i < n - 1 and lexico_compare(dp[i + 1], dp[i]) > 0:
            dp[i] = dp[i + 1]
    return dp[0]

def solve():
    n = int(input())
    a = list(map(int, input().split()))
    
    
    best_b = compute_b(a)
    
    
    for j in range(n):
        
        s = [a[j]] + a[:j] + a[j + 1:]
        b_new = compute_b(s)
        if lexico_compare(b_new, best_b) > 0:
            best_b = b_new
    
    return best_b


t = int(input())
for _ in range(t):
    result = solve()
    print(" ".join(map(str, result)))
    