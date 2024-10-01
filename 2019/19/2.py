from intcode import execute,make_memory
from copy import deepcopy

is_pulled = lambda state: state == 1

def read_input(file):
    with open(file) as input:
        return make_memory(list(map(int,input.read().strip().split(','))))

def scan_pos(program,x,y):
    outputs = []
    execute(deepcopy(program),ip = 0, input = iter([x,y]),outputs = outputs)
    return outputs[-1]

def is_fullline(program,start_x,end_x,y):
    return all(map(is_pulled,map(lambda pos : scan_pos(program,*pos),[(start_x,y),(end_x,y)])))

def find_square(program,size):
    x,y = 5,6
    while True:
        x = next(x_ for x_ in count(x) if is_pulled(scan_pos(program,x_,y)))
        for x_ in takewhile(lambda x_ : is_fullline(program,x_, x_+size-1,y),count(x)):
            if is_fullline(program,x_,x_+size-1,y+size-1):
                yield x_,y
        y += 1

def draw(program,size):
    for y in range(size):
        for x in range(size):
            pixel = scan_pos(program,x,y)
            print("#" if pixel == 1 else ".",end="")
        print()

def solve(file):
    x,y = next(find_square(read_input(file),100))
    return x * 10000 + y
