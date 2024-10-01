from copy import deepcopy
from queue import PriorityQueue
from itertools import takewhile,chain

import sys
sys.setrecursionlimit(1000000)

AMP_ENERGY = {"A":1,"B":10,"C":100,"D":1000}
ROOM_NUMBERS = {2,4,6,8}
AMP_NUMBER = {"A":2,"B":4,"C":6,"D":8}
CAPACITY = 2
ANS = ["","",["A","A"],"",["B","B"],"",["C","C"],"",["D","D"],"",""]
SAMPLE = ["","",["B","A"],"",["C","D"],"",["B","C"],"",["D","A"],"",""]
INPUT = ["","",["C","B"],"",["A","A"],"",["D","B"],"",["D","C"],"",""]
STEP2 = ["","",["B","A"],"B",["D"],"",["C","C"],"",["D","A"],"",""]
STEP3 = ["","",["B","A"],"B",[],"D",["C","C"],"",["D","A"],"",""]
STEP4 = freeze(['', '', ['B', 'A'], '', ['B'], 'D', ['C', 'C'], '', ['D', 'A'], '', ''])

def is_organized(room,index):
    return room and index == AMP_NUMBER[room[0]] and (len(room) == 1 or room[0] == room[1])

def is_hall(element):
    return type(element) == str

def is_room(element):
    return type(element) == list

def distance(fr,to,burrow):
    if is_room(burrow[fr]) and is_room(burrow[to]):
        return abs(fr-to) + 1 + CAPACITY - len(burrow[fr]) + CAPACITY - len(burrow[to])
    if is_hall(burrow[fr]) and is_room(burrow[to]):
        return abs(fr-to) + CAPACITY - len(burrow[to])
    return abs(fr-to) + (CAPACITY + 1) - len(burrow[fr])

def sight(index,burrow):
    left = range(index-1,-1,-1)
    right = range(index + 1,len(burrow))
    can_locate = lambda i : (not burrow[i]) if is_hall(burrow[i]) else True
    return chain(takewhile(can_locate, left),takewhile(can_locate , right))

def can_move(index,burrow):
    val = burrow[index]
    if is_hall(val):
        if not val:
            return False
        room = burrow[AMP_NUMBER[val]]
        return (not room) or room[0] == val
    if is_room(val):
        if not val:
            return False
        return not(is_organized(val,index))
    return False


def move(fr,to,burrow):
    if is_room(burrow[fr]):
        top = burrow[fr].pop(0)
        if is_hall(burrow[to]):
            burrow[to] = top
        else:
            burrow[to].insert(0,top)
    if is_hall(burrow[fr]):
        burrow[to].insert(0,burrow[fr])
        burrow[fr] = ""

def next_moves(burrow):
    for fr in (fr for fr in range(0,len(burrow)) if can_move(fr,burrow)):
        if is_hall(burrow[fr]):
            room_number = AMP_NUMBER[burrow[fr]]
            room = burrow[room_number]
            if room_number in sight(fr,burrow) and (not room or room[0] == burrow[fr]):
                yield fr,room_number
        if is_room(burrow[fr]):
            # print("From",fr,list(sight(fr,burrow)))
            room_number = AMP_NUMBER[burrow[fr][0]]
            matching_room = burrow[room_number]
            if room_number in sight(fr,burrow) and ((not matching_room) or (len(matching_room) == 1 and matching_room[0] == burrow[fr][0])):
                yield fr,room_number
            else:
                for to in (to for to in sight(fr,burrow) if to not in ROOM_NUMBERS):
                    yield fr,to

def freeze(burrow):
    return tuple(e if is_hall(e) else tuple(e) for e in burrow)

def organize(burrow):
    visited = set()
    pq = PriorityQueue()
    pq.put((0,burrow))
    def org(cost,burrow):
        if freeze(burrow) in visited:
            return org(*pq.get())
        visited.add(freeze(burrow))
        # print(cost,burrow)
        if burrow == ANS:
            return cost
        for fr,to in next_moves(burrow):
            br = deepcopy(burrow)
            c = cost + distance(fr,to,br)*AMP_ENERGY[br[fr][0]]
            move(fr,to,br)
            freezed = freeze(br)
            if freezed in visited:
                continue
            else:
                pq.put((c,br))
        return org(*pq.get())
    return org(*pq.get())
