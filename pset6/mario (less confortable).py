# Draw right aligned pyramid as in Mario

from cs50 import get_int

# Continuously control input: 0 < int < 9
while True:
    height = get_int("Height: ")
    if 0 < height < 9:
        break
    else:
        print("Height must be between 0 and 9 excluded")

# Draw one more row of width n
for i in range(height):
    print(" " * (height - i - 1) + "#" * (i + 1))
