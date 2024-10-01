def read_input(file):
    with open(file) as input:
        return tuple(map(int,input.read().strip().split('\n')))

def transform(subject,loop):
    return pow(subject,loop,20201227)

# def find_loop(pk):
#     try_num = 0
#     while True:
#         if transform(7,try_num) == pk:
#             return try_num
#         try_num += 1

def find_loop(key):
    val = 1
    for i in range(1,10000000000):
        val = val * 7 %  20201227
        if key == val:
            return i

def solve(file):
    pk1,pk2 = read_input(file)
    loop1 = find_loop(pk1)
    loop2 = find_loop(pk2)
    encryption1 = transform(pk1,loop2)
    encryption2 = transform(pk2,loop1)
    return encryption1 if encryption1 == encryption2 else -1
