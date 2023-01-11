import random
f = open("input.txt", "w")


def  gen_matric(n,l,r):
    for i in range (n):
        for j in range (n):
            num = random.randint(l,r)
            f.write(str(num)+ " ")
        f.write("\n")

num = input("Enter highest number in test case: ")
num = int(num)
l, r = input("Enter 'lower' and 'upper' bounds to matrix entries separated by spaces: ").split()
l = int(l) 
r = int(r)
f.write(str(num)+ "\n")
for i in range(1,num+1):
    f.write(str(i)+ "\n")
    gen_matric(i,l,r)