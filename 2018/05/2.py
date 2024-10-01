from collections import deque
from math import inf

def poly_match(a,b):
    return (a.lower() == b.lower()) and (a != b)

def react(polymer,ignore):
    polymer = deque(polymer)
    stack = []
    while polymer:
        if polymer[0].lower() == ignore:
            polymer.popleft()
        elif stack:
            if poly_match(stack[-1],polymer[0]):
                stack.pop()
            else:
                stack.append(polymer[0])
            polymer.popleft()
        else:
            stack.append(polymer.popleft())
    return stack

def solve(file):
    with open(file) as f:
        poly = f.readline().strip()
        ans = inf
        for i in range(ord('a'),ord('z')+1):
            ans = min(ans,len(react(poly,chr(i))))
        return ans
