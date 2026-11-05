grid = []


while True:
    numbers = input("Enter a row (or done to finish ): ").upper()

    if numbers == "DONE":
        break

    row = list(map(int, numbers.split()))
    grid.append(row)

operators = input("Please enter the operators with spaces in between: ").split()
for col in range(len(operators)):
    if operators[col] == '*':
        result = 1

        for row in grid:
            result *= row[col]
        print("The value of column", col + 1, "is", result)

    if operators[col] == '+':
        result = 0
        for row in grid:
            result += row[col]
        print("The value of column", col + 1, "is", result)

    if operators[col] == '-':
        result = grid[0][col]
        for row in grid[1:]:
            result -= row[col]
        print("The value of column", col + 1, "is", result)

    if operators[col] == '/':
        result = grid[0][col]
        for row in grid[1:]:
            result /= row[col]
        print("The value of column", col + 1, "is", result)