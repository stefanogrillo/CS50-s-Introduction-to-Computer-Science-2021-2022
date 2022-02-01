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
            
    # Define counters
    sumodd = 0
    sumeven = 0
    sum = 0

    # Transform the ccnumber in a list (btw with no "list" is more direct; I wanted to implement operations with lists)
    lstccnumber = [int(x) for x in str(ccnumber)]

    # Count the odds
    # Create a list starting from the last element, finishing at length 0, and moving back of 2 places
    odd = lstccnumber[-1::-2]
    # range(len(odd)) is useful to avoid int error
    for i in range(len(odd)):
        sumodd += odd[i]

    # Count the evens
    # Create a list starting from the second-to-last element, finishing at length 0, and moving back of 2 places
    even = lstccnumber[-2::-2]
    for i in range(len(even)):
        tempeven = even[i] * 2
        sumeven += tempeven % 10
        sumeven += int(tempeven / 10)

    sum = sumeven + sumodd

    # Identify the credit card
    # Has length 15 and first digit = 3 and second either 4 or 7 and sum is even?
    if length == 15 and lstccnumber[0] == 3 and lstccnumber[1] == 4 or lstccnumber[1] == 7 and sum % 2 == 0:
        print("AMEX")
    # Has length 16 and first digit = 5 and second digit between 0 and 6 and sum is even?
    elif lstccnumber[0] == 5 and length == 16 and 0 < lstccnumber[1] < 6 and sum % 2 == 0:
        print("MASTERCARD")
    # Has length 13 or 16 and first digit = 4 and sum is even?
    elif lstccnumber[0] == 4 and (length == 13 or length == 16) and sum % 2 == 0:
        print("VISA")
    else:
       print("INVALID")


main()
