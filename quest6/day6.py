from pathlib import Path
script_dir = Path(__file__).parent
input_file = script_dir / "input.txt"

numbers = []
operators = []
lines = []
finalResult = 0

with open(input_file, "r") as f:
    for line in f:
        lines.append(line.strip())

operators = list(lines[-1].split())

for line in lines[:-1]:
    numbers.append([int(num) for num in line.split()])

#bug searching
#for i, row in enumerate(numbers):
    #print(f"Row {i}: {len(row)} columns")
    #print("Operators:", len(operators))


for col in range(len(operators)):
    if operators[col] == '*':
        result = 1

        for row in numbers:
            result *= row[col]

    if operators[col] == '+':
        result = 0
        for row in numbers:
            result += row[col]

    if operators[col] == '-':
        result = numbers[0][col]
        for row in numbers[1:]:
            result -= row[col]

    if operators[col] == '/':
        result = numbers[0][col]
        for row in numbers[1:]:
            result /= row[col]
        
    finalResult += result
print("The total result is:", finalResult)