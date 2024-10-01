from collections import namedtuple,deque
from itertools import starmap,takewhile

PLANT = 1
GROUND = 0

Pot = namedtuple("Pot",["id","state"])

def parse_state(state):
    return [1 if s == "#" else 0 for s in state]

def parse_instruction(line):
    state,res = map(lambda l : l.strip(),line.split("=>"))
    return parse_state(state),1 if res == "#" else 0

def read_input(file):
    with open(file) as file:
        state = deque(starmap(Pot,enumerate(parse_state(file.readline().split(":")[1].strip()))))
        file.readline()
        instructions = [[[[[0] * 2 for _ in range(2)] for _ in range(2)] for _ in range(2)] for _ in range(2)]
        for (a,b,c,d,e),pot in map(parse_instruction,file.readlines()):
            instructions[a][b][c][d][e] = pot
        return state,instructions

def state_str(state):
    return "".join(["#" if s else "." for _,s in state])

def add_pad(state):
    left_cnt = len(list(takewhile(lambda pot : pot.state == GROUND,state)))
    while left_cnt != 5:
        if left_cnt < 5:
            state.appendleft(Pot(state[0].id - 1, GROUND))
            left_cnt += 1
        elif left_cnt > 5:
            state.popleft()
            left_cnt -= 1
    right_cnt = len(list(takewhile(lambda pot : pot.state == GROUND,reversed(state))))
    while right_cnt != 5:
        if right_cnt < 5:
            state.append(Pot(state[-1].id + 1, GROUND))
            right_cnt += 1
        elif right_cnt > 5:
            state.pop()
            right_cnt -= 1
    return state

def next_gen(state,instructions):
    pots = deque([state[0],state[1],state[2],state[3],state[4]])
    result = deque([state[0],state[1]])
    for i in range(5,len(state)):
        a,b,c,d,e = pots
        result.append(Pot(c.id,instructions[a.state][b.state][c.state][d.state][e.state]))
        pots.popleft()
        pots.append(state[i])
    return add_pad(result)

def trim(state):
    return "".join(map(lambda pot : str(pot.state),state))

def val(state):
    return sum(id for id,s in state if s == 1)

def nth_gen(state,instructions,n):
    history = dict()
    for gen in range(n):
        if trim(state) in history:
            prev_val = val(state)
            state = next_gen(state,instructions)
            v = val(state)
            return gen+1,v,v - prev_val
        else:
            history[trim(state)] = gen
            state = next_gen(state,instructions)
    return state

def solve(file):
    state, instructions = read_input(file)
    G = 50000000000
    state = add_pad(state)
    gen,v,interval = nth_gen(state,instructions,G)
    return (G - gen) * interval + v
