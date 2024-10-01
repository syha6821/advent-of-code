from itertools import takewhile
from operator import add,mul

def order(op):
    if op == "*":
        return 0
    if op == "+":
        return 1
    if op == "(" or op == ")":
        return 2
    return -1

def infix_to_postfix(infix):
    infix = infix.replace(" ","")
    infix = list(map(lambda e: int(e) if e.isdigit() else e,list(infix)))
    def aux(infix,stack):
        if not infix:
            return list(reversed(stack))
        elif type(infix[0]) == int:
            return [infix[0]] + aux(infix[1:],stack)
        else:
            op = infix[0]
            if not stack:
                return aux(infix[1:],stack + [op])
            if op == "(":
                return aux(infix[1:], stack + ["("])
            elif op == ")":
                popped = list(takewhile(lambda s : s != "(",reversed(stack)))
                return popped + aux(infix[1:], stack[:len(stack)-(len(popped) + 1)])
            elif order(op) >= order(stack[-1]):
                return aux(infix[1:],stack+[op])
            else:
                popped = list(takewhile(lambda s : s != "(",reversed(stack)))
                return popped + aux(infix[1:],stack[:len(stack)-len(popped)] + [op])
    return aux(infix,[])

def calc_postfix(expr):
    def aux(expr,nums):
        if not expr:
            return nums
        if type(expr[0]) == int:
            return aux(expr[1:],nums + [expr[0]])
        else:
            op = add if expr[0] == "+" else mul
            return aux(expr[1:],nums[:len(nums)-2] + [op(nums[-1],nums[-2])])
    return aux(expr,[])[0]

def read_input(file):
    with open(file) as input:
        return input.read().strip().split('\n')

def solve(file):
    return sum(map(lambda l : calc_postfix(infix_to_postfix(l)),read_input(file)))
