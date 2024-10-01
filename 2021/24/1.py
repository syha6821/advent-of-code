from itertools import product

BS = [12,11,13,11,14,-10,11,-9,-3,13,-5,-10,-4,-5]
CS = [4,11,5,11,14,7,11,4,6,5,9,12,14,14]

def make_monad(digits):
    z = 0
    index = 0
    ans = [0] * 14
    for i in range(14):
        if BS[i] > 0:
            z = 26 * z + digits[index] + CS[i]
            ans[i] = digits[index]
            index += 1
        else:
            digit = z % 26 + BS[i]
            if digit > 9 or digit < 1:
                return False
            else:
                ans[i] = digit
                z //= 26
    return ans if z == 0 else False

def largest_monad():
    for digits in product(range(9,0,-1),repeat=7):
        monad = make_monad(digits)
        if monad:
            return int(''.join(map(str,monad)))
    return False
