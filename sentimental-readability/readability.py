from cs50 import get_string


def main():
    text = get_string("Text: ")

    letter = 0
    for i in range(len(text)):
        if text[i].isalpha():
            letter += 1

    word = 0
    for i in range(len(text)):
        if text[i] == " ":
            word += 1
        elif text[i] == "-":
            word -= 1

    word += 1

    sentence = 0
    for i in range(len(text)):
        if text[i] == "!" or text[i] == "." or text[i] == "?":
            sentence += 1

    L = letter
    S = sentence
    W = word

    grade = round((0.0588 * L / W * 100) - (0.296 * S / W * 100) - 15.8)

    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print("Grade", grade)


main()
