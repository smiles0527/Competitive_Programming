a = int(input())
b = int(input())
c = int(input())
d = int(input())
s = int(input())

def steps(f, r, m):
    total1, steps1 = 0, 0
    while total1 < m:
        if total1 + f <= m:
            steps1 += f
            total1 += f
        elif total1 + f > m:
            steps1 += m - total1
            total1 += m - total1
        if total1 + r <= m:
            steps1 -= r
            total1 += r
        elif total1 + r > m:
            steps1 -= m - total1
            total1 += m - total1
    return steps1

if steps(a, b, s) > steps(c, d, s):
    print("Nikky")
elif steps(a, b, s) < steps(c, d, s):
    print("Byron")
else:
    print("Tied")