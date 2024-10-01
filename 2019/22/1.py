from functools import reduce

def new_stack(stack):
    return stack[::-1]

def cut(stack,n):
    return stack[n:] + stack[:n]

def increment(stack,n):
    new_stack = [0] * len(stack)
    for v,i in zip(stack,map(lambda x : (x * n) % len(stack),range(len(stack)))):
        new_stack[i] = v
    return new_stack

def read_input(file):
    processes = []
    with open(file) as input:
        for line in input.read().strip().split('\n'):
            if line.startswith("deal with increment "):
                processes.append([increment,int(line.removeprefix("deal with increment "))])
            if line.startswith("cut "):
                processes.append([cut,int(line.removeprefix("cut "))])
            if line.startswith("deal into"):
                processes.append([new_stack])
    return processes

def shuffle(deck,processes):
    return reduce(lambda acc, p : p[0](acc,*p[1:]),processes,deck)

def solve(file):
    size = 10
    deck = list(range(size))
    processes = read_input(file)
    return shuffle(deck,processes)

def shuffle_n(n,deck,processes):
    for _ in range(n):
        print(deck)
        deck = shuffle(deck,processes)
