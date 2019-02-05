def solve(c, n1, n5, n10, used):
    if c <= 0:
        return used
    if n10 > 0:
        return solve(c-1, n1+2, n5, n10-1, used+1)
    elif n5 >= 2 and  n5*2 >= c-1 :
        return solve(c-1, n1+2, n5-2, n10, used+2)
    elif n5 > 0:
        return solve(c-1, n1-3, n5-1, n10, used+4)
    else:
        return solve(c-1, n1-8, n5, n10, used+8)

        

cases = input()

for case in range(int(cases)):
    line = list(map(int, input().strip().split()))
    C = line[0]
    n1 = line[1]
    n5 = line[2]
    n10 = line[3]

    print(solve(C, n1, n5, n10, 0))
