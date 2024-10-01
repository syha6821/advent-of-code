from collections import namedtuple,Counter

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(self.row+other.row,self.col+other.col)

CROSS = [Pos(-1,0),Pos(0,1),Pos(1,0),Pos(0,-1)]
DIAGONAL = [Pos(-1,1),Pos(1,1),Pos(1,-1),Pos(-1,-1)]
ADJACENTS = CROSS+DIAGONAL
EMPTY = "L"
OCCUP = "#"
FLOOR = "."

def adjacents(pos):
    return [pos + p for p in ADJACENTS]

def read_seats(file):
    seats = dict()
    with open(file) as input:
        for row,line in enumerate(input.read().strip().split("\n")):
            for col,elm in enumerate(line):
                if not elm == FLOOR:
                    seats[(Pos(row,col))] = elm
    return seats

def stablize(seats):
    new_seats = dict()
    changes = 0
    for pos,seat in seats.items():
        adjs = list(filter(lambda p : p in seats,adjacents(pos)))
        if seat == EMPTY and all(map(lambda p : seats[p] != OCCUP,adjs)):
            new_seats[pos] =  OCCUP
            changes += 1
        elif seat == OCCUP and len(list(filter(lambda p : seats[p] == OCCUP,adjs))) >= 4:
            new_seats[pos] =  EMPTY
            changes += 1
        else:
            new_seats[pos] = seat
    return new_seats if changes == 0 else stablize(new_seats)

def solve(file):
    return Counter(stablize(read_seats(file)).values())[OCCUP]
