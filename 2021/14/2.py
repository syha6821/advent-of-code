from collections import defaultdict

def read_input(filepath):
    with open(filepath) as input:
        word, rules = input.read().strip().split("\n\n")
        template = word.strip()
        return template,dict(rule.strip().split(" -> ") for rule in rules.strip().split('\n'))

def polymerization(template,occurence,rules):
    new_pairs = defaultdict(int)
    for pair,count in template.items():
        if not count > 0:
            continue
        template[pair] -= count
        insertion = rules[pair]
        occurence[insertion] += count
        new_pairs[pair[0]+insertion] += count
        new_pairs[insertion+pair[1]] += count
    for pair,count in new_pairs.items():
        template[pair] += count
    
def solve(filepath):
    template, rules = read_input(filepath)
    occurence = defaultdict(int)
    for char in set(template):
        occurence[char] = template.count(char)
    word = template
    template = defaultdict(int)
    for a,b in zip(range(0,len(word)-1),range(1,len(word))):
        template[word[a:b+1]] += 1
    for _ in range(40):
        polymerization(template,occurence,rules)
    return max(occurence.values()) - min(occurence.values())
