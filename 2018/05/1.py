from collections import deque

def poly_match(a,b):
    return (a.lower() == b.lower()) and (a != b)

def react(polymer):
    polymer = deque(polymer)
    stack = []
    while polymer:
        if stack:
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
        return len(react(poly))
