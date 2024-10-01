from collections import namedtuple
from functools import reduce
from itertools import product,chain

Range = namedtuple("Range",["start","stop"])
ROW_RANGE = Range(0,128)
COL_RANGE = Range(0,8)

def range_len(rng):
    return rng.stop - rng.start

def lower_half(rng):
    return Range(rng.start,rng.stop - (range_len(rng)//2))

def upper_half(rng):
    return Range(rng.start + (range_len(rng)//2),rng.stop)

def div_range(rng,letter):
    if letter == "F" or letter == "L":
        return lower_half(rng)
    return upper_half(rng)

def seat_id(seat):
    row_chars = seat[:7]
    col_chars = seat[7:]
    row = reduce(lambda acc,c: div_range(acc,c), row_chars, ROW_RANGE)
    col = reduce(lambda acc,c: div_range(acc,c), col_chars, COL_RANGE)
    return row.start*8 + col.start

def front_seats():
    row_chars = "FFFFFFF"
    return [seat_id(row_chars+"".join(cols)) for cols in product(["L","R"],repeat=3)]

def back_seats():
    row_chars = "BBBBBBB"
    return [seat_id(row_chars+"".join(cols)) for cols in product(["L","R"],repeat=3)]

def find_missing(seats):
    seats = sorted(seats)
    prev = seats[0]
    for i in seats[1:]:
        if i != prev + 1:
            return prev + 1
        else:
            prev = i

def solve(file):
    with open(file) as input:
        seats = set(seat_id(line.strip()) for line in input.readlines())
        return find_missing(seats)
