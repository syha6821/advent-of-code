from collections import namedtuple,defaultdict

Instruction = namedtuple("Instruction",["state","ranges"])
Ranges = namedtuple("Ranges",["x","y","z"])
Range = namedtuple("Range",["start","stop"])

MAX_RANGE = 50
MIN_RANGE = -50

def limit_range(range):
    if range.stop > MAX_RANGE + 1:
        return limit_range(Range(range.start,MAX_RANGE+1))
    if range.start < MIN_RANGE:
        return limit_range(Range(MIN_RANGE,range.stop))
    if range.stop < MIN_RANGE or range.start > MAX_RANGE + 1:
        return Range(0,0)
    return range

def limit_ranges(ranges):
    return Ranges(*map(limit_range,ranges))


def read_ranges(line):
    to_range = lambda min,max : (min,max+1)
    return Ranges(*(map(lambda l: Range(*to_range(*(map(int,l[2:].split(".."))))),line.strip().split(","))))

def read_input(filepath):
    with open(filepath) as input:
        for line in input.read().strip().split('\n'):
            state,ranges = line.strip().split()
            yield Instruction(state,read_ranges(ranges))

def do_step(instruction,cubes):
    for x in range(instruction.ranges.x.start,instruction.ranges.x.stop):
        for y in range(instruction.ranges.y.start,instruction.ranges.y.stop):
            for z in range(instruction.ranges.z.start,instruction.ranges.z.stop):
                if instruction.state == "on":
                    cubes.add((x,y,z))
                else:
                    cubes.discard((x,y,z))

def solve(filepath):
    cubes = set()
    for instruction in read_input(filepath):
        instruction = instruction._replace(ranges = limit_ranges(instruction.ranges))
        do_step(instruction,cubes)
    return len(cubes)
