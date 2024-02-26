# TODO
from cs50 import get_string


def count_letters(word):
    count = 0
    for i in range(0, len(word), 1):
        if (word[i].isalpha()):
            count = count + 1
    return count


def count_words(word):
    count = 0
    for i in range(0, len(word), 1):
        if (word[i] == ' ' or word[i] == '\0'):
            count = count + 1
    return count


def count_sent(word):
    count = 0
    for i in range(0, len(word), 1):
        if (word[i] == '.' or word[i] == '?' or word[i] == '!'):
            count = count + 1
    return count


def main():
    text = get_string("Text: ")
    text = text + '\0'
    letters = count_letters(text)
    words = count_words(text)
    sent = count_sent(text)
    L = (letters / words) * 100
    S = (sent / words) * 100
    grade = 0.0588 * L - 0.296 * S - 15.8
    if (round(grade) >= 16):
        print("Grade 16+")
    elif (round(grade) < 1):
        print("Before Grade 1")
    else:
        print(f"Grade {round(grade)}")


if __name__ == "__main__":
    main()