from collections import defaultdict
from pprint import pprint

def read_input(file):
    graph = defaultdict(dict)
    with open(file) as input:
        for line in input.read()[:-1].split('\n'):
            node, *cs = line.replace(":","").split()
            for c in cs:
                graph[node][c] = 1
                graph[c][node] = 1
    return sum(len(edges) for edges in graph.values())
