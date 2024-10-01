from collections import namedtuple,defaultdict,Counter
from functools import reduce
from operator import add,sub

Instruction = namedtuple("Instruction",["state","cube"])
Cube = namedtuple("Cube",["x","y","z"])
Range = namedtuple("Range",["start","stop"])
EMPTY_RANGE = Range(0,0)
EMPTY_CUBE = Cube(EMPTY_RANGE,EMPTY_RANGE,EMPTY_RANGE)

def read_cube(line):
    to_range = lambda min,max : (min,max+1)
    return Cube(*(map(lambda l: Range(*to_range(*(map(int,l[2:].split(".."))))),line.strip().split(","))))

def read_input(filepath):
    with open(filepath) as input:
        for line in input.read().strip().split('\n'):
            state,ranges = line.strip().split()
            yield Instruction(state,read_cube(ranges))

def is_valid_range(range):
    return range.start < range.stop

def range_intersection(r1,r2):
    intersection = Range(max(r1.start,r2.start),min(r1.stop,r2.stop))
    return intersection if is_valid_range(intersection) else EMPTY_RANGE

def is_valid_cube(cube):
    return all(map(is_valid_range,cube))

def cube_intersection(c1,c2):
    intersection = Cube(*(range_intersection(r1,r2) for r1,r2 in zip(c1,c2)))
    return intersection if is_valid_cube(intersection) else EMPTY_CUBE

def volume(cube):
    return (cube.x.stop - cube.x.start) * (cube.y.stop - cube.y.start) * (cube.z.stop - cube.z.start)

def solve(filepath):
    cubes = Counter()
    for inst in read_input(filepath):
        update = Counter()
        for (sign,cube),count in cubes.items():
            if sign == "on":
                update[("off",cube_intersection(inst.cube,cube))] += count
            if sign == "off":
                update[("on",cube_intersection(inst.cube,cube))] += count
        cubes.update(update)
        if inst.state == "on":
            cubes[(inst.state,inst.cube)] += 1
    return reduce(lambda result,info: (add if info[0][0] == "on" else sub)(result,volume(info[0][1]) * info[1]),cubes.items(),0)
