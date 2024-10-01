from collections import defaultdict, namedtuple,Counter

Timestamp = namedtuple("Timestamp",["year","month","day","hour","minutes"])
Date = namedtuple("Date",["y","m","d"])
Time = namedtuple("Time",["h","m"])

def read_date(line):
    return Date(*map(int,line.split("-")))

def read_time(line):
    return Time(*map(int,line.split(":")))

def read_timestamp(line):
    date,time = line.split('[')[1].split(']')[0].split()
    return Timestamp(*read_date(date),*read_time(time))

def read_input(file):
    with open(file) as input:
        return input.read().strip().split('\n')

def solve(file):
    lines = sorted(map(lambda line : (read_timestamp(line),line.split()[2:]),read_input(file)),key = lambda t : t[0])
    total_slept = defaultdict(int)
    slept_minutes = defaultdict(Counter)
    num = -1
    start = 0
    for timestamp,message in lines:
        if message[0] == "Guard":
            num = int(message[1][1:])
        elif message[0] == "falls":
            start = timestamp.minutes
        elif message[0] == "wakes":
            total_slept[num] += timestamp.minutes - start
            for m in range(start,timestamp.minutes):
                slept_minutes[num][m] += 1


    person = 0
    minute = 0
    count = 0

    for num,minutes in slept_minutes.items():
        for m,cnt in minutes.items():
            if cnt > count:
                count = cnt
                minute = m
                person = num


    return person * minute
