import csv
import re
import sys

def main():

    # Check for proper usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Open files
    data = csv.DictReader(open(sys.argv[1]))
    print(data)
    sequence = open(sys.argv[2]).read()

    # Get counts for each of the STRs
    counts = {}
    for subseq in data.fieldnames[1:]:
        print(subseq)
        print(data.fieldnames[0])
        counts[subseq] = longest_match(sequence, subseq)

    # Check each row for a matching profile
    for row in data:
        if all(counts[subseq] == int(row[subseq]) for subseq in counts):
            print(row["name"])
            return

    # No row matched
    print("No match")


def longest_match(sequence, subseq):
    """Returns length of longest run of subseq in sequence."""
    best = 0
    length = len(subseq)
    for i in range(len(sequence)):
        count = 0
        while True:
            start = i + count * length
            end = start + length
            if sequence[start:end] == subseq:
                count += 1
            else:
                break
        best = max(best, count)
    return best

if __name__ == "__main__":
    main()