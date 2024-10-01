def modinv(x,p):
    return pow(x,-1,p)

def before_new_stack(index,size):
    return size - index - 1

def before_cut(index,size,n):
    return (index + n) % size

def before_increment(index,size,n):
    return (modinv(n,size) * index) % size

def ab_new_stack(size):
    return -1,size-1

def ab_cut(n):
    return 1,n

def ab_increment(size,n):
    return modinv(n,size),0

def read_input(file):
    with open(file) as input:
        return input.read().strip().split("\n")

def compose(processes,size):
    a = 1
    b = 0
    for p in processes:
        a_,b_ = 1,0
        if p.startswith("deal with increment"):
             a_,b_ = ab_increment(size,int(p.removeprefix("deal with increment")))
        elif p.startswith("deal into new stack"):
             a_,b_ = ab_new_stack(size)
        elif p.startswith("cut"):
             a_,b_ = ab_cut(int(p.removeprefix("cut")))
        b += a * b_
        a *= a_
    return a,b

def solve(file):
    processes = read_input(file)
    size = 119315717514047
    times = 101741582076661
    index = 2020
    a,b = compose(processes,size)
    return ((pow(a,times,size) * index) + ((b % size) * (((pow(a,times,size) - 1%size) % size)*(modinv(a-1,size) % size)))) % size
