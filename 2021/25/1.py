from collections import namedtuple,defaultdict

Pos = namedtuple("Pos",["row","col"])
Sea = namedtuple("Sea",["map","width","height"])

UNIT_POS = {"U":Pos(-1,0),"R":Pos(0,1),"D":Pos(1,0),"L":Pos(0,-1)}
EMPTY = "."
EAST = ">"
SOUTH = "v"

def read_input(filepath):
    sea = defaultdict(lambda:EMPTY)
    with open(filepath) as input:
        for row,line in enumerate(input.read().strip().split('\n')):
            for col,face in enumerate(line):
                if face != EMPTY:
                    sea[Pos(row,col)] = face
    return Sea(sea,max(sea,key = lambda p:p.col).col + 1,max(sea,key = lambda p:p.row).row +1)

def print_sea(sea):
    for row in range(sea.height):
        for col in range(sea.width):
            if Pos(row,col) in sea.map:
                print(sea.map[Pos(row,col)],end="")
            else:
                print(".",end="")
        print()

def facing(sea,pos):
    if sea.map[pos] == EAST:
        return Pos(pos.row,(pos.col+1) % sea.width)
    if sea.map[pos] == SOUTH:
        return Pos((pos.row+1) % sea.height,pos.col)

def move(sea):
    easts = list(pos for pos,face in sea.map.items() if face == EAST and facing(sea,pos) not in sea.map)
    for pos in easts:
        sea.map[facing(sea,pos)] = ">"
        del sea.map[pos]

    souths = list(pos for pos,face in sea.map.items() if face == SOUTH and facing(sea,pos) not in sea.map)
    for pos in souths:
        sea.map[facing(sea,pos)] = "v"
        del sea.map[pos]
    return len(easts) + len(souths)

def solve(filepath):
    sea = read_input(filepath)
    moved = -1
    step = 0
    while moved != 0:
        moved = move(sea)
        step += 1
    return step

