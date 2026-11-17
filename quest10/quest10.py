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
    # All targets grouped in one 2D list
    targets = [
        # Config 0: [.##.]
        [0, 1, 1, 0],

        # Config 1: [...#.]
        [0, 0, 0, 1, 0],

        # Config 2: [.###.#]
        [0, 1, 1, 1, 0, 1]
    ]

    # All button sets grouped in one 3D list
    all_buttons = [
        # Buttons for config 0: (3) (1,3) (2) (2,3) (0,2) (0,1)
        [
            [3],
            [1, 3],
            [2],
            [2, 3],
            [0, 2],
            [0, 1]
        ],

        # Buttons for config 1: (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4)
        [
            [0, 2, 3, 4],
            [2, 3],
            [0, 4],
            [0, 1, 2],
            [1, 2, 3, 4]
        ],

        # Buttons for config 2 (your original):
        # (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2)
        [
            [0, 1, 2, 3, 4],
            [0, 3, 4],
            [0, 1, 2, 4, 5],
            [1, 2]
        ]
    ]

    names = [
        "Config 1 [.##.]",
        "Config 2 [...#.]", 
        "Config 3 [.###.#]"
    ]

    total_value = 0

    for i in range(len(targets)):
        best = solve_and_return_best(targets[i], all_buttons[i])
        print(f"{names[i]} - Minimum amount of presses = {best}")
        total_value += best

    print(f"Total value (sum of all best presses) = {total_value}")

if __name__ == "__main__":
    main()