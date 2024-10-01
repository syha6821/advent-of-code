from collections import namedtuple,deque,Counter
from itertools import accumulate

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(self.row+other.row,self.col+other.col)
UNIT_POS = {"U":Pos(-1,0),"R":Pos(0,1),"D":Pos(1,0),"L":Pos(0,-1)}
Edges = namedtuple("Edges",["U","R","D","L"])
Tile = namedtuple("Tile",["num","tile","edges"])

def read_tile(lines):
    num = int(lines[0][5:][:-1])
    top = lines[1]
    left = "".join(list(map(lambda l : l[0],lines[1:])))
    right = "".join(list(map(lambda l : l[-1],lines[1:])))
    bottom = lines[-1]
    return Tile(num,lines[1:],Edges(top,right,bottom,left))

def read_input(file):
    with open(file) as input:
        tiles = list(map(lambda lines : lines.split('\n'),input.read().strip().split("\n\n")))
        return list(map(read_tile,tiles))

def is_matched(e1,e2):
    return e1 == e2 or e1 == e2[::-1]

def get_edges(lines):
    top = lines[0]
    left = "".join(list(map(lambda l : l[0],lines)))
    right = "".join(list(map(lambda l : l[-1],lines)))
    bottom = lines[-1]
    return Edges(top,right,bottom,left)

def transpose(lines):
    return list(map(list,zip(*lines)))

def rotate_lines(lines,direction,degree = 90):
    degree = degree % 360
    if degree == 0:
        return lines
    if direction == "R":
        return rotate_lines(list(map(lambda l : "".join(l[::-1]),transpose(lines))),direction,degree - 90)
    if direction == "L":
        return rotate_lines(transpose(list(map(lambda l : "".join(l[::-1]),lines))),direction,degree - 90)
    raise Exception("Not valid arguments")

def flip_lines(lines):
    return [line[::-1] for line in lines]

def rotate(tile,direction,degree = 90):
    degree = degree % 360
    if degree == 0:
        return tile
    rotated = rotate_lines(tile.tile,direction)
    return rotate(Tile(tile.num,rotated,get_edges(rotated)),direction,degree - 90)

def opposite(direction):
    direction = direction.upper()
    return {"R":"L","L":"R","U":"D","D":"U"}[direction]

def is_match(edge,tile):
    return any(map(lambda e : is_matched(edge,e),tile.edges))

def find_match(edge,tiles):
    for tile in tiles:
        if is_match(edge,tile):
            return tile
    return False

# def flipped_edges(edges):
#     return Edges(edges.U[::-1],edges.L,edges.D[::-1],edges.R)

def flipped_tile(tile):
    flipped = list(map(lambda line : line[::-1],tile.tile))
    return Tile(tile.num,flipped,get_edges(flipped))

def print_tile(tile):
    for line in tile.tile:
        print("".join(line))

def match(t1,direction,t2):
    for tile in [t2,flipped_tile(t2)]:
        for rotate_direction in ["L","R"]:
            for t in accumulate([90,90,90],lambda acc,degree : rotate(acc,rotate_direction),initial=tile):
                if getattr(t1.edges,direction) == getattr(t.edges,opposite(direction)):
                    return t
    return False

def arrange_tiles(tiles):
    tiles = {tile.num:tile for tile in tiles}
    first_tile = next(iter(tiles.values()))
    image = {Pos(0,0):first_tile}
    arranged = deque([(Pos(0,0),first_tile)])
    while tiles:
        pos,tile = arranged.popleft()
        # print(tile.num)
        if tile.num not in tiles:
            continue
        tiles.pop(tile.num)
        for direction in ["U","R","D","L"]:
            found = find_match(getattr(tile.edges,direction),tiles.values())
            if found:
                matched = match(tile,direction,found)
                # print("FOUND",found.num,matched)
                matched_pos = pos + UNIT_POS[direction]
                image[matched_pos] = matched
                arranged.append((matched_pos,matched))
    min_row = min(image,key = lambda p : p.row).row
    min_col = min(image,key = lambda p : p.col).col
    # return image
    return {Pos(pos.row - min_row,pos.col - min_col):tile for pos,tile in image.items()}

def draw_image(image):
    image_height = max(image,key = lambda p : p.row).row + 1
    image_width = max(image,key = lambda p : p.col).col + 1
    tile_height = len(image[Pos(0,0)].tile)
    lines = [""] * image_height * (tile_height-2)
    for row in range(0,image_height):
        for col in range(0,image_width):
            for tile_row,line in enumerate(image[Pos(row,col)].tile[1:][:-1]):
                lines[(tile_height-2)*row+tile_row] = lines[(tile_height-2)*row+tile_row] + "".join(line[1:][:-1])
    return lines

def print_lines(lines):
    [print(line) for line in lines]

def match_pattern(line,pattern):
    for i in range(len(line)):
        if pattern[i] == " ":
            continue
        if pattern[i] != line[i]:
            return False
    return True

MONSTER = ["                  # ","#    ##    ##    ###"," #  #  #  #  #  #   "]

def match_monster(lines):
    return all(match_pattern(l,m) for l,m in zip(lines,MONSTER))

def count_monster(image):
    cnt = 0
    image_height = len(image)
    image_width = len(image[0])
    monster_height = len(MONSTER)
    monster_width = len(MONSTER[0])
    for start,stop in zip(range(0,image_width - monster_width),range(monster_width,image_width)):
        for row in range(image_height-monster_height):
            section = [image[r][start:stop] for r in range(row,row+monster_height)]
            if match_monster(section):
                cnt += 1
    return cnt

# count_monster(draw_image(arrange_tiles(read_input("sample.txt"))))

def char_in_lines(ch,lines):
    return sum(Counter(line)[ch] for line in lines) 


def solve(file):
    tiles = read_input(file)
    image = draw_image(arrange_tiles(tiles))
    tiles_in_monster = char_in_lines("#",MONSTER)
    total_tiles = char_in_lines("#",image)
    for img in [image,flip_lines(image)]:
        for i in accumulate([90,90,90],lambda acc,_ : rotate_lines(acc,"R"),initial=img):
            cnt = count_monster(i)
            if cnt != 0:
                return total_tiles - tiles_in_monster * cnt
