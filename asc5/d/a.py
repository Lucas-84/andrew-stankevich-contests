import sys
sys.stdin = open('digit.in', 'r')
sys.stdout = open('digit.out', 'w')
n = int(input())
s = bin(n)[2:]
l = len(s)
s = s[::-1]
s += '0'
dp = [None] * (l + 1)
for i in range(l + 1):
    dp[i] = [0, 0]
dp[0][0] = 1
for i in range(l):
    for b in range(2):
        for v in range(3):
            if (b + v) % 2 == int(s[i]):
                dp[i + 1][(b + v) // 2] += dp[i][b]
print(dp[l][0])
