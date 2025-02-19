d = int(input())
e = int(input())
current = d
for _ in range(e):
    op = input().strip()
    q = int(input())
    if op == '+':
        current += q
    else:
        current -= q
print(current)