from random import randint

n = int(input("n >> "))
fname = input("file name >> ")

with open(fname, "wb") as f:
    for j in range(n):
        # 65535
        barr = [randint(0,3).to_bytes(4, byteorder='little') for i in range(n)]
        f.write(b''.join(barr))
