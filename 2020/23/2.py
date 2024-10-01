from itertools import chain
import sys
sys.setrecursionlimit(10**9)

MIL = 1000000

def crab(num):
    num = list(map(int,str(num)))
    return list(chain(num,range(len(num) + 1,MIL + 1)))

def link(nums):
    l = dict()
    for i in range(len(nums) - 1):
        l[nums[i]] = nums[i + 1]
    l[nums[-1]] = nums[0]
    return l

def pick(cnt,current,cups):
    def aux(cnt,current):
        if cnt == 0:
            return []
        else:
            next = cups[current]
            return [next] + aux(cnt-1,next)
    return aux(cnt,current)

def dest(current,picks,cups):
    if current - 1 < 1:
        return dest(MIL + 1,picks,cups)
    else:
        if current - 1 in picks:
            return dest(current - 1,picks,cups)
        else:
            return current - 1

def crab_move(num,round):
    cups = link(crab(num))
    def aux(current,round):
        if round == 0:
            return cups
        else:
            picks = pick(3,current,cups)
            destination = dest(current,picks,cups)
            cups[current] = cups[picks[-1]]
            cups[picks[-1]] = cups[destination]
            cups[destination] = picks[0]
            return aux(cups[current],round-1)
    return aux(int(str(num)[0]),round)

def solve(num):
    cups = crab_move(num,10*MIL)
    return cups[1] * cups[cups[1]]
