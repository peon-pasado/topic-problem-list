
def euclid(a, b):
    if b == 0:
        return 1, 0, a 
    y, x, d = euclid(b, a % b)
    y -= a // b * x
    return x, y, d

t = int(input())
for i in range(t):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    g = [0] * n 
    ans = [0] * n 
    g[0] = a[0]
    for i in range(1, n):
        x, y, d = euclid(g[i-1], a[i])
        g[i] = d
    
    if k % g[n-1] == 0:
        print("YES")
        mt = k // g[n-1]
        for i in range(n-2, -1, -1):
            xg, yg, d = euclid(a[i+1], g[i]);
            ans[i+1] = xg * mt                
            mt *= yg
        ans[0] = mt
        for i in range(n): 
            print(ans[i], end=" \n"[i+1==n])
    else:
        print("NO")

