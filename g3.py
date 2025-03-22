import sys,math,bisect
input=sys.stdin.readline



class CandidateSegTree:
    def __init__(self, n):
        self.n = n
        self.size = 1
        while self.size < n:
            self.size *= 2
        
        self.tree = [-1]*(2*self.size)
    def build(self, arr):
        
        for i in range(self.n):
            self.tree[self.size+i] = arr[i]
        for i in range(self.n, self.size):
            self.tree[self.size+i] = -1
        for i in range(self.size-1, 0, -1):
            self.tree[i] = max(self.tree[2*i], self.tree[2*i+1])
    def update(self, idx, value):
        
        i = self.size + idx
        self.tree[i] = value
        i //= 2
        while i:
            self.tree[i] = max(self.tree[2*i], self.tree[2*i+1])
            i //= 2
    def query_leftmost(self, threshold):
        
        if self.tree[1] < threshold:
            return None
        i = 1
        while i < self.size:
            if self.tree[2*i] >= threshold:
                i = 2*i
            else:
                i = 2*i+1
        return i - self.size + 1
    def query_rightmost(self, threshold):
        
        if self.tree[1] < threshold:
            return None
        i = 1
        while i < self.size:
            if self.tree[2*i+1] >= threshold:
                i = 2*i+1
            else:
                i = 2*i
        return i - self.size + 1



class FreqSegTree:
    def __init__(self, m):
        self.m = m
        self.size = 1
        while self.size < m:
            self.size *= 2
        self.tree = [0]*(2*self.size)
    def build(self, arr):
        
        for i in range(self.m):
            self.tree[self.size+i] = arr[i]
        for i in range(self.m, self.size):
            self.tree[self.size+i] = 0
        for i in range(self.size-1, 0, -1):
            self.tree[i] = self.tree[2*i] + self.tree[2*i+1]
    def update(self, pos, delta):
        
        i = self.size + pos
        self.tree[i] += delta
        i //= 2
        while i:
            self.tree[i] = self.tree[2*i] + self.tree[2*i+1]
            i //= 2
    def set_val(self, pos, value):
        
        i = self.size + pos
        self.tree[i] = value
        i //= 2
        while i:
            self.tree[i] = self.tree[2*i] + self.tree[2*i+1]
            i //= 2
    def query_global_max(self):
        
        
        if self.tree[1] == 0:
            return 0
        i = 1
        l = 0; r = self.size
        
        
        idx = -1
        i = 1
        lo = 0; hi = self.size
        
        
        
        for f in range(self.m-1, -1, -1):
            
            if self.tree[self.size+f] > 0:
                return f
        return 0
    def query_count(self, pos):
        
        return self.tree[self.size+pos]
    def query_second_max(self, global_max):
        
        if self.query_count(global_max) >= 2:
            return global_max
        
        for f in range(global_max-1, -1, -1):
            if self.tree[self.size+f] > 0:
                return f
        return 0


N,Q = map(int,input().split())

a = list(map(int,input().split()))

