# Create a program to calculate the minimum number of coins to be given back as change 

from cs50 import get_float

# Set a counter
coins = 0

# Check the conditions are met
while True:
    money = get_float("Change owed: ")
    if money > 0:
        break

# Convert to cents and round
money = round(int(money * 100))

# Keep iterating to count
while money > 0:
    if money >= 25:
        money -= 25
        coins += 1
    elif money >= 10:
        money -= 10
        coins += 1
    elif money >= 5:
        money -= 5
        coins += 1
    elif money >= 1:
        money -= 1
        coins += 1

print(f"{coins}")
