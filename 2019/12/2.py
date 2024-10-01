from collections import namedtuple
import sys
from math import lcm

sys.setrecursionlimit(10**9)

Pos = namedtuple("Pos",["x","y","z"])
Vel = namedtuple("Vel",["x","y","z"])
Moon = namedtuple("Moon",["name","pos","vel"])

Pos.__add__ = lambda self,other : Pos(self.x+other.x,self.y+other.y,self.z+other.z)
Vel.__add__ = lambda self,other : Pos(self.x+other.x,self.y+other.y,self.z+other.z)

def read_moon(line):
    x,y,z = list(map(lambda p : int(p.strip()[2:]),line[1:][:-1].split(',')))
    return Pos(x,y,z),Vel(0,0,0)

def read_input(file):
    with open(file) as input:
        moons = []
        for name,line in zip(["Io","Europa","Ganymede","Callisto"],input.read().strip().split('\n')):
            moons.append(Moon(name,*read_moon(line)))
        return moons

def compare(x,y):
    return 0 if x == y else 1 if x > y else -1

def calc_gravity(moon,moons):
    moons = filter(lambda m : moon.name != m.name,moons)
    gravity = [0,0,0]
    for m in moons:
        for i,coord in enumerate(m.pos):
            gravity[i] += compare(coord,moon.pos[i])
    return Vel(*gravity)

def apply_gravity(moon,moons):
    gravity = calc_gravity(moon,moons)
    vel = moon.vel + gravity
    return Moon(moon.name,moon.pos+vel,vel)

def simulate(moons,time = 1):
    if time == 0:
        return moons
    else:
        return simulate([apply_gravity(moon,moons) for moon in moons],time-1)

def calc_repeat_x(moon,moons):
    index = moons.index(moon)
    def aux(moons,time):
        if moon == moons[index]:
            return time + 1
        else:
            return aux(simulate(moons),time + 1)
    return aux(simulate(moons),0)

def coords_pos(coord,moons):
    return [getattr(moon.pos,coord) for moon in moons]
def coords_vel(coord,moons):
    return [getattr(moon.vel,coord) for moon in moons]

def calc_repeat(moons):
    pos = {"x":coords_pos("x",moons),"y":coords_pos("y",moons),"z":coords_pos("z",moons)}
    vel = {"x":coords_vel("x",moons),"y":coords_vel("y",moons),"z":coords_vel("z",moons)}
    def aux(coord,moons,time):
        if pos[coord] == coords_pos(coord,moons) and vel[coord] == coords_vel(coord,moons):
            return time + 1
        else:
            return aux(coord,simulate(moons),time + 1)
    return lcm(aux("x",simulate(moons),0),aux("y",simulate(moons),0),aux("z",simulate(moons),0))

def solve(file):
    moons = read_input(file)
    return calc_repeat(moons)
