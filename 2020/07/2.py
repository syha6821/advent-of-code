def parse(line):
    line = line.replace("contain","")
    line = line.replace("bags","")
    line = line.replace("bag","")
    line = line.replace("no other","")
    line = line.replace(".","")
    line = line.split("  ")
    line = list(filter(lambda s : s,line))
    line = list(map(lambda s : s.strip(),line))
    if len(line) == 1:
        return line[0],{}
    parsed = dict()
    for info in line[1].split(","):
        i = info.strip().split()
        parsed[i[1] + " " + i[2]] = int(i[0])
    return line[0],parsed

def read_input(file):
    with open(file) as input:
        return dict(parse(line.strip()) for line in input.readlines())

def contains(bag,rules):
    if not rules[bag]:
        return 1
    else:
        return sum(cnt * contains(b,rules) for (b,cnt) in rules[bag].items())

def solve(file):
    rules = read_input(file)
    return contains("shiny gold",rules)
