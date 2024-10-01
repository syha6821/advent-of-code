from collections import namedtuple
from itertools import accumulate
from math import inf

Pos = namedtuple("Pos",["row","col"])

def powerlevel(pos,sn):
    id = pos.col + 10
    pl = id
    pl *= pos.row
    pl += sn
    pl *= id
    pl = (pl // 100) % 10
    pl -= 5
    return pl

def largest_square(cells,accs,L):
    C = len(cells)
    squares = [[0] * (C - L + 1) for _ in range(C - L + 1)]
    for i in range(len(squares)):
        for r in range(L):
            squares[0][i] += accs[r][i+L] - accs[r][i]

    for row in range(1,len(squares)):
        for i in range(len(squares)):
            squares[row][i] = squares[row-1][i] - (accs[row-1][i+L] - accs[row-1][i]) + (accs[row+L-1][i+L] - accs[row+L-1][i])

    power = squares[0][0]
    pos = Pos(0,0)

    for row in range(len(squares)):
        for col in range(len(squares)):
            if squares[row][col] > power:
                power = squares[row][col]
                pos = Pos(row,col)

    return pos,power

def solve(SN):
    L = 300
    cells = [[0] * L for _ in range(L)]
    for row in range(L):
        for col in range(L):
            cells[row][col] = powerlevel(Pos(row+1,col+1),SN)
    accs = [list(accumulate(line,initial=0)) for line in cells]

    x = 0
    y = 0
    power = -inf
    size = 0

    for s in range(1,L+1):
        (row,col),p = largest_square(cells,accs,s)
        if p > power:
            size = s
            power = p
            x = col
            y = row

    return x+1,y+1,size
