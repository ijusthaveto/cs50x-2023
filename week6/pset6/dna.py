import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    data_csv_path = sys.argv[1]
    sequence_txt_path = sys.argv[2]

    # Read database file into a variable
    with open(data_csv_path, "r") as file:
        reader = csv.DictReader(file)
        data_csv = list(reader)

    # Read DNA sequence file into a variable
    with open(sequence_txt_path, "r") as file:
        sequence_txt = file.read()

    # Find longest match of each STR in DNA sequence
    match_dict = {}
    for row in data_csv:
        for key in row:
            if key != "name":
                # Find each nucleotide of DNA
                match_dict[key] = longest_match(sequence_txt, key)

    # Check database for matching profiles
    for people in data_csv:
        is_matched = True
        for nucleotide in people:
            if nucleotide != "name":
                if match_dict[nucleotide] != int(people[nucleotide]):
                    is_matched = False
        if is_matched:
            print(people["name"])
            sys.exit(0)

    print("No match")
    sys.exit(1)


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