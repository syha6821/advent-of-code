from itertools import count

def x_after_time(velocity,time):
    time = velocity if time > velocity else time
    return time*velocity - time*(time-1)/2

def y_after_time(velocity,time):
    return time*velocity - time*(time-1)/2

def read_target(filepath):
    with open(filepath) as input:
        xy = map(lambda s:s.strip(),input.read().strip().split(':')[1].split(','))
        x,y = map(lambda x: x.split("=")[1].split(".."),xy)
        return tuple(map(int,x)),tuple(map(int,y))

def x_velocity_time(target):
    min_edge = min(target)
    max_edge = max(target)
    for velocity in range(1,max_edge+1):
        for time in count(start=0):
            location = x_after_time(velocity,time)
            if location > max_edge:
                break
            if time > velocity:
                break
            if min_edge <= location and location <= max_edge:
                yield velocity,time


def find_velocity(x_target,y_target):
    top_y = max(y_target)
    bottom_y = min(y_target)
    for x_vel,time in x_velocity_time(x_target):
        for y_vel in range(bottom_y,abs(bottom_y)):
            if x_vel == time:
                for t in count(start=time):
                    y_location = y_after_time(y_vel,t)
                    if y_location < bottom_y:
                        break
                    if bottom_y <= y_location and y_location <= top_y:
                        yield (x_vel,y_vel)
            else:
                y_location = y_after_time(y_vel,time)
                if bottom_y <= y_location and y_location <= top_y:
                    yield (x_vel,y_vel)

def solve(filepath):
    return len(set(find_velocity(*read_target(filepath))))
