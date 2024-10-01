def read_input(file):
    with open(file) as input:
        return list(map(lambda l : l.split('\n'),input.read().strip().split("\n\n")))

def read_questions(questions):
    if len(questions) == 1:
        return set(questions[0])
    qs = set(questions[0])
    for q in questions[1:]:
        qs.intersection_update(q)
    return qs

def solve(file):
    return sum(map(lambda q : len(read_questions(q)),read_input(file)))
