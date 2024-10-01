from collections import namedtuple
from functools import reduce

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

def solve(file):
    with open(file) as input:
        return max([seat_id(line.strip()) for line in input.readlines()])
