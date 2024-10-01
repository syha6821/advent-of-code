from collections import namedtuple

Node = namedtuple("Node",["children","meta"])

def read_input(file):
    with open(file) as input:
        return list(map(int,input.readline().split()))

def make_tree(nums):
    tree = dict()
    id = 0
    def aux(parent,index):
        nonlocal id
        node = Node([],[])
        tree[id] = node
        current_id = id
        id += 1
        if parent != None:
            tree[parent].children.append(current_id)
        children_cnt = nums[index]
        meta_cnt = nums[index+1]
        body_len = 2
        for _ in range(children_cnt):
            body_len += aux(current_id,index+body_len)

        for n in nums[index + body_len:index + body_len + meta_cnt]:
            tree[current_id].meta.append(n)

        return body_len + meta_cnt

    aux(None,0)

    return tree

def value_of(id,tree):
    children = tree[id].children
    meta = tree[id].meta
    if children:
        return sum((value_of(children[c-1],tree) if (c <= len(children)) else 0) for c in meta)
    else:
        return sum(meta)

def solve(file):
    nums = read_input(file)
    tree = make_tree(nums)
    return value_of(0,tree)
