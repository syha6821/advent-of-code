from collections import namedtuple
from pprint import pprint

Pos = namedtuple("Pos",["x","y","z"])
Bot = namedtuple("Bot",["id","pos","r"])
Inter = namedtuple("Inter",["ranges","ids"])

def parse_line(line):
    pos,r = line.split(", ")
    x,y,z = map(int,pos[5:-1].split(","))
    r = int(r[2:])
    return Pos(x,y,z),r

def read_input(file):
    with open(file) as input:
        return [Bot(id,*parse_line(line)) for id,line in enumerate(input.readlines())]

def bot_to_inter(bot):
    x,y,z = bot.pos
    r = bot.r
    return Inter([range(x-r,x+r+1),range(y-r,y+r+1),range(z-r,z+r+1)],{bot.id})

def intersection(i1,i2):
    ranges = []
    for r1,r2 in zip(i1.ranges,i2.ranges):
        r = range(max(r1.start,r2.start),min(r1.stop,r2.stop))
        if not r1.start < r2.stop:
            return None
        else:
            ranges.append(r)
    return Inter(ranges,i1.ids | i2.ids)

def solve(file):
    bots = read_input(file)
    inters = list(map(bot_to_inter,bots))
    return inters
    # while inters:
    #     pprint(inters)
    #     print()
    #     next_inters = []
    #     for i in range(len(inters)):
    #         for j in range(len(inters)):
    #             if i != j:
    #                 inter = intersection(inters[i],inters[j])
    #                 if inter:
    #                     next_inters.append(inter)
    #     inters = next_inters
    #     if not inters:
    #         print(inters)
