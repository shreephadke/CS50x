from cs50 import SQL
from sys import argv
from csv import reader
import csv

db = SQL("sqlite:///students.db")

if not len(argv) == 2:
    print("INVALID")
    exit(1)

students = db.execute("SELECT * FROM students WHERE house = (?) ORDER BY last", argv[1])

for row in students:
    if row["middle"] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
