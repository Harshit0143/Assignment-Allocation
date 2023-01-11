import random
import pwd
import grp
import os
import matplotlib
from subprocess import Popen, PIPE
import shutil
uid = pwd.getpwnam("nobody").pw_uid
gid = grp.getgrnam("nogroup").gr_gid

shutil.chown("/Users/harshit/Downloads/project/main.cpp", uid, gid)
program_path = "/Users/harshit/Downloads/project/main.cpp"

p = Popen([program_path], stdout=PIPE, stdin=PIPE)
print("opened")

# p.stdin.write(b"1\n")
# p.stdin.write(b"2\n")
# p.stdin.flush()

# result = p.stdout.readline().strip()
# assert result == b"3"


def rand_matrix(n, l, u):
    L = []
    for i in n:
        L.append([])
        for j in n:
            L.append(random.randint(l, u))


test_num = 200
eff_l, = int(input())

test_num = int(input())

time_dp = [None]*test_num
time_brute = [None]*test_num
for i in range(1, test_num+1):
    pass
