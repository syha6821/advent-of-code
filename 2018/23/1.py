from collections import namedtuple

Pos = namedtuple("Pos",["x","y","z"])
Bot = namedtuple("Bot",["pos","r"])

def parse_line(line):
    pos,r = line.split(", ")
    x,y,z = map(int,pos[5:-1].split(","))
    r = int(r[2:])
    return Bot(Pos(x,y,z),r)

def read_input(file):
    with open(file) as input:
        return [parse_line(line) for line in input.readlines()]

def distance(b1,b2):
    return sum(abs(c1-c2) for c1,c2 in zip(b1.pos,b2.pos))

def solve(file):
    bots = read_input(file)
    strongest = max(bots,key = lambda bot : bot.r)
    ans = len([bot for bot in bots if distance(bot,strongest) <= strongest.r])
    return ans
