def solve(filename):
    result = 0
    prev = False
    with open(filename) as input:
        for line in input:
            val = int(line[:-1])
            if prev and prev < val:
                result += 1
            prev = val
    return result

