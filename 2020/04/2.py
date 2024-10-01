def read_info(info):
    info = dict(map(lambda i: i.split(":"),info.replace("\n"," ").split(" ")))
    return info

def is_valid_byr(byr):
    byr = int(byr)
    return 1920 <= byr and byr <= 2002

def is_valid_iyr(iyr):
    byr = int(iyr)
    return 2010 <= byr and byr <= 2020

def is_valid_eyr(eyr):
    byr = int(eyr)
    return 2020 <= byr and byr <= 2030

def is_valid_hgt(hgt):
    if len(hgt) <= 2:
        return False
    num = int(hgt[:-2])
    if hgt[-2:] == "cm":
        return 150 <= num and num <= 193
    elif hgt[-2:] == "in":
        return 59 <= num and num <= 76
    return False

def is_valid_hcl(hcl):
    if hcl[0] != "#":
        return False
    for c in hcl[1:]:
        if not(c.isdigit() or c.isalpha()):
            return False
    return True

def is_valid_ecl(ecl):
    return ecl in {"amb","blu","brn","gry","grn","hzl","oth"}

def is_valid_pid(pid):
    return len(pid) == 9 and all(map(lambda c : c.isdigit(),pid))

def is_valid_info(info):
    return (len(info) == 8 or (len(info) == 7 and not(info.get("cid"))))\
        and is_valid_byr(info.get("byr"))\
        and is_valid_iyr(info.get("iyr"))\
        and is_valid_eyr(info.get("eyr"))\
        and is_valid_hgt(info.get("hgt"))\
        and is_valid_hcl(info.get("hcl"))\
        and is_valid_ecl(info.get("ecl"))\
        and is_valid_pid(info.get("pid"))\

def read_input(file):
    with open(file) as input:
        infos = input.read().strip().split("\n\n")
        return list(read_info(info) for info in infos)

def solve(file):
    infos = read_input(file)
    return len(list(filter(is_valid_info,infos)))
