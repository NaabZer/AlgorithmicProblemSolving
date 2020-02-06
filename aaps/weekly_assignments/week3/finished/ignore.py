import sys

order = [0, 1, 2, 5, 9, 8, 6]


def numberToBase(n, b):
    if n == 0:
        return [0]
    digits = []
    while n:
        digits.append(int(n % b))
        n //= b
    return digits[::-1]


for n in sys.stdin:
    n_i = int(n)
    new = numberToBase(n_i, 7)
    new.reverse()
    s = ""
    for e in new:
        s += str(order[e])
    print(s)


