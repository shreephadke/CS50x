from cs50 import SQL
from sys import argv
from csv import reader
import csv

db = SQL("sqlite:///students.db")

if not len(argv) == 2:
    print("INVALID")
    exit(1)

with open(argv[1], newline='') as f:
    file = reader(f)
    for row in file:
        if row[0] == "name":
            continue
        name = row[0].split()
        if len(name) < 3:
            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                        name[0], None, name[1], row[1], row[2])
        else:
            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                        name[0], name[1], name[2], row[1], row[2])


# first = []
# mid = []
# last = []
# house = []
# year = []

# for i in range(1, len(file)):
#     split = file[i][0].split(" ")
#    first.append(split[0])
#    if len(split) == 2:
#        last.append(split[1])

#    else:
#        mid.append(split[1])
#        last.append(split[2])

# print(first)
# (mid)
# print(last)


#print(file[1:])

