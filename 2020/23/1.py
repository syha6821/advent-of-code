def destination(cups,current,picked):
    low = min(cups)
    high = max(cups)
    def aux(dest):
        if dest < low:
            return high
        if dest in picked:
            return aux(dest-1)
        return dest
    return aux(current-1)

def pick(l,start,stop):
    picked = l[start:stop]
    if len(l) < stop:
        picked += l[:stop - len(l)]
    return picked

def remove(l,start,stop):
    removed = l[:start] + l[stop:]
    if len(l) < stop:
        removed = removed[stop-len(l):]
    return removed

def insert(l,v,index):
    index = (index % len(l)) 
    return l[:index+1] + v + l[index+1:]

def start_from(index,l):
    return l[index:] + l[:index]

def mix(num,round):
    def aux(cups,index,round):
        index = index % len(cups)
        current = cups[index]
        if round == 0:
            return cups
        else:
            picked = pick(cups,index+1,index+4)
            cups = remove(cups,index+1,index+4)
            dest = destination(cups,current,picked)
            dest_index = cups.index(dest)
            cups = insert(cups,picked,dest_index)
            return aux(cups,cups.index(current) + 1, round - 1)
    return aux(list(map(int,str(num))),0,round)

def solve(num):
    mixed = mix(num,100)
    ordered = start_from(mixed.index(1),mixed)[1:]
    return "".join(map(str,ordered))
