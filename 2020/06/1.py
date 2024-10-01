def read_input(file):
    with open(file) as input:
        return list(map(lambda l : l.split('\n'),input.read().strip().split("\n\n")))

def read_questions(questions):
    qs = set()
    for q in questions:
        qs.update(q)
    return qs

def solve(file):
    return sum(map(lambda q : len(read_questions(q)),read_input(file)))
