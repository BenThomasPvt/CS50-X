import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Error")
        sys.exit(1)

    # Read database file into a variable
    database_file = sys.argv[1]
    sequence_file = sys.argv[2]

    with open(database_file, mode='r') as db_file:
        reader = csv.DictReader(db_file)
        database = list(reader)

    # Read DNA sequence file into a variable
    with open(sequence_file, mode='r') as seq_file:
        sequence = seq_file.read().strip()

    # Get the list of STRs from the database
    str_list = reader.fieldnames[1:]  # Skip the first column which is the name

    # Find longest match of each STR in DNA sequence
    longest_matches = {}
    for str_name in str_list:
        longest_matches[str_name] = longest_match(sequence, str_name)

    # Check database for matching profiles
    for person in database:
        match = True
        for str_name in str_list:
            if int(person[str_name]) != longest_matches[str_name]:
                match = False
                break
        if match:
            print(person['name'])
            return

    # If no match is found
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
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
