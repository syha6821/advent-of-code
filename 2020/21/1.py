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
    non_allergens = defaultdict(set)
    for ingredients,allergens in foods:
        for allergen in allergens:
            if allergen not in non_allergens:
                non_allergens[allergen] |= ingredients
            else:
                non_allergens[allergen] &= ingredients
    return non_allergens

def find_non_allergens(foods):
    all_ingredients = reduce(lambda acc,food : acc.union(food.ingredients),foods,set())
    allergens = reduce(lambda acc,allergens : acc.union(allergens) ,find_allergens(foods).values(),set())
    return all_ingredients - allergens

def solve(file):
    foods = read_input(file)
    ingredients = Counter(reduce(lambda acc,food : acc + list(food.ingredients),foods,list()))
    return reduce(lambda acc,non_allergen: acc + ingredients[non_allergen] ,find_non_allergens(foods),0)
