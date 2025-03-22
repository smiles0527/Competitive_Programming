import sys
import math
input_data = sys.stdin.buffer.read().split()
it = iter(input_data)
n = int(next(it))
q = int(next(it))
a = [0]*(n+1)
for i in range(1, n+1):
    a[i] = int(next(it))
size = 1
while size < n:
    size *= 2
seg = [(0, 0)]*(2*size)
freq = [0]*(n+1)
for i in range(1, n+1):
    freq[a[i]] += 1
for i in range(1, n+1):
    seg[size-1+i] = (freq[i], i)
for i in range(size-1, 0, -1):
    seg[i] = seg[2*i] if seg[2*i][0] >= seg[2*i+1][0] else seg[2*i+1]
def seg_update(pos, val):
    idx = size - 1 + pos
    seg[idx] = (val, pos)
    idx //= 2
    while idx:
        left = seg[2*idx]
        right = seg[2*idx+1]
        seg[idx] = left if left[0] >= right[0] else right
        idx //= 2
class Fenw:
    __slots__ = ('n','tree')
    def __init__(self, n):
        self.n = n
        self.tree = [0]*(n+1)
    def update(self, i, delta):
        while i <= self.n:
            self.tree[i] += delta
            i += i & -i
    def query(self, i):
        s = 0
        while i:
            s += self.tree[i]
            i -= i & -i
        return s
    def find_first(self):
        idx = 0
        bit = 1 << (self.n.bit_length())
        while bit:
            nxt = idx + bit
            if nxt <= self.n and self.tree[nxt] == 0:
                idx = nxt
            bit //= 2
        return idx+1 if idx < self.n else None
    def find_last(self):
        tot = self.query(self.n)
        if tot == 0:
            return None
        idx = 0
        bit = 1 << (self.n.bit_length())
        need = tot
        while bit:
            nxt = idx + bit
            if nxt <= self.n and self.tree[nxt] < need:
                need -= self.tree[nxt]
                idx = nxt
            bit //= 2
        return idx+1
fenw = Fenw(n)
active = [0]*(n+1)
for v in range(1, n+1):
    if freq[v] > 0:
        active[v] = 1
        fenw.update(v, 1)
out_lines = []
for _ in range(q):
    i_val = int(next(it))
    x = int(next(it))
    old = a[i_val]
    if old != x:
        a[i_val] = x
        freq[old] -= 1
        seg_update(old, freq[old])
        if freq[old] == 0:
            if active[old]:
                active[old] = 0
                fenw.update(old, -1)
        if freq[x] == 0:
            if not active[x]:
                active[x] = 1
                fenw.update(x, 1)
        freq[x] += 1
        seg_update(x, freq[x])
    tot_active = fenw.query(n)
    if tot_active < 2:
        out_lines.append("0")
    else:
        L = fenw.find_first()
        R = fenw.find_last()
        m_val, r = seg[1]
        if freq[L] + freq[R] >= m_val:
            ans = R - L
        else:
            ans = max(abs(r - L), abs(R - r))
        out_lines.append(str(ans))
sys.stdout.write("\n".join(out_lines))
