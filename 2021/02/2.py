from collections import namedtuple

Command = namedtuple("Command",["direction","unit"])

def read_commands(filename):
    with open(filename) as input:
        for line in input:
            direction, unit = line.strip().split()
            yield Command(direction,int(unit))

def solve(filename):
    commands = read_commands(filename)
    horizontal = 0
    depth = 0
    aim = 0
    for command in commands:
        if command.direction == "forward":
            horizontal += command.unit
            depth += aim * command.unit
        else:
            if command.direction == "down":
                aim += command.unit
            if command.direction == "up":
                aim -= command.unit
    return horizontal * depth
