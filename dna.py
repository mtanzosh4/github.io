import csv
import sys

if len(sys.argv) != 3:
    exit("Wrong number of command line args")

# database = "databases/small.csv"
# sequence = "sequences/1.txt"
database = sys.argv[1]
sequence = sys.argv[2]

db_file = open(database, "r")
sq_file = open(sequence, "r")

db_list = []
reader = csv.reader(db_file)
db_list.extend(list(reader))

# print(db_list)

dna = sq_file.read()

# print(dna)
str_dict = {}

strs = db_list[0]

for i in range(1, len(strs)):
    str_dict[strs[i]] = 0;


for str in str_dict:
    position = dna.find(str)
    consecutive = 0
    while position != -1:
        consecutive += 1
        str_dict[str] = max(consecutive, str_dict[str])
        # print(f"{consecutive}: {dna[position:position + 4]}")
        next_position = position + len(str)
        position = dna.find(str, next_position)
        if position != next_position:
            consecutive = 0


# print(str_dict)
# print(db_list)

for i in range(1, len(db_list)):
    match = False
    # print(db_list[i][0])
    for j in range(1, len(db_list[0])):

        if int(db_list[i][j]) != str_dict[db_list[0][j]]:
            # not a match
            # print("no match")
            # print(f"No: {db_list[i][j]} {int(str_dict[db_list[0][j]])}")
            # print(f"Not a match: {db_list[i][0]}")
            match = False
            break
        else:
            # print(db_list[i][0])
            match = True
            # print("match")
    if match:
        print(db_list[i][0])