from itertools import permutations

PATTERNS = {
    "abcefg",
    "cf",
    "acdeg",
    "acdfg",
    "bcdf",
    "abdfg",
    "abdefg",
    "acf",
    "abcdefg",
    "abcdfg",
}

CODE = {
    "abcefg":0,
    "cf":1,
    "acdeg":2,
    "acdfg":3,
    "bcdf":4,
    "abdfg":5,
    "abdefg":6,
    "acf":7,
    "abcdefg":8,
    "abcdfg":9,
}

A_TO_G = "abcdefg"

def read_input(filepath):
    with open(filepath) as input:
        for line in input:
            yield map(lambda l: l.strip().split(),line.strip().split('|'))

def decode(ref,pattern):
    return ''.join(sorted(map(lambda seg: ref[seg],pattern)))

def find_code(patterns):
    for perm in permutations("abcdefg"):
        ref = dict(zip(perm,A_TO_G))
        if all(decode(ref,pattern) in PATTERNS for pattern in patterns):
            return ref

def solve(filepath):
    ans = 0
    for patterns,problems in read_input(filepath):
        ref = find_code(patterns)
        ans += int(''.join(map(lambda prob : str(CODE[decode(ref,prob)]),problems)))
    return ans
