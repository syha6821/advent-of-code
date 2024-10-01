from math import ceil,floor
from itertools import permutations
from copy import deepcopy

def read_pairs(filepath):
    with open(filepath) as input:
        for line in input.read().strip().split('\n'):
            yield eval(line.strip())

def add(a,b):
    # print("after addition:",[a,b])
    return red([a,b])

def red(l):
    def red_explode(ll,parents):
        for i in range(0,len(ll)):
            val = ll[i]
            if type(val) == list:
                if len(parents) >= 3:
                    explode(i,parents+[ll])
                    red_explode(l,[])
                else:
                    red_explode(val,parents+[ll])
    def red_split(ll,parents):
        for i in range(0,len(ll)):
            val = ll[i]
            if type(val) == list:
                red_split(val,parents+[ll])
            if type(val) == int and val >= 10:
                split(i,parents+[ll])
                red_split(l,[])
                break
    red_explode(l,[])
    red_split(l,[])
    return l
    # print("=", l)

def explode_expand(val,direction,index,parents):
    if direction == "left":
        if index == -1:
            if len(parents) == 1:
                return False,index
            outer_index = 0 if parents[-1] == parents[-2][0] else 1
            return explode_expand(val,"left",outer_index-1,parents[:-1])
        else:
            if type(parents[-1][index]) == int:
                parents[-1][index] += val
                return parents,index
            else:
                return explode_expand(val,"left",1,parents+[parents[-1][index]])
    else:
        if index == 2:
            if len(parents) == 1:
                return False,index
            outer_index = 0 if parents[-1] == parents[-2][0] else 1
            return explode_expand(val,"right",outer_index+1,parents[:-1])
        else:
            if type(parents[-1][index]) == int:
                parents[-1][index] += val
                return parents,index
            else:
                return explode_expand(val,"right",0,parents+[parents[-1][index]])

def explode(index,parents):
    left,right = parents[-1][index]
    parents[-1][index] = 0
    explode_expand(left,"left",index-1,parents)
    explode_expand(right,"right",index+1,parents)
    # print("after explode:",parents[0])

def split(index,parents):
    val = parents[-1][index]
    parents[-1][index] = [floor(val/2),ceil(val/2)]
    # print("after split:",parents[0])
    if len(parents) >= 4:
        explode(index,parents)

def magnitude(l):
    if type(l) == int:
        return l
    else:
        return 3*magnitude(l[0]) + 2*magnitude(l[1])

def solve(filepath):
    pairs = read_pairs(filepath)
    return max(magnitude(add(deepcopy(a),deepcopy(b))) for a,b in permutations(pairs,2))
