def split_by_bar(pattern):
    result = [[]]
    level = 0
    for p in pattern:
        if p == ")":
            level -= 1
        elif p == "(":
            level += 1

        if p == "|" and level == 0:
            result.append([])
        else:
            result[-1].append(p)
    return list(map(lambda l : "".join(l),result))

def split_by_parens(pattern):
    result = [[]]
    level = 0
    for p in pattern:
        if p == ")":
            level -= 1
        elif p == "(":
            level += 1

        if p == ")" and level == 0:
            result.append([])
        elif p == "(" and level == 1:
            result.append([])
        else:
            result[-1].append(p)

    return list(map(lambda l : "".join(l),result))

def read_input(file):
    with open(file) as input:
        return input.readline().strip()[1:-1]

def index_of(s,item):
    for i,c in enumerate(s):
        if c == item:
            return i
    return -1

def max_door(regex):
    if not regex:
        return 0
    elif regex[-1] == "|":
        return 0
    else:
        bars = split_by_bar(regex)
        if len(bars) > 1:
            return max([max_door(pattern) for pattern in bars])
        else:
            parens = split_by_parens(regex)
            if len(parens) == 1:
                return len(parens[0])
            else:
                return sum([max_door(pattern) for pattern in split_by_parens(regex)])



def solve(file):
    pattern = read_input(file)
    return max_door(pattern)
