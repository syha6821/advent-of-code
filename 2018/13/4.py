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

def is_arrow(shape):
    return shape in ["^",">","v","<"]

def remove(graph,carts):
    c = deepcopy(graph)
    for cart in carts:
        row,col = cart.pos
        if cart.direction == "^":
            c[row][col] = "|"
        elif cart.direction == ">":
            c[row][col] = "-"
        elif cart.direction == "<":
            c[row][col] = "-"
        elif cart.direction == "v":
            c[row][col] = "|"
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
                    print(*next_cart.pos)
                    positions.remove(next_cart.pos)
                else:
                    heappush(next_heap,next_cart)
                    positions.add(next_cart.pos)
        for c in next_heap:
            if c.pos in positions:
                heappush(h,c)
        if len(h) == 1:
            return h[0].pos
