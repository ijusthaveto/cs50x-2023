from cs50 import get_string


def main():
    text = get_string("Text: ")
    letters = count_letters(text)
    sentences = count_sentences(text)
    words = count_words(text)
    grade = count_grade(letters, sentences, words)
    if grade >= 15:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")


def count_letters(text):
    counter = 0
    for i in range(len(text)):
        if text[i].isalpha():
            counter = counter + 1
    return counter


def count_words(text):
    counter = 0
    for i in range(len(text)):
        if text[i].isspace():
            counter = counter + 1
    return counter + 1


def count_sentences(text):
    counter = 0
    for i in range(len(text)):
        if text[i] == "." or text[i] == "?" or text[i] == "!":
            counter = counter + 1
    return counter


def count_grade(letters, sentences, words):
    L = 100.0 * letters / words
    S = 100.0 * sentences / words
    return round(0.0588 * L - 0.296 * S - 15.8)


if __name__ == "__main__":
    main()
