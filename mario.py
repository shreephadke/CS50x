print("Height: ", end="")
a = True
while(a):
    h = input()
    if h.isnumeric():
        h = (int(h))
        if h <= 0 or h > 8:
            print("Invalid input.")
        else:
            a = False
    else:
        print("Invalid input.")


for i in range(h):
    print(" " * (h-i-1), end="")
    print("#" * (i+1), end="")
    print("  ", end="")
    print("#" * (i+1))

