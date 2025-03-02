from cyaron import *

num = 0
while num < 10:
    with open("E:\\C++\\出题\\词库拼接\\词库拼接\\source\\" + str(num) + ".in", 'a') as f:
        Num = 362000 # n 的数量
        Sum = 2000000
        cur = 0
        f.write(str(Num) + "\n")

        while Num > 0:
            Str = String.random((1, 10), charset = "abcdefghijklmnopqrstuvwxyz")
            cur = cur + len(Str)
            f.write(Str + "\n")
            Num = Num - 1
        
        if cur > Sum:
            f.truncate(0)
        else:
            print(cur)
            num = num + 1