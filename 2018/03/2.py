from collections import defaultdict

def readline(line):
    line = line.split()
    num = int(line[0][1:])
    row,col = list(map(int,line[2][:-1].split(',')))
    width,height = list(map(int,line[3].split('x')))
    return num,(row,col),(width,height)

def read_input(file):
    with open(file) as input:
        return list(map(readline,input.read().strip().split('\n')))

def draw(claims):
    map_ = defaultdict(list)
    for num,(col,row),(width,height) in claims:
        for r in range(row,row+height):
            for c in range(col,col+width):
                map_[(r,c)].append(num)
    return map_

def solve(file):
    claims = read_input(file)
    map_ = draw(claims)
    nums = set(map(lambda l : l[0],claims))
    for l in map_.values():
        if len(l) > 1:
            for n in l:
                if n in nums:
                    nums.remove(n)
    return next(iter(nums))
