import sys
def main():
    data = sys.stdin.read().split()
    it = iter(data)
    n = int(next(it))
    q = int(next(it))
    a = [0]*(n+1)
    f = [0]*(n+1)
    for i in range(1, n+1):
        ai = int(next(it))
        a[i] = ai
        f[ai] += 1
    def compute_answer():
        L = None
        R = None
        M = 0
        for cand in range(1, n+1):
            if f[cand] > 0:
                if L is None:
                    L = cand
                R = cand
                if f[cand] > M:
                    M = f[cand]
        if L is None or L == R:
            return 0
        min_M = None
        max_M = None
        for cand in range(1, n+1):
            if f[cand] == M:
                if min_M is None:
                    min_M = cand
                max_M = cand
        if f[L] + f[R] >= M:
            return R - L
        else:
            return max(max_M - L, R - min_M)
    out_lines = []
    for _ in range(q):
        i_val = int(next(it))
        new_vote = int(next(it))
        old_vote = a[i_val]
        if old_vote != new_vote:
            f[old_vote] -= 1
            a[i_val] = new_vote
            f[new_vote] += 1
        out_lines.append(str(compute_answer()))
    sys.stdout.write("\n".join(out_lines))
if __name__ == '__main__':
    main()
