import sys

def is_square(s: str) -> bool:
    m = len(s)
    return s[:m//2] == s[m//2:]

def solve():
    it = iter(sys.stdin.read().split())
    t = int(next(it))
    k = int(next(it))
    out = []
    for _ in range(t):
        n = int(next(it))
        s = next(it)
        if n % 2 == 1:
            out.append("-1")
            continue

        L = 3 * n
        if is_square(s):
            out.append("1")
            out.append(" ".join(["1"] * L))
            continue

        ans = [1] * L
        half = n // 2
        for i in range(half):
            a0 = i * 3
            b0 = (i + half) * 3
            a = s[a0:a0+3]
            b = s[b0:b0+3]
            if a == b:
                continue
            if a[:2] == b[1:]:
                ans[a0+2] = 2
                ans[b0+0] = 2
            else:
                ans[a0+0] = 2
                ans[b0+2] = 2

        out.append("2")
        out.append(" ".join(map(str, ans)))

    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    solve()
