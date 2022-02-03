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
      

main()
