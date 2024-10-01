from collections import deque
from itertools import cycle

def solve(cnt,n):
    players = [0] * cnt
    circle = deque([0])
    for m,p in zip(range(1,n+1),cycle(list(range(cnt)))):
        if m % 23 == 0:
            for _ in range(7):
                circle.appendleft(circle.pop())
            r = circle.pop()
            players[p] += m + r
            circle.append(circle.popleft())
        else:
            circle.append(circle.popleft())
            circle.append(m)

    return max(players)
