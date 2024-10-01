from itertools import takewhile

def read_input(file):
    with open(file) as input:
        jolts = list(map(int,input.read().strip().split('\n')))
        jolts.append(max(jolts)+3)
        jolts.sort()
        return jolts

def cases(jolts):
    mem = dict()
    def aux(prev,index):
        if index == len(jolts)-1:
            return 1
        m = mem.get((prev,index))
        if m:
            return m
        else:
            res = sum(aux(jolts[i],i+1) for i in takewhile(lambda i : abs(prev-jolts[i]) <= 3,range(index,len(jolts))))
            mem[(prev,index)] = res
            return res
    return aux(0,0)

def solve(file):
    return cases(read_input(file))
