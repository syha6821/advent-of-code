from collections import namedtuple

Pos = namedtuple("Pos",["x","y"])

def read_instructions(filepath):
    with open(filepath) as input:
        dots, folds = input.read().strip().split('\n\n')
        dots = map(lambda d: Pos(*map(int,d.split(','))),dots.split('\n'))
        folds = ((xy,int(val)) for xy,val in map(lambda f: f[11:].split('='),folds.split('\n')))
        return dots,folds

# (14,2) -> (0,2)

def fold(dots,xy,at):
    # - fold 
    if xy == "y":
        return set(dot if dot.y < at else Pos(dot.x,abs(dot.y - at * 2)) for dot in dots)
    # | fold 
    else:
        return set(dot if dot.x < at else Pos(abs(dot.x - at * 2),dot.y) for dot in dots)

def solve(filepath):
    dots,folds = read_instructions(filepath)
    dots = list(dots)
    for xy,at in folds:
        dots = fold(dots,xy,at)
    width = max(dot.x for dot in dots)
    height = max(dot.y for dot in dots)
    pict = list(['.']*(width+1) for _ in range(height + 1))
    for dot in dots:
        pict[dot.y][dot.x] = '#'
    for line in pict:
        print(line)
    return len(dots)
