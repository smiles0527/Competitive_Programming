#10/12 TLE

import sys

def main():
    it = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(it); k = next(it)

    c = [[[0]*n for _ in range(n)] for __ in range(n)]
    for _ in range(k):
        x = next(it)-1; y = next(it)-1; z = next(it)-1
        c[x][y][z] += 1

    N = 1 << n
    sc = [0] * N

    for m in range(1, N):
        b = m.bit_length() - 1
        p = m ^ (1 << b)
        sc[m] = sc[p]

        ms = []
        os = []
        for i in range(n):
            if (m >> i) & 1:
                ms.append(i)
            else:
                os.append(i)

        for x in ms:
            for o in os:
                sc[m] -= c[x][b][o] + c[x][o][b]

        for o1 in os:
            for o2 in os:
                sc[m] += c[b][o1][o2]

    mx = max(sc)
    cnt = sc.count(mx)
    print(mx, cnt)

if __name__ == "__main__":
    main()
