from collections import defaultdict,namedtuple
from copy import deepcopy

Path = namedtuple("Path",["visited","last","exhausted"],defaults = [{"start"},"start",False])

def read_caves(filepath):
    caves = defaultdict(set)
    with open(filepath) as input:
        for line in input:
            start,end = line.strip().split('-')
            caves[start].add(end)
            caves[end].add(start)
    return caves

def find_all_path(caves):
    paths = [Path()]
    def find_path(paths):
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
                        if adj == "start":
                            continue
                        if not path.exhausted:
                            p = Path(deepcopy(path.visited),adj,True if adj.islower() and adj in path.visited else False)
                            p.visited.add(adj)
                            nexts.append(p)
                        else:
                            if adj.isupper() or (adj.islower() and adj not in path.visited):
                                p = Path(deepcopy(path.visited),adj,True if adj.islower() else path.exhausted)
                                p.visited.add(adj)
                                nexts.append(p)
            return finished + find_path(nexts)
    return find_path(paths)
