from math import prod

def read_input(file):
    with open(file) as input:
        depart, buses = input.read().strip().split('\n')
        return int(depart),list(map(int,filter(lambda b : b != 'x',buses.split(','))))

def earliest_bus_time_from(time,buses):
    return min(map(lambda b : (b,b - (time % b)),buses),key = lambda t : t[1])

def solve(file):
    return prod(earliest_bus_time_from(*read_input(file)))
