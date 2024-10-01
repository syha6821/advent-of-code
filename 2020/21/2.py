from collections import namedtuple,defaultdict,Counter
from functools import reduce

Food = namedtuple("Food",["ingredients","allergens"])

def read_food(line):
    ingredients,allergens = line.split('(contains ')
    ingredients = ingredients.strip().split()
    allergens = list(map(lambda a: a.strip(),allergens[:-1].split(',')))
    return Food(set(ingredients),allergens)

def read_input(file):
    with open(file) as input:
        return [read_food(line) for line in input.read().strip().split('\n')]

def find_allergens(foods):
    allergens = defaultdict(set)
    for ingredients,alrgs in foods:
        for alg in alrgs:
            if alg not in allergens:
                allergens[alg] |= ingredients
            else:
                allergens[alg] &= ingredients

    result = dict()
    while allergens:
        alrg_removes = list()
        ingr_removes = set()
        for allergen,ingredients in allergens.items():
            if len(ingredients) == 1:
                ingr = next(iter(ingredients))
                alrg_removes.append(allergen)
                ingr_removes.add(ingr)
                result[allergen] = ingr
        for allergen in alrg_removes:
            allergens.pop(allergen)
        for ingrs in allergens.values():
            ingrs -= ingr_removes
    return result

def solve(file):
    allergens = find_allergens(read_input(file))
    return reduce(lambda acc,ingr: acc + "," + ingr ,list(map(lambda t : t[1],sorted(allergens.items()))),"")[1:]
