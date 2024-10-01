from collections import namedtuple
from itertools import accumulate

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

def largest_square(cells):
    L = 3
    C = len(cells)
    accs = [list(accumulate(line,initial=0)) for line in cells]
    squares = [[0] * (C - L + 1) for _ in range(C - L + 1)]
    for i in range(len(squares)):
        squares[0][i] = (accs[0][i+3] - accs[0][i]) + (accs[1][i+3] - accs[1][i]) + (accs[2][i+3] - accs[2][i])

    for row in range(1,len(squares)):
        for i in range(len(squares)):
            squares[row][i] = squares[row-1][i] - (accs[row-1][i+3] - accs[row-1][i]) + (accs[row+2][i+3] - accs[row+2][i])

    power = squares[0][0]
    pos = Pos(0,0)

    for row in range(len(squares)):
        for col in range(len(squares)):
            if squares[row][col] > power:
                power = squares[row][col]
                pos = Pos(row,col)

    return pos

def solve(SN):
    L = 300
    cells = [[0] * L for _ in range(L)]
    for row in range(L):
        for col in range(L):
            cells[row][col] = powerlevel(Pos(row+1,col+1),SN)

    row,col = largest_square(cells)
    return col+1,row+1
