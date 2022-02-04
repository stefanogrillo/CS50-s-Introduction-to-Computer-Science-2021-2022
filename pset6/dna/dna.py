""" Implement a program that identifies a person based on their DNA """

import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit

    # Read database file into a variable
    databases = []
    csvfilename = sys.argv[1]
    # Read file
    with open(csvfilename, "r") as file:
        reader = csv.DictReader(file)
        # Populate "databases"
        for name in reader:
            databases += [name]
      
    # Create an universal variable
    sequence = list(databases[0])
    sequence.pop(0)

    # Read DNA sequence file into a variable
    txtfilename = sys.argv[2]
    # Read file
    with open(txtfilename, "r") as file:
        sequences = file.read()

    # Find longest match of each STR in DNA sequence
    number = []
    for i in sequence:
        number.append(longest_match(sequences, i))
    persons_seqences = dict(zip(sequence, number))

    # Check database for matching profiles
    done = False
    # For every dictionary in the list called "databases"
    for i in databases:
        # Create a list of values, no keys are included
        l = list(i.values())
        # Remove the names (str) from the list of values (int)
        l.pop(0)
        # Convert list values to int
        l = [int(j) for j in l]
        if l == list(persons_seqences.values()):
            print(i['name'])
            done = True
    if done == False:
        print('No match\n')
      

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

