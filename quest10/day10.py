import re

from pathlib import Path
script_dir = Path(__file__).parent
input_file = script_dir / "input.txt"

def matches(a, b):
    if len(a) != len(b):
        return False
    for x, y in zip(a, b):
        if x != y:
            return False
    return True

def solve_and_return_best(target, buttons):
    best = float('inf')
    combinations = 1 << len(buttons)  # 2^{len(buttons)} subsets

    for mask in range(combinations):
        state = [0] * len(target)
        presses = 0

        for button in range(len(buttons)):
            if mask & (1 << button):
                presses += 1
                for light in buttons[button]:
                    state[light] ^= 1

        if matches(state, target):
            best = min(best, presses)

    return best

def main():
    #need to implement the grids.
    targets = []
    all_buttons = []

    with open(input_file, "r") as f:
        for line in f:
            line = line.strip()

            #parses targets
            #regex explenation... \[ = find [
            #[.#] = match either . or #
            #the + indicates that we need to find one or more... so loop
            # the () creates a capturing group, ([.#]) saves the part that matched. 
            #\] = find ] ... so this end the loop.
            target_match = re.search(r"\[([.#]+)\]", line)

            if not target_match:
                continue

            target = [
                1 if c == "#" else 0
                for c in target_match.group(1)
            ]

            targets.append(target)

            #parse buttons
            buttons = []
            #time to explain the re.findall 
            #\( ... this is find...
            #.* = any character ... repeated so zero*or more times
            #? is important to avoid greed without it it won't move on to the last thing 
            #() capture block 
            #\) find this and end.
            for button_text in re.findall(r"\((.*?)\)", line):
                button = [
                    int(x)
                    for x in button_text.split(",")
                ]
                buttons.append(button)
            all_buttons.append(buttons)

        total_value = 0

    for i in range(len(targets)):
        best = solve_and_return_best(targets[i], all_buttons[i])
        print("Machine", i + 1, "requires", best, "presses")
        total_value += best

    print(f"Total value (sum of all best presses) = {total_value}")

if __name__ == "__main__":
    main()