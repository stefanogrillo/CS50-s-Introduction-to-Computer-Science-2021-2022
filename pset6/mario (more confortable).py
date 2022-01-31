# Draw a pyramid as in Mario

from cs50 import get_int

# Continuously control the input: 0 < int < 9
while True:
    height = get_int("Height: ")
    if 0 < height < 9:
        break
    else:
        print("Input must be greater than 0 and lower than 9")

# Print as many # as requested
for i in range(height):
    print(" " * (height - i - 1) + "#" * (i + 1) + "  " + "#" * (i + 1))
