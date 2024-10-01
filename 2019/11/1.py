import sys
sys.path.insert(0,'..')
import intcode

from collections import namedtuple,defaultdict

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(self.row+other.row,self.col+other.col)
BLACK = 0
WHITE = 1
LEFT = 0
RIGHT = 1
DIRECTION = {0:"U",1:"R",2:"D",3:"L"}
UNIT_POS = {"U":Pos(-1,0),"R":Pos(0,1),"D":Pos(1,0),"L":Pos(0,-1)}

def read_input(file):
    with open(file) as input:
        return list(map(int,input.read().strip().split(',')))

def solve(file):
    program = intcode.make_memory(read_input(file))
    ip = 0
    direction = 0
    history = set()
    pos = Pos(0,0)
    ship = defaultdict(int)
    while True:
        outputs = []
        ip = intcode.execute(program,ip=ip,input=iter([ship[pos]]),outputs=outputs,halt_on_output=True)
        if ip == intcode.FINISH:
            break
        ip = intcode.execute(program,ip=ip,input=iter([ship[pos]]),outputs=outputs,halt_on_output=True)
        if ip == intcode.FINISH:
            break
        color,turn = outputs
        ship[pos] = color
        history.add(pos)
        if turn == LEFT:
            direction = (direction - 1) % len(DIRECTION)
        if turn == RIGHT:
            direction = (direction + 1) % len(DIRECTION)
        pos += UNIT_POS[DIRECTION[direction]]
    return len(history)
