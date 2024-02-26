import csv
import sys


def main():

    # TODO: Check for command-line usage

    if len(sys.argv) != 3:
        sys.exit("Wrong command lines")

    # TODO: Read database file into a variable

    with open(sys.argv[1]) as file:
        Mdict = csv.DictReader(file)
        Mkeys = Mdict.fieldnames
        MkeysD = dict.fromkeys(Mkeys, 0)

    # TODO: Read DNA sequence file into a variable

        with open(sys.argv[2]) as file1:
            DNA = file1.read()

    # TODO: Find longest match of each STR in DNA sequence

            for key in MkeysD:
                MkeysD[key] = longest_match(DNA, key)

    # TODO: Check database for matching profiles

            for row in Mdict:
                i = 0
                if (row != 'name'):
                    for key in row:
                        if (key != 'name'):
                            if (int(row[key]) != MkeysD[key]):
                                break
                            i = i + 1
                            if (i == len(row) - 1):
                                print(row["name"])
                                return
    print("No Match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
