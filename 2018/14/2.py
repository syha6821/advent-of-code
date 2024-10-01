def solve(M):
    scoreboard = [3,7]
    a = 0
    b = 1
    M = list(map(int,M))
    index = 0
    matched = 0

    while True:
        for score in str(scoreboard[a] + scoreboard[b]):
            s = int(score)
            scoreboard.append(s)
            if M[index] == s:
                matched += 1
                index += 1
                if matched == len(M):
                    return len(scoreboard) - len(M)
            else:
                index = 1 if M[0] == s else 0
                matched = 1 if M[0] == s else 0

        a = (a + scoreboard[a] + 1) % len(scoreboard)
        b = (b + scoreboard[b] + 1) % len(scoreboard)
