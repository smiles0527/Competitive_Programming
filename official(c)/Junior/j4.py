N = int(input())
days = list(input().split())

left = [0] * N
left[0] = 1 if days[0] == 'S' else 0
for i in range(1, N):
    left[i] = left[i-1] + 1 if days[i] == 'S' else 0

right = [0] * N
right[N-1] = 1 if days[N-1] == 'S' else 0
for i in range(N-2, -1, -1):
    right[i] = right[i+1] + 1 if days[i] == 'S' else 0

ans = 0
has_p = False
for i in range(N):
    if days[i] == 'P':
        has_p = True
        left_count = left[i-1] if i > 0 else 0
        right_count = right[i+1] if i < N-1 else 0
        ans = max(ans, left_count + 1 + right_count)

if not has_p:
    ans = N - 1

print(ans)