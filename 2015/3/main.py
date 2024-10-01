from santa import *

filename = "./input.txt"

moves = ""

with open(filename, "r") as f:
    move = f.readline()
    moves = move[:-1]

houses = set()

santa = Santa()
robot = Santa()

houses.add(santa.location())

for order in range(0, len(moves), 2):
    print(order, order + 1)

    santa.move(moves[order])
    houses.add(santa.location())

    if order == len(moves) - 1:
        break

    robot.move(move[order + 1])
    houses.add(robot.location())

print(len(houses))
