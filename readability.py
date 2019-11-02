from cs50 import get_string
import re

def count_letters(text):
    count = 0
    for letter in text:
        if letter.isalpha():
            count += 1
    return count

def count_words(text):
    return len(text.split())


def count_sentences(text):
    count = 0
    for c in text:
        if c == '!' or c == '?' or c =='.':
            count += 1
    return count

text = get_string("Text: ")
# print(f"letter {count_letters(text)}")
# print(f"words {count_words(text)}")
# print(f"sentences {count_sentences(text)}")


L = count_letters(text) * 100 / count_words(text)
S = count_sentences(text) * 100 / count_words(text)
index = 0.0588 * L - 0.296 * S - 15.8

print(int(round(index)))
