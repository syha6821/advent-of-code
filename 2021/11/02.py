from collections import namedtuple

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(self.row+other.row,self.col+other.col)
UNIT_POS = {"N":Pos(-1,0),
            "NE":Pos(-1,1),
            "E":Pos(0,1),
            "SE":Pos(1,1),
            "S":Pos(1,0),
            "SW":Pos(1,-1),
            "W":Pos(0,-1),
            "NW":Pos(-1,-1)}

def read_octopuses(filepath):
    octopuses = dict()
    with open(filepath) as input:
        for row,line in enumerate(input):
            for col,val in enumerate(line.strip()):
                octopuses[Pos(row,col)] = int(val)
    return octopuses

def adjacents(pos,m):
    return filter(lambda p: p in m,(pos+unit for unit in UNIT_POS.values()))

def flash(octopuses):
    inits = list(pos for pos,val in octopuses.items() if val > 9)
    exhausted = set()
    def f(flashes):
        if not flashes:
            return 0
        else:
            exhausted.update(flashes)
            for pos in flashes:
                octopuses[pos] = 0
                for adj in adjacents(pos,octopuses):
                    if adj not in exhausted:
                        octopuses[adj] += 1
            return len(flashes) + f(list(pos for pos,val in octopuses.items() if val > 9))
    return f(inits)

def solve(filepath):
    flashed = 0
    count = 0
    octopuses = read_octopuses(filepath)
    while not flashed == len(octopuses):
        octopuses.update((pos, val+1) for pos,val in octopuses.items())
        flashed = flash(octopuses)
        count += 1
    return count
