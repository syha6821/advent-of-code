from math import lcm
from functools import reduce

def read_input(file):
    with open(file) as input:
        buses = list(input.read().strip().split('\n')[1].split(','))
        return dict(map(lambda t: (t[0],int(t[1])),filter(lambda t: t[1] != 'x',zip(range(len(buses)),buses))))

def find_t(t,period,num,offset):
    if (t+offset) % num == 0:
        return t,lcm(period,num)
    else:
        return find_t(t+period,period,num,offset)

def solve(file):
    buses = read_input(file)
    return reduce(lambda acc,bus: find_t(acc[0],acc[1],bus[1],bus[0]),buses.items(),(0,1))[0]
