from pathlib import Path

script_dir = Path(__file__).parent
input_file = script_dir / "input.txt"

with open(input_file, "r") as f:
    line = f.read().strip()

#This looks java/c/c++ esq
#ranges = []
#for token in line.split(","):
    #start, end = token.split("-")
    #ranges.append((int(start), int(end)))


#This is more python
ranges = [
    tuple(map(int, token.split("-")))
    for token in line.split(",")
]

invalidNumberValue = 0

for start, end in ranges:
    for n in range(start, end +1):
        s = str(n)
        if len(s) %2 == 0:
            half = len(s) // 2 
            if s[:half] == s[half:]:
                print(n)
                invalidNumberValue += n

print(invalidNumberValue)