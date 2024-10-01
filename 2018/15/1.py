from collections import deque

GOBLIN = "G"
ELF = "E"
EMPTY = "."
WALL = "#"

dx = [0,0,1,-1]
dy = [1,-1,0,0]

class Unit():
    def __init__(self,type,row,col):
        self.type = type
        self.row = row
        self.col = col
        self.hp = 200
        self.power = 3
        self.enemy = ELF if type == GOBLIN else GOBLIN

    def target(self,area):
        for i in range(4):
            row = self.row + dx[i]
            col = self.col + dy[i]
            tile = area[row][col]
            if type(tile) == Unit and tile.type == self.enemy:
                return None

        q = deque([(self.row,self.col)])
        reach = []
        visited = set([self.row,self.col])

        while not reach and q:
            for _ in range(len(q)):
                row,col = q.popleft()
                for i in range(4):
                    r = row + dx[i]
                    c = col + dy[i]
                    if (r,c) not in visited:
                        tile = area[r][c]

                        if tile == EMPTY:
                            q.append((r,c))
                            visited.add((r,c))
                        elif type(tile) == Unit and tile.type == self.enemy:
                            reach.append((row,col))

        return sorted(reach)[0] if reach else None

    def move(self,area):
        t = self.target(area)
        if t:
            reach = []
            q = deque([t])
            visited = set([t])
            while not reach and q:
                for _ in range(len(q)):
                    row,col = q.popleft()
                    for i in range(4):
                        r = row + dx[i]
                        c = col + dy[i]
                        if (r,c) not in visited:
                            tile = area[r][c]

                            if (r,c) == (self.row,self.col):
                                reach.append((row,col))
                            elif tile == EMPTY:
                                q.append((r,c))
                                visited.add((r,c))
            
            row,col = sorted(reach)[0]
            area[self.row][self.col] = EMPTY
            self.row = row
            self.col = col
            area[self.row][self.col] = self

    def attack(self,area):
        enemies = []
        for i in range(4):
            r = self.row + dx[i]
            c = self.col + dy[i]
            tile = area[r][c]
            if type(tile) == Unit and self.enemy == tile.type:
                enemies.append(tile)
        if enemies:
            target = sorted(enemies,key = lambda e : (e.hp,e.row,e.col))[0]
            target.hp -= self.power
            if target.hp <= 0:
                area[target.row][target.col] = EMPTY
                return target
        return None

def read_input(file):
    area = []
    goblins = []
    elves = []
    with open(file) as input:
        for row,line in enumerate(input.readlines()):
            area.append([])
            for col,tile in enumerate(line.strip()):
                if tile in [EMPTY,WALL]:
                    area[row].append(tile)
                else:
                    unit = Unit(tile,row,col)
                    area[row].append(unit)
                    if tile == ELF:
                        elves.append(unit)
                    elif tile == GOBLIN:
                        goblins.append(unit)
    return area,goblins,elves

def print_area(area):
    for line in area:
        print(*[tile if tile in [EMPTY,WALL] else tile.type for tile in line],sep="",end=" ")
        print(*[unit.type + "(" + str(unit.hp) + ")" for unit in line if type(unit) == Unit],sep=" ")

def solve(file):
    area,goblins,elves = read_input(file)
    units = sorted(goblins+elves,key = lambda u : (u.row,u.col))
    goblins = len(goblins)
    elves = len(elves)
    cnt = 0
    while goblins > 0 and elves > 0:
        next_units = []
        finished = False
        for unit in units:
            if not(goblins > 0 and elves > 0):
                finished = True
                next_units.append(unit)
                continue
            if area[unit.row][unit.col] == unit:
                unit.move(area)
                dead = unit.attack(area)
                next_units.append(unit)
                if dead:
                    if dead.type == GOBLIN:
                        goblins -= 1
                    elif dead.type == ELF:
                        elves -= 1
        units = sorted([unit for unit in next_units if area[unit.row][unit.col] != EMPTY and unit.hp > 0],key = lambda u : (u.row,u.col))
        if finished:
            break
        cnt += 1

    # return cnt * sum(unit.hp for unit in units)
    return cnt*sum(unit.hp for unit in units)
