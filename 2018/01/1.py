def read_input(file):
    with open(file) as input:
        return list(map(int,input.read().strip().split('\n')))

def solve(file):
    return sum(read_input(file))
