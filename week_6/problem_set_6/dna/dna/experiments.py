import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) < 2:
        print("Incorrect number of command-line arguments\n")

    # TODO: Read database file into a variable
    database_file = sys.argv[1]
    with open(database_file, "r") as file:
        # Create a CSV reader object
        reader = csv.reader(file)

        # Read the first line from the CSV file
        first_line = next(reader)

    # TODO: Read DNA sequence file into a variable
    sequence_file = sys.argv[2]
    with open(sequence_file, "r") as file:
        sequence = file.readline().strip()

    # TODO: Find longest match of each STR in DNA sequence
    subsequences_longest_match = {"AGATC": 4, "AATG": 1, "TATC": 5}




    # TODO: Check database for matching profiles
    #Create dictionary from every line of the databse file
    with open(database_file, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            print(row)
        #Compare the created dic with the subsequence_longest_match dic
            if subsequences_longest_match == row:
                print("success")
            else:
                print("no success")

    #return


if __name__ == "__main__":
    main()
