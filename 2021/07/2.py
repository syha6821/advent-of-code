from collections import defaultdict

def read_crabs(filepath):
    with open(filepath) as input:
        crabs = defaultdict(int)
        for crab in map(int,input.read().strip().split(',')):
            crabs[crab] += 1
        return crabs

def calc_fuel(start,dest):
    dist = abs(start-dest)
    return int((1 + dist) * dist / 2)

def align(at,crabs):
    fuel = 0
    for location,count in crabs.items():
        fuel += calc_fuel(location,at) * count
    return fuel

def min_cost_align(crabs):
    return min(align(at,crabs) for at in range(min(crabs.keys()),max(crabs.keys())+1))

def solve(filepath):
    return min_cost_align(read_crabs(filepath))
