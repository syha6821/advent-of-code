def transpose(matrix):
    result = [[] for _ in range(len(matrix[0]))]
    for line in matrix:
        for col,elm in enumerate(line):
            result[col].append(elm)
    return result
