from enum import IntEnum
from operator import add,mul,lt,eq
from collections import defaultdict

FINISH = -1

class Opcode(IntEnum):
    ADD = 1
    MUL = 2
    INPUT = 3
    OUTPUT = 4
    JUMPIFTRUE = 5
    JUMPIFFALSE = 6
    LESSTHAN = 7
    EQUALS = 8
    RELATIVE = 9
    QUIT = 99

class Mode(IntEnum):
    POSITION = 0,
    IMMEDIATE = 1,
    RELATIVE = 2

PARAM_COUNT = {Opcode.ADD:3,
               Opcode.MUL:3,
               Opcode.INPUT:1,
               Opcode.OUTPUT:1,
               Opcode.QUIT:0,
               Opcode.JUMPIFTRUE:2,
               Opcode.JUMPIFFALSE:2,
               Opcode.LESSTHAN:3,
               Opcode.EQUALS:3,
               Opcode.RELATIVE:1}

MATCHING_OPERATORS = {Opcode.ADD:add,Opcode.MUL:mul,Opcode.LESSTHAN:lt,Opcode.EQUALS:eq}

def make_memory(program):
    return defaultdict(int,enumerate(program))

def read_instruction(inst):
    digits = str(inst)
    opcode = int(digits[-2:])
    return opcode,list(map(int,list(digits[:-2].zfill(PARAM_COUNT[Opcode(opcode)])[::-1])))

def parameters(ip,opcode,modes,program):
    params = list(map(program.get,range(ip+1,ip+PARAM_COUNT[opcode]+1)))
    if opcode in [Opcode.ADD,Opcode.MUL,Opcode.LESSTHAN,Opcode.EQUALS]:
        params = params[:-1]
    return [param if mode == Mode.IMMEDIATE else (program[param] if mode == Mode.POSITION else program[param + program['r']]) for mode,param in zip(modes,params)]

def execute(program,ip = 0,input=iter([]),outputs=[],halt_on_output=False):
    def aux(ip):
        opcode,modes = read_instruction(program[ip])
        if opcode == Opcode.QUIT:
            return -1
        params = parameters(ip,opcode,modes,program)
        match opcode:
            case Opcode.INPUT:
                try:
                    program[program[ip+PARAM_COUNT[opcode]] + (program['r'] if modes[-1] == Mode.RELATIVE else 0)] = next(input)
                except StopIteration:
                    program[program[ip+PARAM_COUNT[opcode]] + (program['r'] if modes[-1] == Mode.RELATIVE else 0)] = -1
                    return ip + 1 + PARAM_COUNT[opcode]
            case Opcode.OUTPUT:
                outputs.append(params[0])
                if halt_on_output:
                    return ip+1+PARAM_COUNT[opcode]
            case Opcode.ADD | Opcode.MUL | Opcode.LESSTHAN | Opcode.EQUALS:
                program[program[ip+PARAM_COUNT[opcode]] + (program['r'] if modes[-1] == Mode.RELATIVE else 0)] = int((MATCHING_OPERATORS[opcode])(params[0],params[1]))
            case Opcode.JUMPIFTRUE:
                if params[0]:
                    return aux(params[1])
            case Opcode.JUMPIFFALSE:
                if not(params[0]):
                    return aux(params[1])
            case Opcode.RELATIVE:
                program['r'] += params[0]
            case _:
                raise Exception("Not a valid OP " + str(opcode) + " at " + str(ip))
        return aux(ip + 1 + PARAM_COUNT[opcode])
    return aux(ip)
