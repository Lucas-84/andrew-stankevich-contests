from decimal import *
import sys

#sys.stdin = open('gsm.in', 'r')
#sys.stdout = open('gsm.out', 'w')

pi = Decimal("3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038195")

def acos(x):
    tmp = Decimal(x)
    ans = pi / 2 - x
    x = x * x
    i = 1
    while True:
        last = ans
        tmp = tmp * x * (2 * i - 1) / (2 * i)
        ans -= tmp / (2 * i + 1)
        if (ans - last).copy_abs() < Decimal(1e-110):
            break
        i += 1
    return ans

getcontext().prec = 150
s3 = Decimal(3).sqrt()
for H in range(1, 51):
    for R in range(1, 51):
        #H, R = map(int, input().split(' '))
        if R > H:
            #print(1., end = "')")
            pass
        elif 4 * R * R < 3 * H * H:
            #print(2 * pi * R * R / 3 / s3 / H / H, end = "')")
            pass
        else:
            x = Decimal(R * R - 3 * H * H / 4).sqrt()
            tot_area = s3 * H * H / 8
            theta = pi / 6 - Decimal(acos(s3 * H / 2 / R))
            inter_area = theta / 2 * R * R
            inter_area += x * s3 * H / 4
            print("ans[{}][{}] = Decimal('".format(H, R), end = "")
            print(inter_area / tot_area, end = "')")
            print()
"""
pi = acos(-1)
if R > H:
    print(1.)
elif 4 * R * R < 3 * H * H:
    print(2 * pi * R * R / 3 / sqrt(3) / H / H)
else:
    x = sqrt(R * R - 3 * H * H / 4)    
    tot_area = sqrt(3) * H * H / 8
    theta = pi / 6 - acos(sqrt(3) * H / 2 / R)
    inter_area = theta / 2 / pi * pi * R * R
    inter_area += x * sqrt(3) * H / 4
    print(inter_area / tot_area)
"""
