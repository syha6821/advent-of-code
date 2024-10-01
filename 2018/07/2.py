from heapq import *
from collections import defaultdict,Counter

IDLE = "."

def order(a):
    return ord(a) - 65

def alpha(n):
    return chr(n + 65)

def parse_line(line):
    l = line.split()
    return [order(l[1]),order(l[7])]

def read_input(file):
    with open(file) as input:
        return [parse_line(line) for line in input.readlines()]

def solve(file):
    indegree = Counter()
    graph = defaultdict(list)
    for req,alp in read_input(file):
        graph[req].append(alp)

        indegree[alp] += 1
        if not indegree[req]:
            indegree[req] = 0

    h = []

    for alp,cnt in indegree.items():
        if cnt == 0:
            heappush(h,alp)

    remain = len(indegree)

    sec = 0
    T = 60
    W = 5
    workers = [[IDLE,0] for _ in range(W)]

    while remain:
        done = []
        for worker in workers:
            state,t = worker
            if state == IDLE and h:
                a = heappop(h)
                worker[0] = a
                worker[1] = a + T + 1
            elif t == 1:
                done.append(state)
                worker[0] = IDLE
                worker[1] = 0
                remain -= 1
            elif t > 1:
                worker[1] -= 1

        for a in done:
            for a in graph[a]:
                indegree[a] -= 1
                if indegree[a] == 0:
                    heappush(h,a)

        for worker in workers:
            state,t = worker
            if state == IDLE and h:
                a = heappop(h)
                worker[0] = a
                worker[1] = a + T + 1

        sec += 1

    return sec - 1
