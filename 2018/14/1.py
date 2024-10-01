def solve(N):
    scoreboard = [3,7]
    a = 0
    b = 1
    while len(scoreboard) < N + 10:
        for score in str(scoreboard[a] + scoreboard[b]):
            scoreboard.append(int(score))
        a = (a + scoreboard[a] + 1) % len(scoreboard)
        b = (b + scoreboard[b] + 1) % len(scoreboard)
    return "".join(map(str,scoreboard[N: N + 10]))
