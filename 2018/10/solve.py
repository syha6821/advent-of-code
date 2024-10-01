from collections import namedtuple
import re

Pos = namedtuple("Pos",["row","col"])
Vel = namedtuple("Vel",["row","col"])
Point = namedtuple("Point",["pos","vel"])

pattern = r'<([^>]*)>'

def parse_line(line):
    p,v = re.findall(pattern,line)
    return Point(Pos(*map(int,reversed(p.split(',')))),Vel(*map(int,reversed(v.split(',')))))

def read_input(file):
    with open(file) as input:
        return list(map(parse_line,input.readlines()))

def print_points(points):
    min_row = min(point.pos.row for point in points)
    min_col = min(point.pos.col for point in points)
    max_row = max(point.pos.row for point in points)
    max_col = max(point.pos.col for point in points)

    if max_row - min_row > 100:
        return False

    width = max_col - min_col + 1
    height = max_row - min_row + 1

    graph = [["."] * width for _ in range(height)]

    for (row,col),_ in points:
        graph[row - min_row][col - min_col] = "#"

    for line in graph:
        print(*line,sep="")

    return True

def move(before):
    return [Point(Pos(row + vel.row, col + vel.col),vel) for (row,col),vel in before]

def solve(file):
    points = read_input(file)
    sec = 0
    while True:
        res = print_points(points)
        if res:
            print(sec)
            input()
        sec += 1
        points = move(points)
