# Analize the 

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
      
      
main()
