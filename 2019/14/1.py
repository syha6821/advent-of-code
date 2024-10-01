from collections import defaultdict
import sys
sys.setrecursionlimit(10**9)

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

def calc_require(name,cnt,reactions):
    resources = defaultdict(int)
    def aux(name,cnt):
        if name == "ORE":
            return cnt
        if resources[name] >= cnt:
            resources[name] -= cnt
            return 0
        unit,ingredients = reactions[name].values()
        ore = 0
        for ingredient,need in ingredients.items():
            need -= resources[ingredient]
            resources[ingredient] = 0
            ore += aux(ingredient,need)
        if cnt > unit:
            ore += aux(name,cnt - unit)
        else:
            resources[name] = unit - cnt
        return ore
    return aux(name,cnt)

def solve(file):
    return calc_require("FUEL",1,read_input(file))
