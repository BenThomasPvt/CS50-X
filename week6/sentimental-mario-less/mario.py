import cs50

while True:
    n = cs50.get_int("Height: ")
    if (n < 1 or n > 8):
        continue
    else:
        break


for i in range(1, n+1):
    for j in range(1, n+1-i):
        print(" ", end="")

    for k in range(i):
        print("#", end="")

    print()
