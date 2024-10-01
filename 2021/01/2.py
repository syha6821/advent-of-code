from queue import Queue

def solve(filename):
    result = 0
    window_sum = 0
    window = Queue(maxsize=3)
    with open(filename) as input:
        for line in input:
            val = int(line.strip())
            if window.full():
                head = window.get()
                window.put(val)
                if val > head:
                    result += 1
                window_sum += val - head
            else:
                window.put(val)
                window_sum += val
    return result
