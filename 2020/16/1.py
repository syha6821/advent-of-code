from collections import namedtuple
from functools import reduce

Range = namedtuple("Range",["start","stop"])

def read_rules(lines):
    rules = dict()
    for line in lines:
        field,ranges = line.split(':')
        ranges = list(map(lambda r:list(map(int,r.strip().split('-'))),ranges.split("or")))
        rules[field] = list(map(lambda r: Range(r[0],r[1]+1),ranges))
    return rules

def read_ticket(line):
    return list(map(int,line.split(',')))

def read_input(file):
    with open(file) as input:
        rules,my,nearby = list(map(lambda lines : lines.split('\n'),input.read().strip().split("\n\n")))
        return read_rules(rules),read_ticket(my[1]),list(map(read_ticket,nearby[1:]))

def is_in_range(num,rng):
    return rng.start <= num and num < rng.stop

def is_valid(num,rules):
    for ranges in rules.values():
        for rng in ranges:
            if is_in_range(num,rng):
                return True
    return False

def find_error(ticket,rules):
    return list(filter(lambda num : not is_valid(num,rules),ticket))

def solve(file):
    rules,my,nearby = read_input(file)
    return sum(reduce(lambda acc ,ticket: acc + find_error(ticket,rules),nearby,[]))
