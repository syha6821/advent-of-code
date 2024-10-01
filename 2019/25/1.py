from intcode import execute,make_memory
from itertools import chain
from copy import deepcopy
from itertools import combinations
from sys import setrecursionlimit

setrecursionlimit(10**9)

DIRECTIONS = {"north","west","south","east"}

def read_droid(file):
    with open(file) as input:
        return make_memory(list(map(int,input.read().strip().split(','))))

def encode(code):
    return list(map(ord,chain(code,"\n")))

def decode(code):
    return "".join(list(map(chr,code)))

def run(droid,ip=0):
    outputs = []
    command = ""
    while True:
        ip = execute(droid,ip=ip,input=iter(encode(command)),outputs=outputs,halt_on_output=True)
        if outputs[-1] == 10:
            message = decode(outputs).strip()
            if message:
                print(message)
                if message == "Command?":
                    command = input().strip()
            outputs = []

GATHER = ["east",
          "take whirled peas",
          "north",
          "take coin",
          "west",
          "south",
          "take antenna",
          "north",
          "north",
          "west",
          "take astrolabe",
          "east",
          "south",
          "east",
          "south",
          "east",
          "north",
          "take prime number",
          "south",
          "east",
          "east",
          "east",
          "take dark matter",
          "west",
          "west",
          "west",
          "west",
          "west",
          "north",
          "take fixed point",
          "north",
          "take weather machine",
          "east"]

ITEMS = ["whirled peas","coin","antenna","astrolabe","prime number","dark matter","fixed point","weather machine"]

def run_commands(droid,ip,commands):
    outputs = []
    command = ""
    ip = 0
    commands = iter(commands)
    while True:
        ip = execute(droid,ip=ip,input=iter(encode(command)),outputs=outputs,halt_on_output=True)
        if outputs[-1] == 10:
            message = decode(outputs).strip()
            if message:
                print(message)
                if message == "Command?":
                    try:
                        command = next(commands)
                    except StopIteration:
                        return droid,ip
            outputs = []

def solve(file):
    droid = read_droid(file)
    for i in range(1,len(ITEMS)):
        for items in combinations(ITEMS,i):
            commands = list(map(lambda item : "drop " + item, items)) + ["south"]
            run_commands(deepcopy(droid),0,GATHER+commands)
