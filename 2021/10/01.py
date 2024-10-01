from queue import LifoQueue

OPENING = {"(","[","{","<"}
CLOSING = {")","]","}",">"}
MATCH = {"(":")",
         ")":"(",
         "[":"]",
         "]":"[",
         "{":"}",
         "}":"{",
         "<":">",
         ">":"<"}

POINT = {")":3,"]":57,"}":1197,">":25137}

def find_incomplete(line):
    q = LifoQueue()
    for char in line:
        if char in OPENING:
            q.put(char)
        if char in CLOSING:
            c = q.get()
            if not c == MATCH[char]:
                return char
    return None

def read_input(filepath):
    with open(filepath) as input:
        for line in input:
            yield line.strip()

def solve(filepath):
    score = 0
    for line in read_input(filepath):
        incomplete = find_incomplete(line)
        if incomplete:
            score += POINT[incomplete]
    return score
