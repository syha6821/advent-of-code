from collections import defaultdict,namedtuple
from copy import deepcopy

Path = namedtuple("Path",["visited","last"])

def read_caves(filepath):
    caves = defaultdict(set)
    with open(filepath) as input:
        for line in input:
            start,end = line.strip().split('-')
            caves[start].add(end)
            caves[end].add(start)
    return caves

def find_all_path(caves):
    paths = [Path({"start"},"start")]
    def find_path(paths):
        # print(paths)
        finished = 0
        nexts = []
        if not paths:
            return 0
        else:
            for path in paths:
                if path.last == "end":
                    finished += 1
                else:
                    for adj in caves[path.last]:
                        if adj.isupper() or (adj.islower() and adj not in path.visited):
                            p = Path(deepcopy(path.visited),adj)
                            p.visited.add(adj)
                            nexts.append(p)
            return finished + find_path(nexts)
    return find_path(paths)
