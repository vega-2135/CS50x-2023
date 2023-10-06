import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) < 2:
        print("Incorrect number of command-line arguments\n")

    # TODO: Read database file into a variable
    database_file = sys.argv[1]
    number_of_subsequences = 0
    with open(database_file, "r") as file:
        # Create a CSV reader object
        reader = csv.reader(file)

        # Read the first line from the CSV file
        first_line = next(reader)
        number_of_subsequences = len(first_line)

    # TODO: Read DNA sequence file into a variable
    sequence_file = sys.argv[2]
    with open(sequence_file, "r") as file:
        sequence = file.readline().strip()

    # TODO: Find longest match of each STR in DNA sequence
    subsequences_longest_match = {}

    for i in range(1, number_of_subsequences):
        subsequence = first_line[i]
        subsequences_longest_match[subsequence] = longest_match(sequence, subsequence)

    # TODO: Check database for matching profiles
    # Create dictionary from every line of the databse file
    with open(database_file, newline="") as csvfile:
        reader = csv.DictReader(csvfile)
        # Make a list to add the name of the person with the matching sequence
        name = []
        for row in reader:
            counter = 0
            for key in subsequences_longest_match:
                if int(row[key]) != subsequences_longest_match[key]:
                    continue
                else:
                    counter += 1

            if counter == number_of_subsequences - 1:
                name.append(row["name"])
                break

        if len(name) == 1:
            print(name[0])
        else:
            print("No match")


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


if __name__ == "__main__":
    main()