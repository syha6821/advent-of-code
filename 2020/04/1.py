def read_info(info):
    info = dict(map(lambda i: i.split(":"),info.replace("\n"," ").split(" ")))
    return info

def is_valid_info(info):
    return len(info) == 8 or (len(info) == 7 and not(info.get("cid"))) 

def read_input(file):
    with open(file) as input:
        infos = input.read().strip().split("\n\n")
        return list(read_info(info) for info in infos)

def solve(file):
    infos = read_input(file)
    return len(list(filter(is_valid_info,infos)))
