# Simulate a sports tournament

import csv
import sys
import copy


def main():

    # Ensure correct usage
    if len(sys.argv) != 3:

        sys.exit("Usage: python dna.py DATABASE.csv SAMPLE.csv")

    # load the database into a dict
    sequenceCount = []

    with open(sys.argv[1], "r") as database:

        reader = csv.DictReader(database)

        for row in reader:

            sequenceCount.append(row)

    # define an identical dict with no name key
    sequenceCountNoName = copy.deepcopy(sequenceCount)

    for i in range(len(sequenceCountNoName)):

        sequenceCountNoName[i].pop('name')

    # load the sample in a list
    sampleArray = sample = []

    with open(sys.argv[2], "r") as samples:

        reader = csv.reader(samples)

        for row in reader:

            sampleArray.append(row)

    # convert to string
    sample = sampleArray[0][0]

    # output a dict of sequences and occurrences in sample
    sampleAnalysis = analyzeDna(sequenceCountNoName, sample)

    # return index of matched candidate based on analyzed sample
    candidateIndex = findCandidate(sequenceCountNoName, sampleAnalysis)

    # find candidate name
    if candidateIndex == -1:

        print("No Match")

    elif candidateIndex != -1:

        candidate = sequenceCount[candidateIndex]["name"]

        # print output
        print(candidate)


def analyzeDna(sequenceCountNoName, sample):

    sampleAnalysis = {}

    keys = sequenceCountNoName[0].keys()

    # dynamically sequence the DNA depending on which keys are in the database
    for key in keys:

        sampleAnalysis[key] = matchSequence(key, sample)

    return sampleAnalysis


def matchSequence(key, sample):

    # number of letters to search
    length = len(key)
    counter = 0

    # keep looking for multuple occurrences of key until the maximum is reached
    while True:

        # increment
        counter += 1

        # find substring in sample
        index = sample.find(key * counter)

        # key is not found but counter is at least 1
        if index == -1 and counter >= 1:

            break

    # the previous instance of counter identifies the string
    return str(counter - 1)


def findCandidate(sequenceCountNoName, sampleAnalysis):

    # initialize index
    index = -1

    # once the key is popped, sampleAnalysis should match exactly with one item of the sequenceCountNoName array
    for i in range(len(sequenceCountNoName)):

        if sequenceCountNoName[i] == sampleAnalysis:

            index = i

    return index


if __name__ == "__main__":
    main()

