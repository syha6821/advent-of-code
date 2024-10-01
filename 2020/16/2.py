from collections import namedtuple
from math import prod

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

def is_valid_for_field(num,field,rules):
    for rng in rules[field]:
        if is_in_range(num,rng):
            return True
    return False

def is_valid_ticket(ticket,rules):
    return all(map(lambda num: any(is_valid_for_field(num,field,rules) for field in rules),ticket))

def valid_tickets(tickets,rules):
    return list(filter(lambda ticket: is_valid_ticket(ticket,rules),tickets))

def find_field(tickets,rules):
    tickets = valid_tickets(tickets,rules)
    matched = {i:list(rules.keys()) for i in range(len(tickets[0]))}
    while any(map(lambda field: len(field) != 1,matched.values())):
        for i,fields in matched.items():
            fields = [field for field in fields if all(is_valid_for_field(ticket[i],field,rules) for ticket in tickets)]
            matched[i] = fields

            if len(fields) == 1:
                for j in matched:
                    if i == j:
                        continue
                    if fields[0] in matched[j]:
                        matched[j].remove(fields[0])
    return {i:fields[0] for i,fields in matched.items()}

def solve(file):
    rules,my,nearby = read_input(file)
    matched = find_field(nearby,rules)
    return prod([my[i] for i,field in matched.items() if field.startswith("departure")])
