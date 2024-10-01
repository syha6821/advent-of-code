def read_input(filepath):
    with open(filepath) as input:
        word, rules = input.read().strip().split("\n\n")
        template = word.strip()
        return template,dict(rule.strip().split(" -> ") for rule in rules.strip().split('\n'))

def polymerization(template,rules):
    result = ""
    for a,b in zip(range(0,len(template)-1),range(1,len(template))):
        result += template[a] + rules[template[a:b+1]]
    return result + template[-1]
    
def solve(filepath):
    template, rules = read_input(filepath)
    for _ in range(10):
        template = polymerization(template, rules)
    occurence = {char:template.count(char) for char in set(template)}
    return max(occurence.values()) - min(occurence.values())
