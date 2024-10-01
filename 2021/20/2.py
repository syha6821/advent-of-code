from collections import namedtuple
from operator import countOf

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other: Pos(self.row+other.row,self.col+other.col)
DARK = "."
LIGHT = "#"
PIXEL_VAL = {"#":"1",".":"0"}
DIRECTIONS = ("NW","N","NE","W","SELF","E","SW","S","SE")
UNIT_POS = {"SELF":Pos(0,0),
            "N":Pos(-1,0),
            "NE":Pos(-1,1),
            "E":Pos(0,1),
            "SE":Pos(1,1),
            "S":Pos(1,0),
            "SW":Pos(1,-1),
            "W":Pos(0,-1),
            "NW":Pos(-1,-1)}

Image = namedtuple("Image",["map","width","height","outer"])

def read_image(input):
    image = dict()
    for row,line in enumerate(input.split("\n")):
        for col,val in enumerate(line):
            image[Pos(row,col)] = val
    return Image(image,max(map(lambda p:p.col,image))+1,max(map(lambda p:p.row,image))+1,".")

def read_input(filepath):
    with open(filepath) as input:
        algorithm, image = input.read().strip().split("\n\n")
        return list(algorithm),read_image(image)

def adjacents(pos):
    return tuple(pos+UNIT_POS[dir] for dir in DIRECTIONS)

def value_at(pos,image):
    return ''.join(PIXEL_VAL[image.map[p] if p in image.map else image.outer] for p in adjacents(pos))

def enhance_image(image,algorithm):
    output = dict()
    for row in range(0,image.height+2):
        for col in range(0,image.width+2):
            output[Pos(row,col)] = algorithm[int(value_at(Pos(row-1,col-1),image),2)]
    return Image(output,image.width+2,image.height+2,algorithm[0] if image.outer == '.' else algorithm[-1])

def enhance(image,algorithm,time):
    if time == 0:
        return image
    else:
        return enhance(enhance_image(image,algorithm),algorithm,time-1)

def draw_image(image):
    for row in range(0,image.height):
        print(''.join(image.map[Pos(row,col)] for col in range(0,image.width)))

def solve(filepath):
    algorithm,image = read_input(filepath)
    output = enhance(image,algorithm,50)
    return countOf(output.map.values(),LIGHT)
