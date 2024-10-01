from operator import add,mul

def expr_len(l):
    if type(l) != list:
        return 1
    else:
        return 2 + sum(map(expr_len,l))

def read_expression(expr):
    expr = expr.replace(" ","")
    def aux(expr,acc):
        if not expr or expr[0] == ")":
            return acc
        else:
            if expr[0] == '+':
                return aux(expr[1:],acc+[add])
            elif expr[0] == '*':
                return aux(expr[1:],acc+[mul])
            elif expr[0].isdigit():
                return aux(expr[1:],acc+[int(expr[0])])
            elif expr[0] == "(":
                sub_expr = aux(expr[1:],[])
                return aux(expr[expr_len(sub_expr):],acc+[sub_expr])
    return aux(expr,[])

def read_input(file):
    with open(file) as input:
        return list(map(read_expression,input.read().strip().split('\n')))


def evaluate(expr):
    def aux(expr):
        if len(expr) == 1:
            if type(expr[0]) == int:
                return expr[0]
            else:
                return evaluate(expr[0])
        num = expr[0] if type(expr[0]) == int else evaluate(expr[0])
        op = expr[1]
        return op(num,aux(expr[2:]))
    return aux(list(reversed(expr)))

def solve(file):
    return sum(map(evaluate,read_input(file)))
