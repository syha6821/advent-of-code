from collections import defaultdict
TRILLION = 1000000000000

def read_ingredient(line):
    cnt, name = line.split()
    return name,int(cnt)

def read_reaction(line):
    ingredients ,result = line.split("=>")
    return read_ingredient(result.strip()),list(map(lambda l : read_ingredient(l.strip()),ingredients.split(',')))

def read_input(file):
    reactions = dict()
    with open(file) as input:
        for line in input.read().strip().split('\n'):
            result, ingredients = read_reaction(line)
            reactions[result[0]] = {"unit":result[1],"ingredients":dict(ingredients)}
    return reactions

def calc_ore(name,req,reactions):
    resources = defaultdict(int)
    def aux(name,req):
        if name == "ORE":
            return req
        if resources[name] >= req:
            resources[name] -= req
            return 0
        unit,ingredients = reactions[name].values()
        ore = 0

        neccesary = req // unit + (0 if req % unit == 0 else 1)
        surplus = neccesary * unit - req

        for ingredient,need in ingredients.items():
            need *= neccesary
            need -= resources[ingredient]
            del resources[ingredient]
            ore += aux(ingredient,need)

        resources[name] += surplus
        return ore
    return aux(name,req)

def product(max_ore,reactions):
    one_fuel = calc_ore("FUEL",1,reactions)
    def aux(min_,max_):
        if max_ - min_ == 1:
            return min_
        mid = (min_ + max_)//2
        req_ore = calc_ore("FUEL",mid,reactions)
        if req_ore == max_ore:
            return mid
        if req_ore < max_ore:
            return aux(mid,max_)
        if req_ore > max_ore:
            return aux(min_,mid)
    return aux(max_ore//one_fuel,max_ore)

def solve(file):
    reactions = read_input(file)
    return product(TRILLION,reactions)
