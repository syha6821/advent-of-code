from collections import defaultdict

def game(nums):
    mem = defaultdict(list)
    for turn,num in enumerate(nums):
        mem[num].append(turn)
    last = nums[-1]
    for turn in range(len(nums),30000000):
        m = mem[last]
        saying = None
        if len(m) == 1:
            saying = 0
        else:
            saying = m[-1] - m[-2]
        mem[saying].append(turn)
        last = saying
    return last
