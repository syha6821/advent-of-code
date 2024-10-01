from itertools import chain,permutations,combinations,product
from collections import namedtuple
from fractions import Fraction 

Scanner = namedtuple("Scanner",["beacons","distances"])
Pos = namedtuple("Pos",["x","y","z"])
Pos.__add__ = lambda self,other : Pos(self.x+other.x,self.y+other.y, self.z+other.z)

MINIMUM_OVERLAPS = 12
UNIT_FACE = ("+x","+z","+y")

facing_plus_x = (("+x","+z","+y"),
                 ("+x","-y","+z"),
                 ("+x","-z","-y"),
                 ("+x","+y","-z"))

facing_minus_x = (("-x","+z","-y"),
                  ("-x","-y","-z"),
                  ("-x","-z","+y"),
                  ("-x","+y","+z"))

facing_plus_y = (("+y","+z","-x"),
                 ("+y","-x","-z"),
                 ("+y","-z","+x"),
                 ("+y","+x","+z"))

facing_minus_y = (("-y","+z","+x"),
                  ("-y","-x","+z"),
                  ("-y","-z","-x"),
                  ("-y","+x","-z"))

facing_plus_z = (("+z","-y","-x"),
                 ("+z","-x","+y"),
                 ("+z","+y","+x"),
                 ("+z","+x","-y"))

facing_minus_z = (("-z","-y","+x"),
                  ("-z","-x","-y"),
                  ("-z","+y","-x"),
                  ("-z","+x","+y"))

facing = tuple(chain(facing_plus_x,facing_minus_x,facing_plus_y,facing_minus_y,facing_plus_z,facing_minus_z))


def distance(pos1,pos2):
    return Fraction(sum(tuple(abs(p1-p2) for p1,p2 in zip(pos1,pos2))),len(pos1))

def read_scanners(filepath):
    with open(filepath) as input:
        for scanner in input.read().strip().split("\n\n"):
            beacons = tuple(tuple(map(int,line.strip().split(','))) for line in scanner.split("\n")[1:])
            yield Scanner(beacons,{beacon:set(distance(other,beacon) for other in beacons) for beacon in beacons})

def overlaps(s1,s2):
    for b1,b2 in product(s1.beacons,s2.beacons):
        s1_distances = s1.distances[b1]
        s2_distances = s2.distances[b2]
        inter = s1_distances & s2_distances
        if len(inter) >= MINIMUM_OVERLAPS:
            inter1 = sorted((beacon for beacon in s1.beacons if distance(beacon,b1) in inter),key= lambda beacon: distance(beacon,b1))
            inter2 = sorted((beacon for beacon in s2.beacons if distance(beacon,b2) in inter),key= lambda beacon: distance(beacon,b2))
            return inter1,b1,inter2,b2
    return False

def apply_face(pos,face):
    p = {f[1]:p if f[0] == '+' else -p for p,f in zip(pos,face)}
    return Pos(p["x"],p["y"],p["z"])

def match_face(ref1,face1,ref2):
    m = apply_face(ref1,face1)
    for face in facing:
        if m == apply_face(ref2,face):
            return face
    return False

def face_change(beacon,fr,to):
    to = {f[1]:f[0] for f in to}
    m = {f[1]:b if to[f[1]] == f[0] else -b for f,b in zip(fr,beacon)}
    return Pos(m["x"],m["y"],m["z"])

def get_scanner_infos(scanners):
    inspected = dict()
    inspected[0] = {"scanner":scanners[0],"face":UNIT_FACE,"position":Pos(0,0,0)}
    found = set()
    found.update(apply_face(beacon,UNIT_FACE) for beacon in scanners[0].beacons)
    while len(inspected) != len(scanners):
        for i,j in ((i,j) for i,j in combinations(range(0,len(scanners)),2) if not i == j):
            if (i in inspected) == (j in inspected):
                continue
            if j in inspected:
                i,j = j,i
            overlap = overlaps(scanners[i],scanners[j])
            if not overlap:
                continue
            inter1,b1,inter2,b2 = overlap
            i1 = next(b for b in inter1 if b != b1)
            i2 = next(b for b in inter2 if b != b2)
            i1_face = inspected[i]["face"]
            i2_face = match_face(tuple(p1-p2 for p1,p2 in zip(i1,b1)),inspected[i]["face"],tuple(p1-p2 for p1,p2 in zip(i2,b2)))
            i1_faced = apply_face(i1,i1_face)
            i1_face_changed = face_change(i1,i1_face,UNIT_FACE)
            i2_face_changed = face_change(i2,i2_face,UNIT_FACE)
            diff = Pos(i1_face_changed.x-i2_face_changed.x,i1_face_changed.y-i2_face_changed.y,i1_face_changed.z-i2_face_changed.z)
            inspected_location = inspected[i]["position"] + diff
            adjusted_beacons = list(face_change(beacon,i2_face,UNIT_FACE)+inspected_location for beacon in scanners[j].beacons)
            found.update(adjusted_beacons)
            inspected[j] = {"scanner":scanners[j],"face":i2_face,"position":inspected_location}
    return inspected

def manhattan(p1,p2):
    return sum(abs(p11-p22) for p11,p22 in zip(p1,p2))

def solve(filepath):
    scanners = get_scanner_infos(list(read_scanners(filepath)))
    return max(manhattan(p1,p2) for p1,p2 in combinations((scanner["position"] for scanner in scanners.values()),2))
