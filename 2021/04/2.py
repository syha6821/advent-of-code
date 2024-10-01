from collections import defaultdict,namedtuple

Pos = namedtuple("Pos",["row","col"])

def read_board(input):
    board = []
    for line in input.split('\n'):
        board.append(list(map(int, line.split())))
    return board

def read_input(filepath):
    with open(filepath) as input:
        input = input.read().strip().split('\n\n')
        return list(map(int,input[0].strip().split(','))),[read_board(board) for board in input[1:]]

def read_position(board):
    position = dict()
    for row,line in enumerate(board):
        for col,num in enumerate(line):
            position[num] = Pos(row,col)
    return position

def get_col(col,board):
    line = []
    for row in board:
        line.append(row[col])
    return line

def get_row(row,board):
    return board[row]

def sum_board(board):
    return sum((sum(row) for row in board))

def solve(filepath):
    nums,boards = read_input(filepath)
    positions = [read_position(board) for board in boards]
    bingos = [{"row":defaultdict(int),"col":defaultdict(int)} for _ in range(len(boards))]
    sums = [0] * len(boards)
    finished = set()
    for num in nums:
        for board,position,bingo,n in zip(boards,positions,bingos,range(0,len(boards))):
            if n in finished:
                pass
            pos = position.get(num)
            if pos:
                sums[n] += num
                bingo["row"][pos.row] += 1
                bingo["col"][pos.col] += 1
                if bingo["row"][pos.row] == 5 or bingo["col"][pos.col] == 5:
                    finished.add(n)
                    if len(finished) == len(boards):
                        return num * (sum_board(board) - sums[n])
