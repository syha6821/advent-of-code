import re
import heapq

with open('sample2.txt') as f:
    data = list(f)

def d3(a, b):
    return abs(a[0]-b[0])+abs(a[1]-b[1])+abs(a[2]-b[2])

bots = [tuple(map(int, list(re.findall(r'-?\d+', ln)))) for ln in data]

# Find a box big enough to contain everything in range
maxabscord = max(max(abs(b[i])+b[3] for b in bots) for i in (0, 1, 2))

boxsize = 1
while boxsize <= maxabscord:
    boxsize *= 2

initial_box = ((-boxsize, -boxsize, -boxsize), (boxsize, boxsize, boxsize))

def does_intersect(box, bot):
    # returns whether box intersects bot
    d = 0
    for i in (0, 1, 2):
        boxlow, boxhigh = box[0][i], box[1][i] - 1
        d += abs(bot[i] - boxlow) + abs(bot[i] - boxhigh)
        d -= boxhigh - boxlow
    d //= 2
    return d <= bot[3]

def intersect_count(box):
    return sum(1 for b in bots if does_intersect(box, b))

workheap = [(-len(bots), -2*boxsize, 3*boxsize, initial_box)]
while workheap:
    print(workheap[0])
    (negreach, negsz, dist_to_orig, box) = heapq.heappop(workheap)
    if negsz == -1:
        print("Found closest at %s dist %s (%s bots in range)" %
              (str(box[0]), dist_to_orig, -negreach))
        break
    newsz = negsz // -2
    for octant in [(0, 0, 0), (0, 0, 1), (0, 1, 0), (0, 1, 1),
                   (1, 0, 0), (1, 0, 1), (1, 1, 0), (1, 1, 1)]:
        newbox0 = tuple(box[0][i] + newsz * octant[i] for i in (0, 1, 2))
        newbox1 = tuple(newbox0[i] + newsz for i in (0, 1, 2))
        newbox = (newbox0, newbox1)
        newreach = intersect_count(newbox)
        heapq.heappush(workheap,
                       (-newreach, -newsz, d3(newbox0, (0, 0, 0)), newbox))
