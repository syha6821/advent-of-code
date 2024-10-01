from collections import namedtuple
import sys

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

def simulate(time,moons):
    if time == 0:
        return moons
    else:
        return simulate(time-1,[apply_gravity(moon,moons) for moon in moons])

def potential(moon):
    return sum(map(abs,moon.pos))

def kinetic(moon):
    return sum(map(abs,moon.vel))

def solve(file):
    moons = read_input(file)
    moons = simulate(1000,moons)
    return sum(map(lambda moon: potential(moon) * kinetic(moon),moons))
