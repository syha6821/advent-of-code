from collections import defaultdict

def solve(filename):
    vals = defaultdict(int)
    with open(filename) as input:
        for bits in input:
            for i,bit in enumerate(bits.strip()):
                vals[i] += 1 if bit == '1' else -1
    gamma = int(''.join('1' if val > 0 else '0' for val in vals.values()),2)
    epsilon = int(''.join('0' if val > 0 else '1' for val in vals.values()),2)
    return gamma * epsilon


