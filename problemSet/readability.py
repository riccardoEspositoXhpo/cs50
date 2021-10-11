

def main():

    # promt user for text
    text = input("Text: ")

    score = computeScore(text)

    if score < 1:

        print("Before Grade 1")

    elif score >= 1 and score < 17:

        print(f"Grade {score}")

    else:

        print("Grade 16+")


def computeScore(text):

    score = 0

    # compute data required for formula
    elements = countElements(text)

    letters = elements[0]
    words = elements[1]
    sentences = elements[2]

    # letters and sentences per 100 words
    adjustedLetters = letters * (100 / words)
    adjustedSentences = sentences * (100 / words)

    # run the Coleman-Liau index
    score = (0.0588 * adjustedLetters) - (0.296 * adjustedSentences) - 15.8

    score = round(score)

    return score


def countElements(text):

    letters = words = sentences = 0

    for i in range(len(text)):

        # identify a letter with ascii
        if (text[i] >= 'A' and text[i] <= 'Z') or (text[i] >= 'a' and text[i] <= 'z'):

            letters += 1

        # identify a word with a space
        elif text[i] == ' ':

            words += 1

        # identify sentences with predetermined punctuation
        elif text[i] == '!' or text[i] == '.' or text[i] == '?':

            sentences += 1

    # the last word in text does not have a space. Add 1
    words += 1

    return [letters, words, sentences]


if __name__ == "__main__":
    main()