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

POINT = {")":1,"]":2,"}":3,">":4}

def find_incomplete(line):
    q = LifoQueue()
    for char in line:
        if char in OPENING:
            q.put(char)
        if char in CLOSING:
            c = q.get()
            if not c == MATCH[char]:
                return char,q
    return None,q

def read_input(filepath):
    with open(filepath) as input:
        for line in input:
            yield line.strip()

def solve(filepath):
    scores = []
    for line in read_input(filepath):
        incomplete,q = find_incomplete(line)
        if not incomplete:
            score = 0
            for char in reversed(q.queue):
                score = score * 5 + POINT[MATCH[char]]
            scores.append(score)
    return sorted(scores)[len(scores)//2]
