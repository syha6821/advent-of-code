from itertools import batched,dropwhile
from collections import Counter

BLACK = '0'
WHITE = '1'
TRANSPARENT = '2'

def read_input(file):
    with open(file) as input:
        return input.read().strip()

def solve(file):
    data = read_input(file)
    width = 25
    height = 6
    layers = list(batched(data,width*height))
    layered_image = [[layer[n] for layer in layers] for n in range(width*height)]
    image = [list(dropwhile(lambda p: p == TRANSPARENT ,pixels))[0] for pixels in layered_image]
    for line in batched(image,width):
        print("".join("█"if val == BLACK else "▒" for val in line))
