from math import ceil
from itertools import chain

class Unit:
    def __init__(self,count,hp,weaks,immunes,type,damage,initiative):
        self.count = count
        self.hp = hp
        self.weaks = weaks
        self.immunes = immunes
        self.type = type
        self.damage = damage
        self.initiative = initiative
        self.target = None

    def effective(self):
        return self.count * self.damage

    def scan(self,defender):
        if self.type in defender.weaks:
            return self.damage * 2 * self.count
        elif self.type in defender.immunes:
            return 0
        else:
            return self.damage * self.count

    def attack(self):
        if self.target:
            damage = self.scan(self.target)
            killed = self.target.count - ceil((self.target.hp * self.target.count - damage)/self.target.hp)
            self.target.count = ceil((self.target.hp * self.target.count - damage)/self.target.hp)

def parse_weaks(line):
    try:
        index = line.index("weak to")
        words = line[index + 7:].split()
        weaks = []
        for word in words:
            weaks.append(word[:-1])
            if word.endswith(";") or word.endswith(")"):
                return weaks
    except:
        return []

def parse_immunes(line):
    try:
        index = line.index("immune to")
        words = line[index + 9:].split()
        weaks = []
        for word in words:
            weaks.append(word[:-1])
            if word.endswith(";") or word.endswith(")"):
                return weaks
    except:
        return []

def parse_line(line):
    weaks = parse_weaks(line)
    immunes = parse_immunes(line)
    words = line.split()
    count = int(words[0])
    hp = int(words[4])
    words = line[line.index("does ") + 5:].split()
    damage = int(words[0])
    type = words[1]
    initiative = int(words[-1])
    return Unit(count,hp,weaks,immunes,type,damage,initiative)

def read_input(file):
    immunes = []
    infections = []
    with open(file) as input:
        input.readline()
        while True:
            line = input.readline()
            if line.isspace():
                break
            else:
                immunes.append(parse_line(line))
        input.readline()
        for line in input.readlines():
            infections.append(parse_line(line))
    return immunes,infections

def choose_target(attacker,defender):
    not_choosen = set(defender)
    for a in sorted(attacker,key = lambda a : (-a.effective(),-a.initiative)):
        if not_choosen:
            target = max(not_choosen,key = lambda d : (a.scan(d),d.effective(),d.initiative))
            if a.scan(target) != 0:
                a.target = target
                not_choosen.remove(target)
            else:
                a.target = None
        else:
            a.target = None

def solve(file):
    immunes,infections = read_input(file)
    while immunes and infections:
        choose_target(immunes,infections)
        choose_target(infections,immunes)
        for unit in sorted(chain(immunes,infections),key = lambda unit : -unit.initiative):
            if unit.count > 0:
                unit.attack()
        immunes = [unit for unit in immunes if unit.count > 0]
        infections = [unit for unit in infections if unit.count > 0]

    return sum([unit.count for unit in (immunes if immunes else infections)])
    # return [unit.count for unit in (immunes if immunes else infections)]
