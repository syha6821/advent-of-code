from itertools import cycle
from collections import namedtuple
from copy import deepcopy
from heapq import *

Pos = namedtuple("Pos",["row","col"])
Cart = namedtuple("Cart",["pos","direction","cycle"])
EMPTY = " "

def up(pos):
    return pos._replace(row = pos.row - 1)

def down(pos):
    return pos._replace(row = pos.row + 1)

def right(pos):
    return pos._replace(col = pos.col + 1)

def left(pos):
    return pos._replace(col = pos.col - 1)

def at(pos,graph):
    if 0 <= pos.row < len(graph) and 0 <= pos.col < len(graph[0]):
        return graph[pos.row][pos.col]
    return " "

def guess(pos,graph):
    u = at(up(pos),graph) != EMPTY
    r = at(right(pos),graph) != EMPTY
    d = at(down(pos),graph) != EMPTY
    l = at(left(pos),graph) != EMPTY
    if u and r and d and l:
        return "+"
    elif (l and u) or (r and d):
        return "/"
    elif (l and d) or (r and u):
        return "\\"
    elif l and r:
        return "-"
    else:
        return "|"

def is_arrow(shape):
    return shape in ["^",">","v","<"]

def remove(graph,carts):
    c = deepcopy(graph)
    for (row,col),_,_ in carts:
        c[row][col] = guess(Pos(row,col),graph)
    return c

def print_graph(graph):
    for line in graph:
        print(*line,sep="")

def read_input(file):
    graph = []
    carts = []
    with open(file) as input:
        for row,line in enumerate(input.readlines()):
            graph.append([])
            for col,s in enumerate(line[:-1]):
                graph[row].append(s)
                if is_arrow(s):
                    carts.append(Cart(Pos(row,col),s,cycle(["L","S","R"])))
    return graph,carts

def move(cart,graph):
    if cart.direction == ">":
        p = right(cart.pos)
        if graph[p.row][p.col] == "-":
            return Cart(p,">",cart.cycle)
        elif graph[p.row][p.col] == "/":
            return Cart(p,"^",cart.cycle)
        elif graph[p.row][p.col] == "\\":
            return Cart(p,"v",cart.cycle)
        else:
            d = next(cart.cycle)
            return Cart(p,">" if d == "S" else ("v" if d == "R" else "^"),cart.cycle)

    elif cart.direction == "v":
        p = down(cart.pos)
        if graph[p.row][p.col] == "|":
            return Cart(p,"v",cart.cycle)
        elif graph[p.row][p.col] == "\\":
            return Cart(p,">",cart.cycle)
        elif graph[p.row][p.col] == "/":
            return Cart(p,"<",cart.cycle)
        else:
            d = next(cart.cycle)
            return Cart(p,"v" if d == "S" else ("<" if d == "R" else ">"),cart.cycle)

    elif cart.direction == "<":
        p = left(cart.pos)
        if graph[p.row][p.col] == "-":
            return Cart(p,"<",cart.cycle)
        elif graph[p.row][p.col] == "/":
            return Cart(p,"v",cart.cycle)
        elif graph[p.row][p.col] == "\\":
            return Cart(p,"^",cart.cycle)
        else:
            d = next(cart.cycle)
            return Cart(p,"<" if d == "S" else ("^" if d == "R" else "v"),cart.cycle)

    elif cart.direction == "^":
        p = up(cart.pos)
        if graph[p.row][p.col] == "|":
            return Cart(p,"^",cart.cycle)
        elif graph[p.row][p.col] == "/":
            return Cart(p,">",cart.cycle)
        elif graph[p.row][p.col] == "\\":
            return Cart(p,"<",cart.cycle)
        else:
            d = next(cart.cycle)
            return Cart(p,"^" if d == "S" else (">" if d == "R" else "<"),cart.cycle)

    else:
        return cart

def solve(file):
    g,carts = read_input(file)
    og = remove(g,carts)
    h = []
    for cart in carts:
        heappush(h,cart)

    positions = set(cart.pos for cart in carts)

    while True:
        next_heap = []
        while h:
            cart = heappop(h)
            if cart.pos in positions:
                positions.remove(cart.pos)
                next_cart = move(cart,og)
                if next_cart.pos in positions:
                    positions.remove(next_cart.pos)
                    print(next_cart.pos,positions)
                else:
                    print(*cart.pos,"->",*next_cart.pos)
                    heappush(next_heap,next_cart)
                    positions.add(next_cart.pos)
        h = next_heap
        print(positions)
        print(len(h),"left",*map(lambda c : (c.pos.row,c.pos.col),h))
        if len(h) == 1:
            return h
        print("------------------")
