# Re-created the Coleman-Liau Index, a readability test to gauge the understandability of a text with Python

from cs50 import get_string


def main():
    text = get_string("Text: ")

    # Count letters when the single char is a alphabetical
    letters = sum(1 for i in text if i.isalpha())

    # Count words
    words = len(text.split())

    # Count sentences when ".", "!", "?" occur
    sentences = text.count(".") + text.count("!") + text.count("?")
    # OR: len(re.split(r'[.!?]+', text)) - 1
    # BUT: import re
    # from https://github.com/gjacqual/CS50-readability-python/blob/main/readability.py
    
    # Coleman-Liau formula
    # Avg letters per 100 words
    L = 100 * letters / words
    # Avg words per 100 sentences
    S = 100 * sentences / words
    # Formula
    CL = round(0.0588 * L - 0.296 * S - 15.8)

    if CL > 16:
        print("Grade: 16+")
    elif CL < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {CL}")

    
main()
