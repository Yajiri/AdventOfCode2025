from pathlib import Path

script_dir = Path(__file__).parent
input_file = script_dir / "input.txt"

ranges = []
numbers = []

reading_ranges = True
numberOfFreshItems = 0

with open(input_file, "r") as f:
    for line in f:
        line = line.strip()

        if not line: 
            reading_ranges = False
            continue

        if reading_ranges:
            start, end = map(int, line.split("-"))
            ranges.append((start, end))
        else:
            numbers.append(int(line))

    for number in numbers:
        #Ensure that the boolean is here and not before you start looping otherwise it will never reset to false and thuse eveything will be true after the first true.
        fresh = False
        for start, end in ranges:
            if start <= number <= end:
                fresh = True
                numberOfFreshItems = numberOfFreshItems + 1
                break

        #if fresh == True:
        #    print(number, "is a fresh item")
        #else:
        #    print(number, "is not a fresh")
    print("Number of fresh items are", numberOfFreshItems)