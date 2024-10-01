from collections import namedtuple,deque
from itertools import count
from pprint import pprint

dx = [0,0,1,-1]
dy = [1,-1,0,0]

Area = namedtuple("Area",["id","x","y"])

def read_input(file):
    with open(file) as input:
        return [Area(id,*map(int,line.split(","))) for line,id in zip(input.readlines(),count(1))]

def minmax(nums):
    mn = nums[0]
    mx = nums[0]
    for n in nums:
        mn = min(mn,n)
        mx = max(mx,n)
    return mn,mx

def solve(file):
    areas = read_input(file)

    min_x,max_x = minmax([x for _,x,_ in areas])
    min_y,max_y = minmax([y for _,_,y in areas])
    width = max_x - min_x + 1
    height = max_y - min_y + 1
    areas = [Area(id,x - min_x,y - min_y) for id,x,y in areas]
    graph = [[0] * width for _ in range(height)]
    visited = [[0] * width for _ in range(height)]
    ins = [True] * (len(areas)+1)

    for id,x,y in areas:
        graph[y][x] = id
        visited[y][x] = 1

    def dfs(q,step):
        for _ in range(len(q)):
            id,x,y = q.popleft()

            for i in range(4):
                xx = x + dx[i]
                yy = y + dy[i]
                if (0 <= xx < width) and (0 <= yy < height):
                    if not visited[yy][xx]:
                        visited[yy][xx] = step
                        graph[yy][xx] = id
                        q.append(Area(id,xx,yy))
                    elif visited[yy][xx] == step and graph[yy][xx] != id:
                        graph[yy][xx] = -1
                else:
                    ins[id] = False
        if q:
            dfs(q,step+1)

    dfs(deque(areas),2)

    counts = [0] * (len(areas)+1)

    for row in range(height):
        for col in range(width):
            id = graph[row][col]
            if id != -1 and ins[id]:
                counts[id] += 1

    return max(counts)
