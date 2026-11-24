from dataclasses import dataclass
from datetime import timedelta
import time
from pathlib import Path
dir_path = Path(__file__).parent
file_path = dir_path / "input.txt"

@dataclass
class Puzzle:
        width: int
        height: int
        requirements: list[int]

@dataclass
class ParsedInput:
        nets: list
        puzzles: list[Puzzle]

Net = list[list[str]]
Board = list[list[int]]


def all_counts_zero(counts):
    return all(c == 0 for c in counts) 
    #Above code does the same as bellow code, but looks more python. 
    #for c in counts:
    #    if c != 0:
    #        return False
    #    return True
    
def rotate_90(net):
    h = len(net)
    w = len(net[0])

    rotated = [['.' for _ in range(h)] for _ in range(w)]
    for y in range(h):
        for x in range(w):
            rotated[x][h - 1 - y] = net[y][x]
    return rotated    


def generate_rotations(net):
    forms = []
    #This is like in rust with the: let mut current = net.clone(); but python  version.
    current = [row[:] for row in net]
    for _ in range(4):
        already_seen = False
        for form in forms:
            if form == current:
                already_seen = True
                break
        if not already_seen:
            forms.append([row[:] for row in current])
        current = rotate_90(current)
    return forms

def net_area(net):
    area = 0
    for row in net:
        for c in row:
            if c == '#':
                area += 1
    return area     
   
def fits(board, net, start_x, start_y):
    for y in range(len(net)):
        for x in range(len(net[0])):
            if net[y][x] != '#':
                continue
            board_x = start_x + x
            board_y = start_y + y

            if board_y >= len(board) or board_x >= len(board[0]):
                return False
            if board[board_y][board_x] > 0:
                return False
    return True        

def place_piece(board, net, start_x, start_y):
    for y in range(len(net)):
        for x in range(len(net[0])):
            if net[y][x] == '#':
                board[start_y + y][start_x + x] += 1


def remove_piece(board, net, start_x, start_y):
    for y in range(len(net)):
        for x in range(len(net[0])):
            if net[y][x] == '#':
                board[start_y + y][start_x + x] -= 1

def solve(board, nets_with_rotations, counts, nodes_explored, node_limit):
    if nodes_explored[0] > node_limit:
        return False
    if all_counts_zero(counts):
        return True
    for piece_index in range(len(nets_with_rotations)):
        if counts[piece_index] == 0:
            continue
        for net in nets_with_rotations[piece_index]:
            for y in range(len(board)):
                for x in range(len(board[0])):
                    nodes_explored[0] += 1
                    if nodes_explored[0] > node_limit:
                        return False
                    if not fits(board, net, x, y):
                        continue
                    place_piece(board, net, x, y)
                    counts[piece_index] -= 1

                    if solve(board, nets_with_rotations, counts, nodes_explored, node_limit):
                        return True
                    counts[piece_index] += 1
                    remove_piece(board, net, x, y)
    return False

def parse_input(path):
    nets = []
    puzzles = []
    
    with open(path, "r") as f:
        lines = [line.rstrip("\n") for line in f]
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        if not line:
            i += 1
            continue

        if line.endswith(":") and line[:-1].isdigit():
            net = []
            i += 1

            while i < len(lines):
                next_line  = lines[i].strip()

                if not next_line:
                    i += 1
                    break

                if all(c in "#." for c in next_line):
                    net.append(list(next_line))
                    i += 1
                else:
                    break
            if net:
                nets.append(net)
            continue 

        colon_pos = line.find(":")

        if colon_pos != -1:
            dims_part = line[:colon_pos].strip()
            rest = line[colon_pos + 1:].strip()
            x_pos = dims_part.find("x")
            if x_pos != -1:
                try:
                    width = int(dims_part[:x_pos].strip())
                    height = int(dims_part[x_pos + 1:].strip())

                    requirements = [
                        int(part)
                        for part in rest.split()
                    ]
                    puzzles.append(Puzzle(width, height, requirements))
                except ValueError:
                    print("Malformed puzzle line")
        i += 1
    return ParsedInput(nets, puzzles)

def main():
    counter = 0

    parsed = parse_input(file_path)
    nets = parsed.nets
    puzzles = parsed.puzzles

    if not nets:
        print("There are no nets in the input")
        return

    if not puzzles:
        print("There are no puzzles in the input")
        return

    nets_with_rotations = [
        generate_rotations(net)
        for net in nets
    ]

    net_areas = [
        net_area(net)
        for net in nets
    ]

    node_limit = 55_000_000
    time_limit = timedelta(seconds=10)

    for puzzle in puzzles:
        board_area = puzzle.width * puzzle.height
        required_area = 0

        for i, count in enumerate(puzzle.requirements):
            if i >= len(net_areas):
                raise RuntimeError(
                    f"Puzzle requires net index {i} "
                    f"but only {len(net_areas)} nets were parsed"
                )

            required_area += count * net_areas[i]

        print(
            "Puzzle",
            puzzle.width,
            "x",
            puzzle.height,
            "required area:",
            required_area,
            "board area:",
            board_area
        )

        if required_area > board_area:
            print(
                "No solution for",
                puzzle.width,
                "x",
                puzzle.height,
                "(pieces require more area than the board)"
            )
            print()
            continue

        board = [
            [0] * puzzle.width
            for _ in range(puzzle.height)
        ]

        counts = puzzle.requirements.copy()
        nodes_explored = [0]

        start = time.time()

        solved = solve(
            board,
            nets_with_rotations,
            counts,
            nodes_explored,
            node_limit
        )

        elapsed_seconds = time.time() - start
        elapsed = timedelta(seconds=elapsed_seconds)

        if solved:
            counter += 1

            print(
                "Solved",
                puzzle.width,
                "x",
                puzzle.height,
                "in",
                elapsed,
                "nodes explored:",
                nodes_explored[0]
            )

            for row in board:
                print(
                    "".join(
                        "#" if cell > 0 else "."
                        for cell in row
                    )
                )

        else:
            if (
                nodes_explored[0] > node_limit
                or elapsed > time_limit
            ):
                print(
                    f"Stopped search for "
                    f"{puzzle.width}x{puzzle.height} "
                    f"(limit reached), "
                    f"nodes explored: {nodes_explored[0]}, "
                    f"time: {elapsed}"
                )
            else:
                print(
                    f"No solution found for "
                    f"{puzzle.width}x{puzzle.height} "
                    f"(exhaustive within limits), "
                    f"nodes explored: {nodes_explored[0]}, "
                    f"time: {elapsed}"
                )

        print()

    print(f"Total amount of solved puzzles: {counter}")

if __name__  == "__main__":
    main()
            
