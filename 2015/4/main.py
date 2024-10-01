import hashlib

file = "./sample.txt"
s_key = ""

with open(file) as f:
    s_key = f.readline()[:-1]

def is_mined(s_key, num):
    hashed = hashlib.md5((s_key+str(num)).encode()).hexdigest()
    if str(hashed)[:6] == "000000":
        return True
    return False


num = 0
find = False
while not find:
    if is_mined(s_key, num):
        print("The num is " + str(num))
        break;
    num = num + 1


