from collections import defaultdict
from queue import PriorityQueue
import sys
sys.setrecursionlimit(10**9)

def line_count(file):
    with open(file) as input:
        return len(input.read().strip().split('\n'))

def read_orbits(file):
    orbits = dict()
    with open(file) as input:
        for line in input.read().strip().split('\n'):
            l,r = line.split(")")
            orbits[r] = l
    return orbits

def read_map(file):
    m = defaultdict(set)
    with open(file) as input:
        for line in input.read().strip().split('\n'):
            l,r = line.split(")")
            m[r].add(l)
            m[l].add(r)
    return m

def min_transfer(start,dest,m):
    visited = set()
    pq = PriorityQueue()
    pq.put((0,start))
    def aux(dist,current):
        if current == dest:
            return dist
        else:
            visited.add(current)
            for adj in m[current]:
                if adj not in visited:
                    pq.put((dist+1,adj))
            return aux(*pq.get())
    return aux(*pq.get())

def solve(file):
    orbits = read_orbits(file)
    m = read_map(file)
    return min_transfer(orbits["YOU"],orbits["SAN"],m)
