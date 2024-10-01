def read_rules(lines):
    rules = dict()
    for line in lines:
        num,rule = line.split(':')
        if rule[1] == '"':
            rules[int(num)] = [[rule.split('"')[1]]]
        else:
            sub_rules = []
            for sub_rule in rule.strip().split('|'):
                sub_rules.append(list(int(n) for n in sub_rule.strip().split()))
            rules[int(num)] = sub_rules
    rules[8] = [[42],[42,8]]
    rules[11] = [[42,31],[42,11,31]]
    return rules

def read_input(file):
    with open(file) as input:
        rules,messages = input.read().strip().split("\n\n")
        return read_rules(rules.split('\n')),messages.split('\n')

def is_valid(message,rules):
    def aux(message,rule):
        if not message:
            return False if rule else True
        if not rule:
            return False if message else True
        if type(rule[0]) == int:
            return any(aux(message,r + rule[1:]) for r in rules[rule[0]])
        elif type(rule[0]) == str:
            if rule[0] == message[0]:
                return aux(message[1:],rule[1:])
            else:
                return False
    return aux(message,rules[0][0])

def solve(file):
    rules,messages = read_input(file)
    return len(list(filter(lambda m: is_valid(m,rules),messages)))
