ranges = [
    (3,5),
    (10,14),
    (16,20),
    (12,18)
]

numbers = list(map(int, input("Please enter numbers separated by spaces:").split()))

for number in numbers:
    #Ensure that the boolean is here and not before you start looping otherwise it will never reset to false and thuse eveything will be true after the first true.
    fresh = False
    for start, end in ranges:
        if start <= number <= end:
            fresh = True
            break

    if fresh == True:
        print(number, "is a fresh item")
    else:
        print(number, "is not a fresh item")

