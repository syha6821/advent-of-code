DIGIT_TO_SEGS = {0:frozenset({"a","b","c","e","f","g"}),
                 1:frozenset({"c","f"}),
                 2:frozenset({"a","c","d","e","g"}),
                 3:frozenset({"a","c","d","f","g"}),
                 4:frozenset({"b","c","d","f"}),
                 5:frozenset({"a","b","d","f","g"}),
                 6:frozenset({"a","b","d","e","f","g"}),
                 7:frozenset({"a","c","f"}),
                 8:frozenset({"a","b","c","d","e","f","g"}),
                 9:frozenset({"a","b","c","d","f","g"})}

SEGS_TO_DIGIT = {frozenset({"a","b","c","e","f","g"}):0,
                 frozenset({"c","f"}):1,
                 frozenset({"a","c","d","e","g"}):2,
                 frozenset({"a","c","d","f","g"}):3,
                 frozenset({"b","c","d","f"}):4,
                 frozenset({"a","b","d","f","g"}):5,
                 frozenset({"a","b","d","e","f","g"}):6,
                 frozenset({"a","c","f"}):7,
                 frozenset({"a","b","c","d","e","f","g"}):8,
                 frozenset({"a","b","c","d","f","g"}):9}

UNIQUES = {2:1,4:4,3:7,7:8}

def read_input(filepath):
    with open(filepath) as input:
        for line in input:
            yield map(lambda l: l.strip().split(),line.strip().split('|'))

def solve(filepath):
    uniques = 0
    for _, outputs in read_input(filepath):
        for output in outputs:
            if len(set(output)) in UNIQUES:
                uniques += 1
    return uniques
