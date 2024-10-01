def line_count(file):
    with open(file) as input:
        return len(input.read().strip().split('\n'))

def read_input(file):
    orbits = dict()
    with open(file) as input:
        for line in input.read().strip().split('\n'):
            l,r = line.split(")")
            orbits[r] = l
    return orbits

def count_orbits(obj,orbits):
    if obj not in orbits:
        return 0
    else:
        return 1 + count_orbits(orbits[obj],orbits)

def solve(file):
    orbits = read_input(file)
    return sum(map(lambda o: count_orbits(o,orbits),orbits))
