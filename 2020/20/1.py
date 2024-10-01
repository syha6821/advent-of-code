from collections import namedtuple,defaultdict
from functools import reduce
from math import prod

Tile = namedtuple("Tile",["num","tile","edges"])

def read_tile(lines):
    num = int(lines[0][5:][:-1])
    top = lines[1]
    left = "".join(list(map(lambda l : l[0],lines[1:])))
    right = "".join(list(map(lambda l : l[-1],lines[1:])))
    bottom = lines[-1]
    return Tile(num,lines[1:],[top,right,bottom,left])

def read_input(file):
    with open(file) as input:
        tiles = list(map(lambda lines : lines.split('\n'),input.read().strip().split("\n\n")))
        return list(map(read_tile,tiles))

def is_matched(e1,e2):
    return e1 == e2 or e1 == e2[::-1]

def all_edges(tiles):
    return reduce(lambda acc, tile : acc + tile.edges ,tiles,[])

def is_outermost(edge,edges):
    return len(list(filter(lambda e : is_matched(e,edge),edges))) == 1

def is_corner(tile,edges):
    return len(list(edge for edge in tile.edges if is_outermost(edge,edges))) == 2

def solve(file):
    tiles = read_input(file)
    edges = all_edges(tiles)
    return prod(map(lambda tile : tile.num, filter(lambda tile : is_corner(tile,edges),tiles)))

# def test(file):
#     tiles = read_input(file)
#     res = defaultdict(int)
#     for tile in tiles:
#         for t in tiles:
#             if tile.num == t.num:
#                 continue
#             for edge in tile.edges:
#                 for e in t.edges:
#                     if is_matched(edge,e):
#                         res[edge+str(tile.num)] += 1
#     return res.values()
