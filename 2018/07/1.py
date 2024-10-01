from heapq import *
from collections import defaultdict,Counter

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

    ans = []

    while h:
        alp = heappop(h)
        ans.append(alpha(alp))
        for a in graph[alp]:
            indegree[a] -= 1
            if indegree[a] == 0:
                heappush(h,a)

    return "".join(ans)
