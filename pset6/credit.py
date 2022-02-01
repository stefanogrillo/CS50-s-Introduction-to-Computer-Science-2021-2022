# Implement a program to recognize valid credit cards through Luhn’s Algorithm

import sys


def main():
    # Check some conditions
    while True:
        ccnumber = input("Number: ")
        length = len(str(ccnumber))
        if length == 13 or length == 15 or length == 16:
            break
        else:
            print("INVALID")
            sys.exit()
