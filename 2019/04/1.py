from itertools import islice

def num_to_digits(num):
    return list(map(int,list(str(num))))

def is_increasing(digits):
    def aux(index):
        if index == len(digits) - 1:
            return True
        if digits[index] > digits[index+1]:
            return False
        else:
            return aux(index+1)
    return aux(0)

def two_adjs_same(digits):
    for i,j in zip(islice(digits,0,len(digits)-1),islice(digits,1,len(digits))):
        if i == j:
            return True
    return False

def is_valid(password):
    digits = num_to_digits(password)
    return len(digits) == 6 and is_increasing(digits) and two_adjs_same(digits)

def read_range(rng):
    start,stop = rng.split('-')
    return int(start),int(stop)+1

def solve(rng):
    return len(list(filter(is_valid,range(*read_range(rng)))))
