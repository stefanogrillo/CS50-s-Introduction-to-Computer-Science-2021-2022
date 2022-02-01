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
    
    
main()
