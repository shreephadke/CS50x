import csv
from sys import argv

# if there aren't 3 command-line arguments, exit the program
if not len(argv) == 3:
    print("INVALID")
    exit(1)

# open the database file and save it as a list named key
with open(argv[1], newline='') as keyf:
    reader = csv.reader(keyf)
    key = list(reader)

# open the sequence file and save it as a list named seq
with open(argv[2], newline='') as seqf:
    reader = csv.reader(seqf)
    seq = list(reader)

# declare variables, lists
counter, j = 0, 0
key1 = key[0][1:]
seq1 = seq[0][0]
fin = []

# print(len(key1))
# print(len(seq1))

# outer loop for iterating through the various STRs
for i in range(len(key1)):
    # create new list, and re-initialize variables after every STR is processed
    arr = []
    counter = 0
    j = 0
    # inner loop for iterating through the sequence
    while j < len(seq1):
        # if the substring contained by the current index j and
        # j + length of STR is equal to the current STR, increment counter
        # and move j to the index after that of the last character of the STR
        if (seq1[j:j+len(key1[i])]) == (key1[i]):
            counter += 1
            j += len(key1[i])
        # otherwise if counter is greater than 0, add it to the list
        # and only increment j by 1
        else:
            if counter > 0:
                arr.append(counter)
            counter = 0
            j += 1
    # if the list is not empty, sort the array and add the greatest value
    # to the final list
    if len(arr) > 0:
        arr.sort()
        fin.append(arr[-1])

# print(fin)

# number of rows in the key
numrows = len(key)

# iterate over the number of rows in the key, excluding the first one
for i in range(1, numrows):
    # convert list of strings to list of integers
    key2 = list(map(int, key[i][1:]))
    # compare the final list with the newly converted list
    # if true, print the name associated with the respective STRs and quit
    if fin == key2:
        print(key[i][0])
        exit(0)

print("No match")