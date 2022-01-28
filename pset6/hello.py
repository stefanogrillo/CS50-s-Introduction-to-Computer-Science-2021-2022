# Same as "hello.c"
# We ask the user's name, and we welcome them

# We import this "training wheel" function
from cs50 import get_string

answer = get_string("What is your name?\n")
print("Hello, " + answer)
# OR USE print(f"Hello, {answer}")
